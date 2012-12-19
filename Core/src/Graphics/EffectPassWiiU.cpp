#include <Graphics/EffectPass.h>

#include <Graphics/Effect.h>

#include "EffectInternalWiiU.h"

struct EffectPassInternal
{
	EffectInternal *Parent;
};

EffectPass::EffectPass( const Effect &effect, unsigned int progId ) :
	internal_( new EffectPassInternal )
{
	internal_->Parent = effect.internal_;
}

EffectPass::~EffectPass()
{
	delete internal_;
}

void EffectPass::Apply()
{
	GX2SetShaders( &internal_->Parent->Shader.fetchShader, internal_->Parent->Shader.pVertexShader, internal_->Parent->Shader.pPixelShader );
}
