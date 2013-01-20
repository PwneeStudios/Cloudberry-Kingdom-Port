#ifndef _EFFECT_INTERNAL_PS3_H_
#define _EFFECT_INTERNAL_PS3_H_

#include <boost/shared_ptr.hpp>
#include <Cg/cg.h>
#include <map>
#include <string>

class EffectParameter;

struct EffectInternal
{
	std::map<std::string, boost::shared_ptr<EffectParameter> > Parameters;

	CGprogram VertexProgram;
	CGprogram FragmentProgram;
};

#endif
