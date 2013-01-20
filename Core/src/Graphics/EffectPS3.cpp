#include <Graphics/Effect.h>

#include <cassert>
#include <fstream>
#include <map>
#include <sstream>
#include <Utility/Log.h>

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

void Effect::Load( const std::string &name )
{
	internal_->VertexProgram = cgCreateProgramFromFile( cgCreateContext(), CG_BINARY, ( "/app_home/" + name + ".vpo" ).c_str(), cgGLGetLatestProfile( CG_GL_VERTEX ), NULL, NULL );
	internal_->FragmentProgram = cgCreateProgramFromFile( cgCreateContext(), CG_BINARY, ( "/app_home/" + name + ".fpo" ).c_str(), cgGLGetLatestProfile( CG_GL_FRAGMENT ), NULL, NULL );

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
