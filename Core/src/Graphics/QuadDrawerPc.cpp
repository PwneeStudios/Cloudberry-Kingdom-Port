#include <Graphics/QuadDrawerPc.h>

#include <cassert>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <cstring>
#include <fstream>
#include <GL/glew.h>
#include <Graphics/Types.h>
#include <sstream>
#include <string>
#include <vector>

/// Maximum number of displayable quads.
#define MAX_QUADS 1024

struct QuadVert
{
	Vector2 Position;
	Vector2 TexCoord;
	Vector4 Color;
};

struct RenderBatch
{
	GLuint Offset;
	GLuint NumElements;
	ResourcePtr< Texture > Map;
};

typedef std::vector< RenderBatch > BatchList;

struct QuadDrawerInternal
{
	GLuint QuadBuffer[2];
	GLuint CurrentBuffer;
	GLuint NumElements;
	QuadVert *Vertices;

	GLuint Program;
	GLuint VertexAttrib;
	GLuint TexCoordAttrib;
	GLuint ColorAttrib;
	GLuint TexUniform;

	BatchList Batches;
};

/// Read a whole file into a string.
/**
 * @param path Path to file.
 * @return String containing file contents.
 */
std::string ReadFile( const std::string &path )
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
GLuint CreateShader( GLenum type, const std::string &src )
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
		
		assert( !errBuf );
		delete errBuf;

		glDeleteShader( shader );
		return 0;
	}

	return shader;
}

/// Create screen program.
/**
 * @return Identifier of screen space drawing program or 0 in case of failure.
 */
GLuint CreateProgram()
{
	using namespace std;

	string vsSource = ReadFile( "Content/Shaders/screen.vs" );
	string psSource = ReadFile( "Content/Shaders/screen.ps" );

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

QuadDrawerPc::QuadDrawerPc() :
	internal_( new QuadDrawerInternal )
{
	memset( internal_, 0, sizeof( QuadDrawerInternal ) );

	glGenBuffers( 2, internal_->QuadBuffer );

	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer[ 0 ] );
	glBufferData( GL_ARRAY_BUFFER, MAX_QUADS * 4 * sizeof( QuadVert ), 0, GL_DYNAMIC_DRAW );
	internal_->Vertices = reinterpret_cast< QuadVert * >(
		glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY )
	);
	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer[ 1 ] );
	glBufferData( GL_ARRAY_BUFFER, MAX_QUADS * 4 * sizeof( QuadVert ), 0, GL_DYNAMIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	internal_->Program = CreateProgram();

	internal_->VertexAttrib = glGetAttribLocation( internal_->Program, "a_position" );
	internal_->TexCoordAttrib = glGetAttribLocation( internal_->Program, "a_texcoord" );
	internal_->ColorAttrib = glGetAttribLocation( internal_->Program, "a_color" );
	internal_->TexUniform = glGetUniformLocation( internal_->Program, "u_texture" );

	glClearColor( 0, 0, 0, 1 );
	glClearDepth( 1 );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glDisable( GL_CULL_FACE );
	glViewport( 0, 0, 1280, 720 );

}

QuadDrawerPc::~QuadDrawerPc()
{
	glDeleteProgram( internal_->Program );

	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer[ internal_->CurrentBuffer ] );
	glUnmapBuffer( GL_ARRAY_BUFFER );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glDeleteBuffers( 2, internal_->QuadBuffer );

	delete internal_;
}

void QuadDrawerPc::Draw( const SimpleQuad &quad )
{
	if( internal_->NumElements >= MAX_QUADS * 4 )
		return;

	RenderBatch rb;
	rb.Map = quad.Diffuse;
	rb.Offset = 0;
	rb.NumElements = 4;

	for( int i = 0; i < 4; ++i )
	{
		internal_->Vertices->Position = quad.V[ i ];
		internal_->Vertices->TexCoord = quad.T[ i ];
		internal_->Vertices->Color = quad.Color;
		++internal_->Vertices;
	}

	BatchList &batches = internal_->Batches;
	if( batches.empty() )
		batches.push_back( rb );
	else
	{
		RenderBatch &lastBatch = batches[ batches.size() - 1 ];

		// If the previous batch has the same texture, expand it. Otherwise
		// start a new batch.
		if( lastBatch.Map == rb.Map )
			lastBatch.NumElements += 4;
		else
		{
			rb.Offset = lastBatch.Offset + lastBatch.NumElements;
			batches.push_back( rb );
		}
	}
	internal_->NumElements += 4;
}

void QuadDrawerPc::Flush()
{
	if( internal_->NumElements == 0 )
		return;

	glUseProgram( internal_->Program );
	glUniform1i( internal_->TexUniform, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer[ internal_->CurrentBuffer ] );
	glUnmapBuffer( GL_ARRAY_BUFFER );
	glEnableVertexAttribArray( internal_->VertexAttrib );
	glEnableVertexAttribArray( internal_->TexCoordAttrib );
	glEnableVertexAttribArray( internal_->ColorAttrib );
	glVertexAttribPointer( internal_->VertexAttrib, 2, GL_FLOAT, GL_FALSE,
		sizeof( QuadVert ), reinterpret_cast< const GLvoid * >( offsetof( QuadVert, Position ) ) );
	glVertexAttribPointer( internal_->TexCoordAttrib, 2, GL_FLOAT, GL_FALSE,
		sizeof( QuadVert ), reinterpret_cast< const GLvoid * >( offsetof( QuadVert, TexCoord ) ) );
	glVertexAttribPointer( internal_->ColorAttrib, 4, GL_FLOAT, GL_FALSE,
		sizeof( QuadVert ), reinterpret_cast< const GLvoid * >( offsetof( QuadVert, Color ) ) );

	glActiveTexture( GL_TEXTURE0 + 0 );

	for( size_t i = 0; i < internal_->Batches.size(); ++i )
	{
		RenderBatch &batch = internal_->Batches[ i ];
		batch.Map->Activate();
		glDrawArrays( GL_QUADS, batch.Offset, batch.NumElements );
	}

	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glDisableVertexAttribArray( internal_->ColorAttrib );
	glDisableVertexAttribArray( internal_->TexCoordAttrib );
	glDisableVertexAttribArray( internal_->VertexAttrib );

	internal_->Batches.clear();
	internal_->NumElements = 0;
	internal_->CurrentBuffer = 1 - internal_->CurrentBuffer;
	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer[ internal_->CurrentBuffer ] );
	internal_->Vertices = reinterpret_cast< QuadVert * >(
		glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY )
	);
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}
