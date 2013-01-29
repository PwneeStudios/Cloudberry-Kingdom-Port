#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void BobPhsxRandom::InitializeStatics()
	{
		BobPhsxRandom::instance = boost::make_shared<BobPhsxRandom>();
			InitBobPhsxSingleton( BobPhsxRandom::instance );
	}

	// Statics
	boost::shared_ptr<BobPhsxRandom> BobPhsxRandom::instance;


	void BobPhsxRandom::InitSingleton()
	{
		BobPhsx::InitSingleton();

		Name = Localization::Words_Random;
		Icon = ObjectIcon::RandomIcon;
	}

	const boost::shared_ptr<BobPhsxRandom> &BobPhsxRandom::getInstance()
	{
		return instance;
	}

	boost::shared_ptr<BobPhsx> BobPhsxRandom::ChooseHeroType()
	{
		// FIXME: Check isomorphism.
		return Tools::GlobalRnd->ChooseOne( Bob::HeroTypes );
		//return Tools::GlobalRnd->Choose( Bob::HeroTypes );
	}

	boost::shared_ptr<BobPhsx> BobPhsxRandom::Clone()
	{
		boost::shared_ptr<BobPhsxRandom> newBob = boost::make_shared<BobPhsxRandom>();
			InitBobPhsxSingleton( newBob );
		CopyTo( newBob );
		return boost::static_pointer_cast<BobPhsx>( newBob );
	}

	void BobPhsxRandom::CopyTo( const boost::shared_ptr<BobPhsxRandom> &bob )
	{
		BobPhsx::CopyTo( boost::static_pointer_cast<BobPhsx>( bob ) ); 
	}

	BobPhsxRandom::BobPhsxRandom()
	{
		DefaultValues();
	}
}
