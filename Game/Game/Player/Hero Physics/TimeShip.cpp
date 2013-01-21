#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void BobPhsxTimeship::InitializeStatics()
	{
		BobPhsxTimeship::instance = boost::make_shared<BobPhsxTimeship>();
			InitBobPhsxSingleton( BobPhsxTimeship::instance );
	}

	// Statics
	boost::shared_ptr<BobPhsxTimeship> BobPhsxTimeship::instance;

	float BobPhsxTimeship::KeepUnused( float UpgradeLevel )
	{
		return.5f + .03f * UpgradeLevel;
	}

	void BobPhsxTimeship::InitSingleton()
	{
		BobPhsx::InitSingleton();

		Specification = HeroSpec( 5, 0, 0, 0 );
		Name = Localization::Words_SPACESHIP;
		NameTemplate = std::wstring( L"spaceship" );
		Icon = boost::make_shared<PictureIcon>( Tools::Texture( std::wstring( L"Spaceship_Paper" ) ), Color::White, 1.15f * DefaultIconWidth );
	}

	const boost::shared_ptr<BobPhsxTimeship> &BobPhsxTimeship::getInstance()
	{
		return instance;
	}

	BobPhsxTimeship::BobPhsxTimeship()
	{
		InitializeInstanceFields();
		DefaultValues();
	}

	void BobPhsxTimeship::DefaultValues()
	{
		BobPhsxSpaceship::DefaultValues();
	}

	void BobPhsxTimeship::Init( const boost::shared_ptr<Bob> &bob )
	{
		BobPhsxSpaceship::Init( bob );
	}

	void BobPhsxTimeship::PhsxStep()
	{
		BobPhsxSpaceship::PhsxStep();
	}

	void BobPhsxTimeship::SideHit( ColType side, const boost::shared_ptr<BlockBase> &block )
	{
		BobPhsxSpaceship::SideHit( side, block );
	}

	void BobPhsxTimeship::ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style )
	{
		BobPhsxSpaceship::ModData( makeData, Style );

		Style->TimeType = TimeTypes_Y_SYNC;
	}

	void BobPhsxTimeship::InitializeInstanceFields()
	{
		Dir = 0;
	}
}
