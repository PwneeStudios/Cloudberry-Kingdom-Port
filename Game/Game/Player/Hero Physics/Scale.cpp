#include <global_header.h>

namespace CloudberryKingdom
{

	void BobPhsxScale::InitializeStatics()
	{
		BobPhsxScale::instance = boost::make_shared<BobPhsxScale>();
	}

	// Statics
	boost::shared_ptr<BobPhsxScale> BobPhsxScale::instance;

	void BobPhsxScale::Set( const boost::shared_ptr<BobPhsx> &phsx )
	{
		phsx->Oscillate_Renamed = true;
		phsx->ForceDown = -7.5f;
		phsx->CapePrototype = CapeType_NORMAL;

		phsx->DollCamZoomMod = .535f;
	}

	void BobPhsxScale::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 2, 0, 0 );
		Name = Localization::Words_PHASE_BOB;
		Adjective = _T( "phasing" );
		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "HeroIcon_Phase" ) ), Color::White, 1.1f * DefaultIconWidth );
	}

	const boost::shared_ptr<BobPhsxScale> &BobPhsxScale::getInstance()
	{
		return instance;
	}

	BobPhsxScale::BobPhsxScale()
	{
		// Pulled out to avoid using shared_from_this inside constructor.
		//Set( shared_from_this() );
	}
}
