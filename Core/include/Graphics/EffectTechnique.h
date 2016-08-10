#ifndef _EFFECTTECHNIQUES_H_
#define _EFFECTTECHNIQUES_H_

#include "EffectPass.h"

#include <boost/shared_ptr.hpp>
#include <vector>

class EffectTechnique
{

public:

	std::vector<boost::shared_ptr<EffectPass> > Passes;

	EffectTechnique( const boost::shared_ptr<EffectPass> &pass )
	{
		Passes.push_back( pass );
	}

};

#endif
