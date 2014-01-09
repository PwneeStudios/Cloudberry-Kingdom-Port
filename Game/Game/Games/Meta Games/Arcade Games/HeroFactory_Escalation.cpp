#include <small_header.h>
#include "Game/Games/Meta Games/Arcade Games/HeroFactory_Escalation.h"

#include "Game/Localization.h"
#include "Game/Games/Meta Games/Arcade Games/Escalate/Escalation.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Player/Hero Physics/Normal.h"


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
