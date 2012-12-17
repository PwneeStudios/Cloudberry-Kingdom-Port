#include <Graphics/EffectParameter.h>

struct EffectParameterInternal
{
};

EffectParameter::EffectParameter( unsigned int progId, int id ) :
	internal_( new EffectParameterInternal )
{
}

EffectParameter::~EffectParameter()
{
	delete internal_;
}

void EffectParameter::SetValue( const Vector4 &v )
{
}

void EffectParameter::SetValue( const Matrix &m )
{
}

void EffectParameter::SetValue( const boost::shared_ptr<struct Texture2D> &t )
{
}

void EffectParameter::SetValue( const Vector2 &v )
{
}

void EffectParameter::SetValue( float v )
{
}

void EffectParameter::SetValue( int v )
{
}

float EffectParameter::GetValueSingle()
{
	return 0;
}