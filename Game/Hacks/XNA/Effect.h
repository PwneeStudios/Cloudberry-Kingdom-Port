#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "Hacks/XNA/EffectParameter.h"
#include "Hacks/XNA/EffectTechnique.h"

class Effect
{

public:

	std::shared_ptr<class EffectTechnique> CurrentTechnique;

	// FIXME: Implement.
	std::shared_ptr<class EffectParameter> Parameters( const std::wstring &name )
	{
		return 0;
	}

	// FIXME: Implement.
	std::shared_ptr<class EffectTechnique> Techniques( const std::wstring &name )
	{
		return 0;
	}

};

#endif
