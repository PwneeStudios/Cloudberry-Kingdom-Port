#include <Graphics/Effect.h>

#include <cassert>
#include <fstream>
#include <map>
#include <sstream>
#include <Utility/Log.h>
#include <vector>

#include "EffectInternalVita.h"

void Effect::Apply()
{
	//cgGLBindProgram( internal_->VertexProgram );
	//cgGLBindProgram( internal_->FragmentProgram );

	std::map<std::string, boost::shared_ptr<EffectParameter> >::iterator i;
	for( i = internal_->Parameters.begin(); i != internal_->Parameters.end(); ++i )
		i->second->Apply();
}

Effect::Effect() :
	internal_( new EffectInternal )
{
	//internal_->FragmentProgram = 0;
	//internal_->VertexProgram = 0;
}

Effect::~Effect()
{
	delete internal_;
}

extern std::string PS3_PATH_PREFIX;

char *LoadShaderFromSDATA( const std::string &path )
{
	char *buffer = 0;
	return buffer;
}

void Effect::Load( const std::string &name )
{
}

boost::shared_ptr<EffectParameter> Effect::Parameters( const std::string &name )
{
	if( internal_->Parameters.find( name ) == internal_->Parameters.end() )
	{
		return internal_->Parameters[ "SecretDefaultParameter" ];
	}

	return internal_->Parameters[ name ];
}

boost::shared_ptr<EffectTechnique> Effect::Techniques( const std::string &name )
{
	return DefaultTechnique;
}

unsigned int Effect::Attributes( const std::string &name )
{
	return 0;
}
