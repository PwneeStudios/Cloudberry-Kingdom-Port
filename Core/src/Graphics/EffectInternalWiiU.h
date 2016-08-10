#ifndef _EFFECT_INTERNAL_WIIU_H_
#define _EFFECT_INTERNAL_WIIU_H_

#include <boost/shared_ptr.hpp>
#include <cafe/demo.h>
#include <map>
#include <string>

// Forward declarations.
class EffectParameter;

struct EffectInternal
{
	std::map<std::string, boost::shared_ptr<EffectParameter> > Parameters;
	std::map<std::string, unsigned int> Attributes;

	DEMOGfxShader Shader;
};

#endif