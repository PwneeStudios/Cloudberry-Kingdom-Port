#include <Graphics/EffectPass.h>

#include <GL/glew.h>

struct EffectPassInternal
{
	GLuint id;
};

EffectPass::EffectPass( const Effect &effect, unsigned int id ) :
	internal_( new EffectPassInternal )
{
	internal_->id = id;
}

EffectPass::~EffectPass()
{
	delete internal_;
}

void EffectPass::Apply()
{
	glUseProgram( internal_->id );
}
