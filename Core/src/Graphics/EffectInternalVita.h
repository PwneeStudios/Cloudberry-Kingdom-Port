#ifndef _EFFECT_INTERNAL_PS3_H_
#define _EFFECT_INTERNAL_PS3_H_

#include <boost/shared_ptr.hpp>
//#include <Cg/cg.h>
#include <map>
#include <string>

#include <gxm.h>

class EffectParameter;

struct EffectInternal
{
	std::map<std::string, boost::shared_ptr<EffectParameter> > Parameters;

	SceGxmVertexProgram		*VertexProgram;
	SceGxmFragmentProgram	*FragmentProgram;
};

enum ParamType
{
	ParamType_None,
	ParamType_Vector4,
	ParamType_Matrix,
	ParamType_Texture,
	ParamType_Vector2,
	ParamType_Float,
	ParamType_Int
};

struct EffectParameterInternal
{
	ParamType PType;

	float							Data[ sizeof( Matrix ) ];
	int								NumComponents;
	const SceGxmProgramParameter *	Parameter;
};

#endif
