#include <Graphics/Effect.h>

#include <cassert>
#include <fstream>
#include <map>
#include <sstream>
#include <Utility/Log.h>
#include <vector>

#include <cell/cell_fs.h>
#include "EffectInternalPS3.h"
#include <PSGL/psgl.h>
#include <PSGL/psglu.h>

void Effect::Apply()
{
	cgGLBindProgram( internal_->VertexProgram );
	cgGLBindProgram( internal_->FragmentProgram );

	std::map<std::string, boost::shared_ptr<EffectParameter> >::iterator i;
	for( i = internal_->Parameters.begin(); i != internal_->Parameters.end(); ++i )
		i->second->Apply();
}

Effect::Effect() :
	internal_( new EffectInternal )
{
	internal_->FragmentProgram = 0;
	internal_->VertexProgram = 0;
}

Effect::~Effect()
{
	if( internal_->FragmentProgram )
		cgDestroyProgram( internal_->FragmentProgram );
	if( internal_->VertexProgram )
		cgDestroyProgram( internal_->VertexProgram );

	delete internal_;
}

extern std::string PS3_PATH_PREFIX;

char *LoadShaderFromSDATA( const std::string &path )
{
	CellFsErrno err;

	int fd;
	//err = cellFsOpen( path.c_str(), CELL_FS_O_RDONLY, &fd, NULL, 0 );
	err = cellFsSdataOpen( path.c_str(), CELL_FS_O_RDONLY, &fd, NULL, 0 );

	if( err != CELL_FS_SUCCEEDED )
		return NULL;

	uint64_t length, start, numRead;
	cellFsLseek( fd, 0, CELL_FS_SEEK_END, &length );
	cellFsLseek( fd, 0, CELL_FS_SEEK_SET, &start );

	char *buffer = new char[ length ];
	cellFsRead( fd, buffer, length, &numRead );

	assert( length == numRead );

	cellFsClose( fd );
	return buffer;
}

void Effect::Load( const std::string &name )
{
	// FIXME: We never free the shaderBinary.
	char *shaderBinary = LoadShaderFromSDATA( PS3_PATH_PREFIX + "ContentPS3/" + name + ".vpo.SDAT" );
	internal_->VertexProgram = cgCreateProgram( cgCreateContext(), CG_BINARY, shaderBinary, cgGLGetLatestProfile( CG_GL_VERTEX ), NULL, NULL );
	CGerror cgerror = cgGetError();
	shaderBinary = LoadShaderFromSDATA( PS3_PATH_PREFIX + "ContentPS3/" + name + ".fpo.SDAT" );
	internal_->FragmentProgram = cgCreateProgram( cgCreateContext(), CG_BINARY, shaderBinary, cgGLGetLatestProfile( CG_GL_FRAGMENT ), NULL, NULL );
	cgerror = cgGetError();
	/*internal_->VertexProgram = cgCreateProgramFromFile( cgCreateContext(), CG_BINARY, ( PS3_PATH_PREFIX + "ContentPS3/" + name + ".vpo" ).c_str(), cgGLGetLatestProfile( CG_GL_VERTEX ), NULL, NULL );
	internal_->FragmentProgram = cgCreateProgramFromFile( cgCreateContext(), CG_BINARY, ( PS3_PATH_PREFIX + "ContentPS3/" + name + ".fpo" ).c_str(), cgGLGetLatestProfile( CG_GL_FRAGMENT ), NULL, NULL );*/

	internal_->Parameters[ "SecretDefaultParameter" ] = boost::make_shared<EffectParameter>( *this, 0 );
	DefaultTechnique = boost::make_shared<EffectTechnique>(
		boost::shared_ptr<EffectPass>( new EffectPass( *this, 0 ) )
	);

	CurrentTechnique = DefaultTechnique;

	CGparameter parameter = cgGetFirstLeafParameter( internal_->VertexProgram, CG_GLOBAL );
	while( parameter )
	{
		const char *name = cgGetParameterName( parameter );
		int ordinal = cgGetParameterOrdinalNumber( parameter );
		internal_->Parameters[ name ] = boost::make_shared<EffectParameter>( *this,
			reinterpret_cast< int >( parameter )
		);

		parameter = cgGetNextLeafParameter( parameter );
	}

	parameter = cgGetFirstLeafParameter( internal_->FragmentProgram, CG_GLOBAL );
	while( parameter )
	{
		const char *name = cgGetParameterName( parameter );
		int ordinal = cgGetParameterOrdinalNumber( parameter );
		internal_->Parameters[ name ] = boost::make_shared<EffectParameter>( *this,
			reinterpret_cast< int >( parameter )
		);

		parameter = cgGetNextLeafParameter( parameter );
	}
}

boost::shared_ptr<EffectParameter> Effect::Parameters( const std::string &name )
{
	if( internal_->Parameters.find( name ) == internal_->Parameters.end() )
	{
		return internal_->Parameters[ "SecretDefaultParameter" ];
	}

	return internal_->Parameters[ name ];
}

boost::shared_ptr<EffectTechnique> Effect::Techniques( const std::string &name )
{
	return DefaultTechnique;
}

unsigned int Effect::Attributes( const std::string &name )
{
	return 0;
}
