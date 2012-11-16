#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

std::shared_ptr<BobPhsx> Challenge_HeroFactoryEscalation::FactoryHero = BobPhsxNormal::getInstance();
const std::shared_ptr<Challenge_HeroFactoryEscalation> Challenge_HeroFactoryEscalation::instance = std::make_shared<Challenge_HeroFactoryEscalation>();

	const std::shared_ptr<Challenge_HeroFactoryEscalation> &Challenge_HeroFactoryEscalation::getInstance() const
	{
		return instance;
	}

	Challenge_HeroFactoryEscalation::Challenge_HeroFactoryEscalation()
	{
		GameTypeId = 10;
		Name = Localization::Words_CUSTOM;
	}

	std::shared_ptr<BobPhsx> Challenge_HeroFactoryEscalation::GetHero( int i )
	{
		return FactoryHero;
	}
}
