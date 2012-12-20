#ifndef _EFFECT_INTERNAL_PC_H_
#define _EFFECT_INTERNAL_PC_H_

#include <boost/shared_ptr.hpp>
#include <map>
#include <string>

class EffectParameter;

struct EffectInternal
{
	std::map<std::string, boost::shared_ptr<EffectParameter> > Parameters;

	unsigned int Program;
};

#endif
