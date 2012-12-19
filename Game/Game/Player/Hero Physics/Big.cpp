#include <global_header.h>

namespace CloudberryKingdom
{

	void BobPhsxBig::InitializeStatics()
	{
		BobPhsxBig::instance = boost::make_shared<BobPhsxBig>();
	}

	// Statics
	boost::shared_ptr<BobPhsxBig> BobPhsxBig::instance;


	void BobPhsxBig::Set( const boost::shared_ptr<BobPhsx> &phsx )
	{
		if ( boost::dynamic_pointer_cast<BobPhsxWheel>( phsx ) != 0 )
			phsx->ModInitSize = Vector2( 1.45f );
		else
			phsx->ModInitSize = Vector2( 1.7f, 1.4f );

		phsx->CapePrototype = CapeType_NORMAL;
		phsx->CapeOffset += Vector2( 0, -20 );

		boost::shared_ptr<BobPhsxNormal> normal = boost::dynamic_pointer_cast<BobPhsxNormal>( phsx );
		if ( 0 != normal )
		{
			normal->Gravity *= 1.55f;
			normal->SetAccels();

			normal->Gravity *= .935f;
			normal->MaxSpeed *= 1.5f;
			normal->XAccel *= 1.5f;
		}
	}

	void BobPhsxBig::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 3, 0, 0 );
		Name = Localization::Words_FAT_BOB;
		Adjective = std::wstring( L"Fatty" );

		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( std::wstring( L"Bob_Run_0024" ) ), Color::White, DefaultIconWidth * 1.55f );
	}

	const boost::shared_ptr<BobPhsxBig> &BobPhsxBig::getInstance()
	{
		return instance;
	}

	BobPhsxBig::BobPhsxBig()
	{
		// Pulled out to avoid using shared_from_this inside constructor.
		//Set( shared_from_this() );
	}
}
