#include <Graphics/EffectParameter.h>

#include <cafe/demo.h>
#include <cafe/gx2.h>

struct EffectParameterInternal
{
	u32 Offset;
};

EffectParameter::EffectParameter( unsigned int progId, int id ) :
	internal_( new EffectParameterInternal )
{
	internal_->Offset = static_cast< u32 >( id );
}

EffectParameter::~EffectParameter()
{
	delete internal_;
}

void EffectParameter::SetValue( const Vector4 &v )
{
	GX2SetVertexUniformReg( internal_->Offset, 16, &v.X );
}

void EffectParameter::SetValue( const Matrix &m )
{
	GX2SetVertexUniformReg( internal_->Offset, 64, m.M );
}

void EffectParameter::SetValue( const boost::shared_ptr<struct Texture2D> &t )
{
}

void EffectParameter::SetValue( const Vector2 &v )
{
	GX2SetVertexUniformReg( internal_->Offset, 8, &v.X );
}

void EffectParameter::SetValue( float v )
{
	GX2SetVertexUniformReg( internal_->Offset, 4, &v );
}

void EffectParameter::SetValue( int v )
{
	//GX2SetPixelUniformReg( internal_->Offset, 8, &v.X );
}

float EffectParameter::GetValueSingle()
{
	return 0;
}