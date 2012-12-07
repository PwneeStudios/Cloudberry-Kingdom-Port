#include <global_header.h>

namespace CloudberryKingdom
{

	void BobPhsxRandom::InitSingleton()
	{
		BobPhsx::InitSingleton();

		Name = Localization::Words_RANDOM;
		Icon = ObjectIcon::RandomIcon;
	}

const std::shared_ptr<BobPhsxRandom> BobPhsxRandom::instance = std::make_shared<BobPhsxRandom>();

	const std::shared_ptr<BobPhsxRandom> &BobPhsxRandom::getInstance()
	{
		return instance;
	}

	std::shared_ptr<BobPhsx> BobPhsxRandom::ChooseHeroType()
	{
		// FIXME: Check isomorphism.
		return Tools::GlobalRnd->ChooseOne( Bob::HeroTypes );
		//return Tools::GlobalRnd->Choose( Bob::HeroTypes );
	}

	std::shared_ptr<BobPhsx> BobPhsxRandom::Clone()
	{
		std::shared_ptr<BobPhsxRandom> newBob = std::make_shared<BobPhsxRandom>();
		CopyTo( newBob );
		return std::static_pointer_cast<BobPhsx>( newBob );
	}

	void BobPhsxRandom::CopyTo( const std::shared_ptr<BobPhsxRandom> &bob )
	{
		BobPhsx::CopyTo( std::static_pointer_cast<BobPhsx>( bob ) ); 
	}

	BobPhsxRandom::BobPhsxRandom()
	{
	}
}
