#include "Effect.h"

#include <map>

struct EffectInternal
{
	std::map<std::wstring, std::shared_ptr<EffectParameter> > Parameters;
};

Effect::Effect() :
	internal_( new EffectInternal )
{
	CurrentTechnique = std::make_shared<EffectTechnique>();
}

Effect::~Effect()
{
	delete internal_;
}

std::shared_ptr<EffectParameter> Effect::Parameters( const std::wstring &name )
{
	if( internal_->Parameters.find( name ) == internal_->Parameters.end() )
		return 0;

	return internal_->Parameters.at( name );
}

std::shared_ptr<EffectTechnique> Effect::Techniques( const std::wstring &name )
{
	return 0;
}