#include <Graphics/EffectParameter.h>

#include <Graphics/Effect.h>

#include "EffectInternalPS3.h"

#include <PSGL/psgl.h>
#include <PSGL/psglu.h>

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
	CGparameter Parameter;
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
	internal_->Parameter = reinterpret_cast< CGparameter >( id );
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
}

void EffectParameter::SetValue( const Matrix &m )
{
	internal_->PType = ParamType_Matrix;
	internal_->CachedMatrix = m;
}

void EffectParameter::SetValue( const boost::shared_ptr<struct Texture2D> &t )
{
}

void EffectParameter::SetValue( const Vector2 &v )
{
	internal_->PType = ParamType_Vector2;
	internal_->CachedVector2 = v;
}

void EffectParameter::SetValue( float v )
{
	internal_->PType = ParamType_Float;
	internal_->CachedSingle = v;
}

void EffectParameter::SetValue( int v )
{
	internal_->PType = ParamType_Int;
	internal_->CachedInt = v;
}

float EffectParameter::GetValueSingle()
{
	return internal_->CachedSingle;
}

void EffectParameter::Apply()
{
	if( internal_->Parameter == 0 )
		return;

	switch( internal_->PType )
	{
		case ParamType_None:
			break;
		case ParamType_Vector4:
			cgGLSetParameter4fv( internal_->Parameter, &internal_->CachedVector4.X );
			break;
		case ParamType_Matrix:
			cgGLSetMatrixParameterfr( internal_->Parameter, internal_->CachedMatrix.M );
			break;
		case ParamType_Texture:
			break;
		case ParamType_Vector2:
			cgGLSetParameter2fv( internal_->Parameter, &internal_->CachedVector2.X );
			break;
		case ParamType_Float:
			cgGLSetParameter1f( internal_->Parameter, internal_->CachedSingle );
			break;
		case ParamType_Int:
			cgGLSetTextureParameter( internal_->Parameter, internal_->CachedInt );
			cgGLEnableTextureParameter( internal_->Parameter );
			break;
		default:
			break;
	}
}
