#include <Graphics/Effect.h>

#include <cassert>
#include <fstream>
#include <GL/glew.h>
#include <map>
#include <sstream>
#include <Utility/Log.h>

#include "EffectInternalPc.h"

static std::string ReadFile( const std::string &path );
static GLuint CreateShader( GLenum type, const std::string &src );
static GLuint CreateProgram( const std::string &name );

void Effect::Apply()
{
	std::map<std::string, boost::shared_ptr<EffectParameter> >::iterator i;
	for( i = internal_->Parameters.begin(); i != internal_->Parameters.end(); ++i )
		i->second->Apply();
}

Effect::Effect() :
	internal_( new EffectInternal )
{
}

Effect::~Effect()
{
	delete internal_;
}

void Effect::Load( const std::string &name )
{
	internal_->Program = CreateProgram( "Content/" + name );
	assert( internal_->Program != 0 );

	GLint activeUniforms;
	glGetProgramiv( internal_->Program, GL_ACTIVE_UNIFORMS, &activeUniforms );

	internal_->Parameters[ "SecretDefaultParameter" ] = boost::make_shared<EffectParameter>( *this, -1 );
	for( GLint i = 0; i < activeUniforms; ++i )
	{
		GLchar buffer[ 256 ];
		GLsizei length;
		GLint size;
		GLenum type;
		glGetActiveUniform( internal_->Program, i, sizeof( buffer ), &length, &size, &type, buffer );

		internal_->Parameters[ buffer ] = boost::make_shared<EffectParameter>( *this, i );
	}

	DefaultTechnique = boost::make_shared<EffectTechnique>(
		boost::make_shared<EffectPass>( *this, internal_->Program )
	);
	CurrentTechnique = DefaultTechnique;
}

boost::shared_ptr<EffectParameter> Effect::Parameters( const std::string &name )
{
	if( internal_->Parameters.find( name ) == internal_->Parameters.end() )
	{
		//LOG.Write( "Unknown parameter %s\n", name.c_str() );

		return internal_->Parameters[ "SecretDefaultParameter" ];
	}

	return internal_->Parameters.at( name );
}

boost::shared_ptr<EffectTechnique> Effect::Techniques( const std::string &name )
{
	return DefaultTechnique;
}

unsigned int Effect::Attributes( const std::string &name )
{
	return glGetAttribLocation( internal_->Program, name.c_str() );
}

/// Read a whole file into a string.
/**
 * @param path Path to file.
 * @return String containing file contents.
 */
static std::string ReadFile( const std::string &path )
{
	using namespace std;
	stringstream ss;
	fstream in( path.c_str(), ios_base::in | ios_base::binary );

	string line;
	while( getline( in, line ) )
		ss << line << endl;

	return ss.str();
}

/// Create a shader.
/**
 * @param type Shader type.
 * @param src Shader source code.
 * @return Shader identifier or 0 in case of failure.
 */
static GLuint CreateShader( GLenum type, const std::string &src )
{
	GLuint shader = glCreateShader( type );

	const GLchar *source = src.c_str();
	glShaderSource( shader, 1, &source, NULL );

	glCompileShader( shader );

	GLint param;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &param );
	if( param == GL_FALSE )
	{
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &param );
		GLchar *errBuf = new GLchar[ param + 1 ];
		glGetShaderInfoLog( shader, param, NULL, errBuf );
		errBuf[ param ] = '\0';
		
		LOG.Write( static_cast< const char * >( errBuf ) );

		assert( !errBuf );
		delete errBuf;

		glDeleteShader( shader );
		return 0;
	}

	return shader;
}

/// Create screen program.
/**
 * @param name Name of effect.
 * @return Identifier of screen space drawing program or 0 in case of failure.
 */
static GLuint CreateProgram( const std::string &name )
{
	using namespace std;

	string vsSource = ReadFile( name + ".vs" );
	string psSource = ReadFile( name + ".ps" );

	GLuint vs = CreateShader( GL_VERTEX_SHADER, vsSource );
	GLuint ps = CreateShader( GL_FRAGMENT_SHADER, psSource );

	if( vs != 0 && ps != 0 )
	{
		GLuint program = glCreateProgram();

		glAttachShader( program, vs );
		glAttachShader( program, ps );
		glLinkProgram( program );

		GLint param;
		glGetProgramiv( program, GL_LINK_STATUS, &param );
		if( param == GL_FALSE )
		{
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &param );
			GLchar *errBuf = new GLchar[ param + 1 ];
			glGetProgramInfoLog( program, param, NULL, errBuf );
			errBuf[ param ] = '\0';

			LOG.Write( static_cast< const char * >( errBuf ) );

			assert( !errBuf );
			delete errBuf;

			glDeleteProgram( program );
			return 0;
		}

		glDeleteShader( vs );
		glDeleteShader( ps );
		return program;
	}

	return 0;
}