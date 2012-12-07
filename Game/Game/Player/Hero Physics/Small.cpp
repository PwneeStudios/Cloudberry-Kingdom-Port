#include <global_header.h>



namespace CloudberryKingdom
{

	void BobPhsxSmall::Set( const std::shared_ptr<BobPhsx> &phsx )
	{
		Set( phsx, Vector2(1) );
	}

	void BobPhsxSmall::Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize )
	{
		phsx->ModInitSize = Vector2( .6f ) * modsize;

		phsx->CapePrototype = CapeType_SMALL;
		phsx->CapeOffset += Vector2( 0, -20 );

		std::shared_ptr<BobPhsxNormal> normal = std::dynamic_pointer_cast<BobPhsxNormal>( phsx );
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
		Name = Localization::Words_TINY_BOB;
		Adjective = _T( "tiny" );
		//Icon = new PictureIcon(Tools.TextureWad.FindByName("HeroIcon_Tiny"), Color.White, DefaultIconWidth);
		//Icon = new PictureIcon(Tools.TextureWad.FindByName("HeroIcon_Classic"), Color.White, DefaultIconWidth * .6f);
		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "Bob_Run_0024" ) ), Color::White, DefaultIconWidth *.8f );
	}

const std::shared_ptr<BobPhsxSmall> BobPhsxSmall::instance = std::make_shared<BobPhsxSmall>();

	const std::shared_ptr<BobPhsxSmall> &BobPhsxSmall::getInstance()
	{
		return instance;
	}

	BobPhsxSmall::BobPhsxSmall()
	{
		Set( shared_from_this() );
	}
}
