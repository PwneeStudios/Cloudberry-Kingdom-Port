#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "EffectParameter.h"
#include "EffectTechnique.h"

#include <memory>
#include <string>

struct Effect
{

	struct EffectInternal *internal_;

	std::shared_ptr<EffectTechnique> CurrentTechnique;

	Effect();
	~Effect();

	std::shared_ptr<EffectParameter> Parameters( const std::wstring &name );
	std::shared_ptr<EffectTechnique> Techniques( const std::wstring &name );

};

#endif
