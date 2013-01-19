#include <Graphics/QuadDrawerPc.h>

#include <cassert>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstring>
#include <fstream>
#include <GL/glew.h>
#include <Graphics/Types.h>
#include <Graphics/Effect.h>
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

	//GLuint Program;
	GLuint VertexAttrib;
	GLuint TexCoordAttrib;
	GLuint ColorAttrib;
	//GLuint TexUniform;

	boost::shared_ptr<Effect> CurrentEffect;
	boost::shared_ptr<EffectParameter> TextureParameter;
	boost::shared_ptr<EffectParameter> ExtraTextureParameter1;
	boost::shared_ptr<EffectParameter> ExtraTextureParameter2;

	ResourcePtr< Texture > MiddleFrame;
	ResourcePtr< Texture > LeftFrame;
	ResourcePtr< Texture > RightFrame;

	ResourcePtr< Texture > MiddleFrameMask;
	ResourcePtr< Texture > LeftFrameMask;
	ResourcePtr< Texture > RightFrameMask;

	ResourcePtr< Texture > CastleBackground;
	
	BatchList Batches;

	QuadDrawerInternal() :
		CurrentBuffer( 0 ),
		NumElements( 0 ),
		Vertices( 0 ),
		//Program( 0 ),
		VertexAttrib( 0 ),
		TexCoordAttrib( 0 ),
		ColorAttrib( 0 )//,
		//TexUniform( 0 )
	{

	}
};

/// Read a whole file into a string.
/**
 * @param path Path to file.
 * @return String containing file contents.
 */
/*std::string ReadFile( const std::string &path )
{
	using namespace std;
	stringstream ss;
	fstream in( path.c_str(), ios_base::in | ios_base::binary );

	string line;
	while( getline( in, line ) )
		ss << line << endl;

	return ss.str();
}*/

/// Create a shader.
/**
 * @param type Shader type.
 * @param src Shader source code.
 * @return Shader identifier or 0 in case of failure.
 */
/*GLuint CreateShader( GLenum type, const std::string &src )
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
}*/

/// Create screen program.
/**
 * @return Identifier of screen space drawing program or 0 in case of failure.
 */
/*GLuint CreateProgram()
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
}*/

QuadDrawerPc::QuadDrawerPc() :
	internal_( new QuadDrawerInternal )
{
	glGenBuffers( 2, internal_->QuadBuffer );

	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer[ 0 ] );
	glBufferData( GL_ARRAY_BUFFER, MAX_QUADS * 4 * sizeof( QuadVert ), 0, GL_DYNAMIC_DRAW );
	internal_->Vertices = reinterpret_cast< QuadVert * >(
		glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY )
	);
	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer[ 1 ] );
	glBufferData( GL_ARRAY_BUFFER, MAX_QUADS * 4 * sizeof( QuadVert ), 0, GL_DYNAMIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	/*internal_->Program = CreateProgram();

	internal_->VertexAttrib = glGetAttribLocation( internal_->Program, "a_position" );
	internal_->TexCoordAttrib = glGetAttribLocation( internal_->Program, "a_texcoord" );
	internal_->ColorAttrib = glGetAttribLocation( internal_->Program, "a_color" );
	internal_->TexUniform = glGetUniformLocation( internal_->Program, "u_texture" );*/

	glClearColor( 0, 0, 0, 1 );
	glClearDepth( 1 );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glDisable( GL_CULL_FACE );
	glViewport( 0, 0, 1280, 720 );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	internal_->MiddleFrame = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Center_Frame.png" );
	internal_->LeftFrame = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Left_Frame.png" );
	internal_->RightFrame = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Right_Frame.png" );

	internal_->MiddleFrameMask = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Center_Mask.png" );
	internal_->LeftFrameMask = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Left_Mask.png" );
	internal_->RightFrameMask = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Right_Mask.png" );

	internal_->CastleBackground = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Backdrop_2.png" );
}

QuadDrawerPc::~QuadDrawerPc()
{
	//glDeleteProgram( internal_->Program );

	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer[ internal_->CurrentBuffer ] );
	glUnmapBuffer( GL_ARRAY_BUFFER );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glDeleteBuffers( 2, internal_->QuadBuffer );

	delete internal_;
}

void QuadDrawerPc::SetEffect( const boost::shared_ptr<Effect> &effect )
{
	internal_->CurrentEffect = effect;

	internal_->VertexAttrib = effect->Attributes( "a_position" );
	internal_->TexCoordAttrib = effect->Attributes( "a_texcoord" );
	internal_->ColorAttrib = effect->Attributes( "a_color" );
	internal_->TextureParameter = effect->Parameters( "u_texture" );
	internal_->ExtraTextureParameter1 = effect->Parameters( "u_backTexture" );
	internal_->ExtraTextureParameter2 = effect->Parameters( "u_maskTexture" );
}

boost::shared_ptr<Effect> QuadDrawerPc::GetEffect()
{
	return internal_->CurrentEffect;
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
		RenderBatch &lastBatch = batches.back();

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

	internal_->TextureParameter->SetValue( 0 );
	internal_->ExtraTextureParameter1->SetValue( 1 );
	internal_->ExtraTextureParameter2->SetValue( 2 );

	internal_->CurrentEffect->CurrentTechnique->Passes[ 0 ]->Apply();

	//glUseProgram( internal_->Program );
	//glUniform1i( internal_->TexUniform, 0 );

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
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	internal_->CastleBackground->Activate( 1 );

	BatchList::iterator i;
	for( i = internal_->Batches.begin(); i != internal_->Batches.end(); ++i )
	{
		RenderBatch &batch = *i;
		batch.Map->Activate( 0 );

		if( batch.Map == internal_->LeftFrame )
			internal_->LeftFrameMask->Activate( 2 );
		else if( batch.Map == internal_->MiddleFrame )
			internal_->MiddleFrameMask->Activate( 2 );
		else if( batch.Map == internal_->RightFrame )
			internal_->RightFrameMask->Activate( 2 );

		glDrawArrays( GL_QUADS, batch.Offset, batch.NumElements );
	}

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
