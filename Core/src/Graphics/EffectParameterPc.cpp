#include <Graphics/EffectParameter.h>

#include <GL/glew.h>

struct EffectParameterInternal
{
	int Location;
	float CachedSingle;
	GLuint ProgId;
};

EffectParameter::EffectParameter( unsigned int progId, int id ) :
	internal_( new EffectParameterInternal )
{
	internal_->Location = id;
	internal_->CachedSingle = 0;
	internal_->ProgId = progId;
}

EffectParameter::~EffectParameter()
{
	delete internal_;
}

void EffectParameter::SetValue( const Vector4 &v )
{
	glUseProgram( internal_->ProgId );
	glUniform4fv( internal_->Location, 1, &v.X );
}

void EffectParameter::SetValue( const Matrix &m )
{
	glUseProgram( internal_->ProgId );
	glUniform4fv( internal_->Location, 4, m.M );
}

void EffectParameter::SetValue( const boost::shared_ptr<struct Texture2D> &t )
{
	glUseProgram( internal_->ProgId );
}

void EffectParameter::SetValue( const Vector2 &v )
{
	glUseProgram( internal_->ProgId );
	glUniform2fv( internal_->Location, 1, &v.X );
}

void EffectParameter::SetValue( float v )
{
	internal_->CachedSingle = v;
	glUseProgram( internal_->ProgId );
	glUniform1f( internal_->Location, v );
}

void EffectParameter::SetValue( int v )
{
	glUseProgram( internal_->ProgId );
	glUniform1i( internal_->Location, v );
}

float EffectParameter::GetValueSingle()
{
	return internal_->CachedSingle;
}