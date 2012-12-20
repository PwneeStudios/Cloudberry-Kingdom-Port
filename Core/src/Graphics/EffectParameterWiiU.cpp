#include <Graphics/EffectParameter.h>

#include <Graphics/Effect.h>

#include <cafe/demo.h>
#include <cafe/gx2.h>

#include "EffectInternalWiiU.h"

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
	u32 Offset;
	EffectInternal *Parent;

	ParamType PType;
	Vector4 CachedVector4;
	Matrix CachedMatrix;
	Vector2 CachedVector2[2];
	float CachedSingle[4];
	int CachedInt[4];
};

EffectParameter::EffectParameter( const Effect &effect, int id ) :
	internal_( new EffectParameterInternal )
{
	internal_->Offset = static_cast< u32 >( id );
	internal_->Parent = effect.internal_;

	internal_->PType = ParamType_None;
	memset( internal_->CachedVector2, 0, sizeof( internal_->CachedVector2 ) );
	memset( internal_->CachedSingle, 0, sizeof( internal_->CachedSingle ) );
	memset( internal_->CachedInt, 0, sizeof( internal_->CachedInt ) );
}

EffectParameter::~EffectParameter()
{
	delete internal_;
}

void EffectParameter::SetValue( const Vector4 &v )
{
	if( internal_->Offset == 0xffff )
		return;

	internal_->PType = ParamType_Vector4;
	internal_->CachedVector4 = v;
	/*GX2SetShaders( &internal_->Parent->Shader.fetchShader, internal_->Parent->Shader.pVertexShader, internal_->Parent->Shader.pPixelShader );
	GX2SetVertexUniformReg( internal_->Offset, 4, &v.X );*/
}

void EffectParameter::SetValue( const Matrix &m )
{
	if( internal_->Offset == 0xffff )
		return;

	internal_->PType = ParamType_Matrix;
	internal_->CachedMatrix = m;
	/*GX2SetShaders( &internal_->Parent->Shader.fetchShader, internal_->Parent->Shader.pVertexShader, internal_->Parent->Shader.pPixelShader );
	GX2SetVertexUniformReg( internal_->Offset, 16, m.M );*/
}

void EffectParameter::SetValue( const boost::shared_ptr<struct Texture2D> &t )
{
}

void EffectParameter::SetValue( const Vector2 &v )
{
	if( internal_->Offset == 0xffff )
		return;

	internal_->PType = ParamType_Vector2;
	internal_->CachedVector2[ 0 ] = v;
	/*Vector2 buf[] = { v, Vector2( 0 ) };
	GX2SetShaders( &internal_->Parent->Shader.fetchShader, internal_->Parent->Shader.pVertexShader, internal_->Parent->Shader.pPixelShader );
	GX2SetVertexUniformReg( internal_->Offset, 4, buf );*/
}

void EffectParameter::SetValue( float v )
{
	if( internal_->Offset == 0xffff )
		return;

	internal_->PType = ParamType_Float;
	internal_->CachedSingle[ 0 ] = v;
	/*float buf[] = { v, 0, 0, 0 };
	internal_->CachedSingle = v;
	GX2SetShaders( &internal_->Parent->Shader.fetchShader, internal_->Parent->Shader.pVertexShader, internal_->Parent->Shader.pPixelShader );
	GX2SetVertexUniformReg( internal_->Offset, 4, buf );*/
}

void EffectParameter::SetValue( int v )
{
	//GX2SetPixelUniformReg( internal_->Offset, 8, &v.X );
}

float EffectParameter::GetValueSingle()
{
	return internal_->CachedSingle[ 0 ];
}

void EffectParameter::Apply()
{
	if( internal_->Offset == 0xffff )
		return;

	switch( internal_->PType )
	{
		case ParamType_None:
			break;
		case ParamType_Vector4:
			GX2SetVertexUniformReg( internal_->Offset, 4, &internal_->CachedVector4 );
			break;
		case ParamType_Matrix:
			GX2SetVertexUniformReg( internal_->Offset, 16, internal_->CachedMatrix.M );
			break;
		case ParamType_Texture:
			break;
		case ParamType_Vector2:
			GX2SetVertexUniformReg( internal_->Offset, 4, internal_->CachedVector2 );
			break;
		case ParamType_Float:
			GX2SetVertexUniformReg( internal_->Offset, 4, internal_->CachedSingle );
			break;
		case ParamType_Int:
			break;
	}
}
