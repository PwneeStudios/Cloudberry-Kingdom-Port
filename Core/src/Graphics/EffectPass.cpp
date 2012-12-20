#include <Graphics/EffectPass.h>

#include <GL/glew.h>
#include <Graphics/Effect.h>

struct EffectPassInternal
{
	GLuint id;
	Effect *Effect;
};

EffectPass::EffectPass( Effect &effect, unsigned int id ) :
	internal_( new EffectPassInternal )
{
	internal_->id = id;
	internal_->Effect = &effect;
}

EffectPass::~EffectPass()
{
	delete internal_;
}

void EffectPass::Apply()
{
	glUseProgram( internal_->id );
	internal_->Effect->Apply();
}
