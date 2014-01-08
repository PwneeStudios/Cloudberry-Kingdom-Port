#include <Graphics/EffectParameter.h>

#include <Graphics/Effect.h>
#include <gxm.h>

#include "EffectInternalVita.h"

EffectParameter::EffectParameter( const Effect &effect, int id ) :
	internal_( new EffectParameterInternal )
{
	internal_->Parameter		= reinterpret_cast< const SceGxmProgramParameter * >( id );

	internal_->PType			= ParamType_None;
	internal_->NumComponents	= 0;
}

EffectParameter::~EffectParameter()
{
	delete internal_;
}

void EffectParameter::SetValue( const Vector4 &v )
{
	internal_->PType = ParamType_Vector4;
	memcpy( internal_->Data, &v, sizeof( Vector4 ) );
	internal_->NumComponents = 4;
}

void EffectParameter::SetValue( const Matrix &m )
{
	internal_->PType = ParamType_Matrix;
	memcpy( internal_->Data, &m, sizeof( Matrix ) );
	internal_->NumComponents = 16;
}

void EffectParameter::SetValue( const boost::shared_ptr<struct Texture2D> &t )
{
}

void EffectParameter::SetValue( const Vector2 &v )
{
	internal_->PType = ParamType_Vector2;
	memcpy( internal_->Data, &v, sizeof( Vector2 ) );
	internal_->NumComponents = 2;
}

void EffectParameter::SetValue( float v )
{
	internal_->PType = ParamType_Float;
	internal_->Data[ 0 ] = v;
	internal_->NumComponents = 1;
}

void EffectParameter::SetValue( int v )
{
	internal_->PType = ParamType_Int;
	memcpy( internal_->Data, &v, sizeof( int ) );
	internal_->NumComponents = 1;
}

float EffectParameter::GetValueSingle()
{
	return internal_->Data[ 0 ];
}

void EffectParameter::Apply()
{
	//if( internal_->Parameter == 0 )
	//	return;

	switch( internal_->PType )
	{
		case ParamType_None:
			break;
		case ParamType_Vector4:
			//cgGLSetParameter4fv( internal_->Parameter, &internal_->CachedVector4.X );
			break;
		case ParamType_Matrix:
			//cgGLSetMatrixParameterfr( internal_->Parameter, internal_->CachedMatrix.M );
			break;
		case ParamType_Texture:
			break;
		case ParamType_Vector2:
			//cgGLSetParameter2fv( internal_->Parameter, &internal_->CachedVector2.X );
			break;
		case ParamType_Float:
			//cgGLSetParameter1f( internal_->Parameter, internal_->CachedSingle );
			break;
		case ParamType_Int:
			//cgGLSetTextureParameter( internal_->Parameter, internal_->CachedInt );
			//cgGLEnableTextureParameter( internal_->Parameter );
			break;
		default:
			break;
	}
}
