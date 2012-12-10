#ifndef _EFFECTTECHNIQUES_H_
#define _EFFECTTECHNIQUES_H_

#include "Hacks/XNA/EffectPass.h"

struct EffectTechnique
{



	std::vector<std::shared_ptr<EffectPass> > Passes;

	EffectTechnique()
	{
		Passes.resize( 1 );
	}

};

#endif
