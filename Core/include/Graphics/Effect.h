#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "EffectParameter.h"
#include "EffectTechnique.h"

#include <memory>
#include <string>

class Effect
{

	std::shared_ptr<EffectTechnique> DefaultTechnique;

public:

	struct EffectInternal *internal_;

	std::shared_ptr<EffectTechnique> CurrentTechnique;

	Effect();
	~Effect();

	void Load( const std::string &name );

	std::shared_ptr<EffectParameter> Parameters( const std::string &name );
	std::shared_ptr<EffectTechnique> Techniques( const std::string &name );
	unsigned int Attributes( const std::string &name );

};

#endif
