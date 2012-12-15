#ifndef _EFFECTTECHNIQUES_H_
#define _EFFECTTECHNIQUES_H_

#include "EffectPass.h"

#include <vector>

struct EffectTechnique
{

	std::vector<std::shared_ptr<EffectPass> > Passes;

	EffectTechnique()
	{
		Passes.resize( 1 );
		Passes[ 0 ] = std::make_shared<EffectPass>();
	}

};

#endif
