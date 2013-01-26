#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void BobPhsxSmall::InitializeStatics()
	{
		BobPhsxSmall::instance = boost::make_shared<BobPhsxSmall>();
			InitBobPhsxSingleton( BobPhsxSmall::instance );
	}

	// Statics
	boost::shared_ptr<BobPhsxSmall> BobPhsxSmall::instance;

	void BobPhsxSmall::Set( const boost::shared_ptr<BobPhsx> &phsx )
	{
		Set( phsx, Vector2(1) );
	}

	void BobPhsxSmall::Set( const boost::shared_ptr<BobPhsx> &phsx, Vector2 modsize )
	{
		phsx->ModInitSize = Vector2( .6f ) * modsize;

		phsx->CapePrototype = CapeType_SMALL;
		phsx->CapeOffset += Vector2( 0, -20 );

		boost::shared_ptr<BobPhsxNormal> normal = boost::dynamic_pointer_cast<BobPhsxNormal>( phsx );
		if ( 0 != normal )
		{
			normal->Gravity *= .56f;
			normal->SetAccels();
			normal->ForcedJumpDamping = .85f;
		}
	}

	void BobPhsxSmall::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 1, 0, 0 );
		Name = Localization::Words_TinyBob;
		Adjective = std::wstring( L"tiny" );
		//Icon = new PictureIcon(Tools::TextureWad.FindByName("HeroIcon_Tiny"), Color.White, DefaultIconWidth);
		//Icon = new PictureIcon(Tools::TextureWad.FindByName("HeroIcon_Classic"), Color.White, DefaultIconWidth * .6f);
		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( std::wstring( L"Bob_Run_0024" ) ), Color::White, DefaultIconWidth *.8f );
	}

	const boost::shared_ptr<BobPhsxSmall> &BobPhsxSmall::getInstance()
	{
		return instance;
	}

	BobPhsxSmall::BobPhsxSmall()
	{
		// Pulled out to avoid using shared_from_this inside constructor.
		//Set( shared_from_this() );
		DefaultValues();
	}
}
