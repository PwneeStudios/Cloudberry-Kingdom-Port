#include <Graphics/EffectPass.h>

#include <Graphics/Effect.h>

struct EffectPassInternal
{
	Effect *Effect;
};

EffectPass::EffectPass( Effect &effect, unsigned int id ) :
	internal_( new EffectPassInternal )
{
	internal_->Effect = &effect;
}

EffectPass::~EffectPass()
{
	delete internal_;
}

void EffectPass::Apply()
{
	internal_->Effect->Apply();
}
