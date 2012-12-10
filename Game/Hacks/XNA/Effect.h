#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Hacks/XNA/EffectParameter.h"
#include "Hacks/XNA/EffectTechnique.h"

struct Effect
{



	std::shared_ptr<struct EffectTechnique> CurrentTechnique;

	// FIXME: Implement.
	std::shared_ptr<struct EffectParameter> Parameters( const std::wstring &name )
	{
		return 0;
	}

	// FIXME: Implement.
	std::shared_ptr<struct EffectTechnique> Techniques( const std::wstring &name )
	{
		return 0;
	}

};

#endif
