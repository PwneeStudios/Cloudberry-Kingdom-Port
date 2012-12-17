#include <Graphics/Effect.h>

#include <map>
#include <Utility/Log.h>

struct EffectInternal
{
	std::map<std::string, boost::shared_ptr<EffectParameter> > Parameters;
};

Effect::Effect() :
	internal_( new EffectInternal )
{
}

Effect::~Effect()
{
	delete internal_;
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
