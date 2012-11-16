#include "Random.h"
#include "Game/Localization.h"
#include "Game/Objects/Icon.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Tools/Tools.h"

namespace CloudberryKingdom
{

	void BobPhsxRandom::InitSingleton()
	{
		BobPhsx::InitSingleton();

		Name = Localization::Words_RANDOM;
		Icon = ObjectIcon::RandomIcon;
	}

const std::shared_ptr<BobPhsxRandom> BobPhsxRandom::instance = std::make_shared<BobPhsxRandom>();

	const std::shared_ptr<BobPhsxRandom> &BobPhsxRandom::getInstance() const
	{
		return instance;
	}

	std::shared_ptr<BobPhsx> BobPhsxRandom::ChooseHeroType()
	{
		return Tools::GlobalRnd->Choose( Bob::HeroTypes );
	}

	BobPhsxRandom::BobPhsxRandom()
	{
	}
}
