#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Hacks/XNA/EffectParameter.h"
#include "Hacks/XNA/EffectTechnique.h"

struct Effect
{

	std::shared_ptr<EffectTechnique> CurrentTechnique;

	Effect() 
	{
		CurrentTechnique = std::make_shared<EffectTechnique>();
	}

	// FIXME: Implement.
	std::shared_ptr<EffectParameter> Parameters( const std::wstring &name )
	{
		return 0;
	}

	// FIXME: Implement.
	std::shared_ptr<EffectTechnique> Techniques( const std::wstring &name )
	{
		return CurrentTechnique;
	}

};

#endif
