#ifndef _EFFECTTECHNIQUES_H_
#define _EFFECTTECHNIQUES_H_

#include "EffectPass.h"

#include <vector>

class EffectTechnique
{

public:

	std::vector<boost::shared_ptr<EffectPass> > Passes;

	EffectTechnique( unsigned int progId )
	{
		Passes.resize( 1 );
		Passes[ 0 ] = boost::make_shared<EffectPass>( progId );
	}

};

#endif
