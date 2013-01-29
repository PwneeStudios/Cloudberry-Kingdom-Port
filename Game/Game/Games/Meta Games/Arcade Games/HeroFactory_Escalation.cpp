#include <global_header.h>

namespace CloudberryKingdom
{

	boost::shared_ptr<BobPhsx> Challenge_HeroFactoryEscalation::FactoryHero = BobPhsxNormal::getInstance();
	boost::shared_ptr<Challenge_HeroFactoryEscalation> Challenge_HeroFactoryEscalation::instance = boost::make_shared<Challenge_HeroFactoryEscalation>();

	const boost::shared_ptr<Challenge_HeroFactoryEscalation> &Challenge_HeroFactoryEscalation::getInstance()
	{
		return instance;
	}

	Challenge_HeroFactoryEscalation::Challenge_HeroFactoryEscalation()
	{
		GameTypeId = 10;
		Name = Localization::Words_Custom;
	}

	boost::shared_ptr<BobPhsx> Challenge_HeroFactoryEscalation::GetHero( int i )
	{
		return FactoryHero;
	}
}
