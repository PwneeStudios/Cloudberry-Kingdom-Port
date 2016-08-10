#include <Graphics/EffectParameter.h>

#include <GL/glew.h>
#include <Graphics/Effect.h>

#include "EffectInternalPc.h"

enum ParamType
{
	ParamType_None,
	ParamType_Vector4,
	ParamType_Matrix,
	ParamType_Texture,
	ParamType_Vector2,
	ParamType_Float,
	ParamType_Int
};

struct EffectParameterInternal
{
	int Location;
	GLuint ProgId;

	ParamType PType;
	Vector4 CachedVector4;
	Matrix CachedMatrix;
	Vector2 CachedVector2;
	float CachedSingle;
	int CachedInt;
};

EffectParameter::EffectParameter( const Effect &effect, int id ) :
	internal_( new EffectParameterInternal )
{
	internal_->Location = id;
	internal_->ProgId = effect.internal_->Program;

	internal_->PType = ParamType_None;
	internal_->CachedSingle = 0;
	internal_->CachedInt = 0;
}

EffectParameter::~EffectParameter()
{
	delete internal_;
}

void EffectParameter::SetValue( const Vector4 &v )
{
	internal_->PType = ParamType_Vector4;
	internal_->CachedVector4 = v;
	/*glUseProgram( internal_->ProgId );
	glUniform4fv( internal_->Location, 1, &v.X );*/
}

void EffectParameter::SetValue( const Matrix &m )
{
	internal_->PType = ParamType_Matrix;
	internal_->CachedMatrix = m;
	/*glUseProgram( internal_->ProgId );
	glUniform4fv( internal_->Location, 4, m.M );*/
}

void EffectParameter::SetValue( const boost::shared_ptr<struct Texture2D> &t )
{
	//glUseProgram( internal_->ProgId );
}

void EffectParameter::SetValue( const Vector2 &v )
{
	internal_->PType = ParamType_Vector2;
	internal_->CachedVector2 = v;
	/*glUseProgram( internal_->ProgId );
	glUniform2fv( internal_->Location, 1, &v.X );*/
}

void EffectParameter::SetValue( float v )
{
	internal_->PType = ParamType_Float;
	internal_->CachedSingle = v;
	/*glUseProgram( internal_->ProgId );
	glUniform1f( internal_->Location, v );*/
}

void EffectParameter::SetValue( int v )
{
	internal_->PType = ParamType_Int;
	internal_->CachedInt = v;
	/*glUseProgram( internal_->ProgId );
	glUniform1i( internal_->Location, v );*/
}

float EffectParameter::GetValueSingle()
{
	return internal_->CachedSingle;
}

void EffectParameter::Apply()
{
	switch( internal_->PType )
	{
		case ParamType_None:
			break;
		case ParamType_Vector4:
			glUniform4fv( internal_->Location, 1, &internal_->CachedVector4.X );
			break;
		case ParamType_Matrix:
			glUniformMatrix4fv( internal_->Location, 1, GL_TRUE, internal_->CachedMatrix.M );
			break;
		case ParamType_Texture:
			break;
		case ParamType_Vector2:
			glUniform2fv( internal_->Location, 1, &internal_->CachedVector2.X );
			break;
		case ParamType_Float:
			glUniform1f( internal_->Location, internal_->CachedSingle );
			break;
		case ParamType_Int:
			glUniform1i( internal_->Location, internal_->CachedInt );
			break;
	}
}
