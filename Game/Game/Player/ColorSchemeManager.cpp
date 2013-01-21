#include <global_header.h>

#include "Hacks/List.h"

#include <Core\Tools\Set.h>

namespace CloudberryKingdom
{

	void ColorSchemeManager::InitializeStatics()
	{
		ColorSchemeManager::None = boost::make_shared<ClrTextFx>();
	}

	// Statics
	boost::shared_ptr<CapeOnLambda> ColorSchemeManager::CapeOn;
	std::vector<ColorScheme> ColorSchemeManager::ColorSchemes, ColorSchemeManager::ComputerColorSchemes;

	std::vector<boost::shared_ptr<MenuListItem> > ColorSchemeManager::HatList, ColorSchemeManager::ColorList, ColorSchemeManager::CapeColorList, ColorSchemeManager::CapeOutlineColorList, ColorSchemeManager::TextureList, ColorSchemeManager::OutlineList;
	std::vector<boost::shared_ptr<Hat> > ColorSchemeManager::HatInfo;
	std::vector<boost::shared_ptr<Hat> > ColorSchemeManager::BeardInfo;
	std::vector<boost::shared_ptr<MenuListItem> > ColorSchemeManager::ClrList;
	boost::shared_ptr<ClrTextFx> ColorSchemeManager::None;



	CapeOnLambda::CapeOnLambda()
	{
	}

	void CapeOnLambda::Apply( const boost::shared_ptr<Bob> &bob )
	{
		bob->ShowCape = false;

		boost::shared_ptr<ObjectClass> obj = bob->PlayerObject;
		obj->FindQuad( std::wstring( L"Wing1" ) )->Show = false;
		obj->FindQuad( std::wstring( L"Wing2" ) )->Show = false;
		obj->FindQuad( std::wstring( L"DWing1" ) )->Show = false;
		obj->FindQuad( std::wstring( L"DWing2" ) )->Show = false;

		bob->ShowCape = true;
	}

	void ColorSchemeManager::AddScheme( ColorScheme scheme, bool ValidComputerScheme )
	{
		ColorSchemes.push_back( scheme );
		if ( ValidComputerScheme )
			ComputerColorSchemes.push_back( scheme );
	}

	boost::shared_ptr<MenuListItem> ColorSchemeManager::_i( int Guid, int Price, Color Clr, Matrix M, Localization::Words Name )
	{
		return boost::make_shared<MenuListItem>( boost::make_shared<ClrTextFx>( Guid, Price, Clr, M, Name ), Name );
	}

	boost::shared_ptr<MenuListItem> ColorSchemeManager::_i( int Guid, int Price, Color Clr, Color HighlightClr, Matrix M, Localization::Words Name )
	{
		return boost::make_shared<MenuListItem>( boost::make_shared<ClrTextFx>( Guid, Price, Clr, HighlightClr, M, Name ), Name );
	}

	boost::shared_ptr<MenuListItem> ColorSchemeManager::_i( int Guid, int Price, Color Clr, Matrix M, const boost::shared_ptr<EzEffect> &Effect, Localization::Words Name )
	{
		boost::shared_ptr<ClrTextFx> ctf = boost::make_shared<ClrTextFx>( Guid, Price, Clr, M, Name );
		ctf->Effect = Effect;

		return boost::make_shared<MenuListItem>( ctf, Name );
	}

	void ColorSchemeManager::InitColorSchemes()
	{
		ColorList = std::vector<boost::shared_ptr<MenuListItem> >();
		CapeColorList = std::vector<boost::shared_ptr<MenuListItem> >();
		CapeOutlineColorList = std::vector<boost::shared_ptr<MenuListItem> >();
		HatList = std::vector<boost::shared_ptr<MenuListItem> >();
		TextureList = std::vector<boost::shared_ptr<MenuListItem> >();
		OutlineList = std::vector<boost::shared_ptr<MenuListItem> >();

		ColorSchemes = std::vector<ColorScheme>();
		ComputerColorSchemes = std::vector<ColorScheme>();

		HatInfo = std::vector<boost::shared_ptr<Hat> >();
		BeardInfo = std::vector<boost::shared_ptr<Hat> >();

		CapeOn = boost::make_shared<CapeOnLambda>();

		// Fill the beard list
		boost::shared_ptr<Hat> beard;

		Hat::Vandyke = beard = boost::make_shared<Hat>( std::wstring( L"None" ) );
		beard->Name = Localization::Words_VANDYKE;
		beard->Price = Hat::Expensive;
		beard->Guid = 5259001;
		beard->HatPicShift = Vector2();
		BeardInfo.push_back( beard );

		Hat::Beard = beard = boost::make_shared<Hat>( std::wstring( L"Facial_Beard" ) );
		beard->Name = Localization::Words_RUGGED;
		beard->Price = Hat::Expensive;
		beard->Guid = 5259002;
		beard->HatPicShift = Vector2();
		BeardInfo.push_back( beard );

		Hat::Mustache = beard = boost::make_shared<Hat>( std::wstring( L"Facial_Moustache" ) );
		beard->Name = Localization::Words_MANHATTAN;
		beard->Price = Hat::Expensive;
		beard->Guid = 5259003;
		beard->HatPicShift = Vector2();
		BeardInfo.push_back( beard );

		Hat::BigBeard = beard = boost::make_shared<Hat>( std::wstring( L"Facial_BigBeard" ) );
		beard->Name = Localization::Words_LUMBERJACK;
		beard->Price = Hat::Expensive;
		beard->Guid = 5259004;
		beard->HatPicShift = Vector2();
		BeardInfo.push_back( beard );

		Hat::Goatee = beard = boost::make_shared<Hat>( std::wstring( L"Facial_Goatee" ) );
		beard->Name = Localization::Words_GOATEE;
		beard->Price = Hat::Expensive;
		beard->Guid = 5259005;
		beard->HatPicShift = Vector2();
		BeardInfo.push_back( beard );


		// Fill the hat list
		boost::shared_ptr<Hat> hat;
		hat = boost::make_shared<Hat>( std::wstring( L"None" ) );
		hat->Name = Localization::Words_NONE;
		hat->Guid = 19;
			HatInfo.push_back( hat );
			Hat::None = hat;


		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Viking" ) );
		hat->Name = Localization::Words_VIKING;
		hat->Price = Hat::Expensive;
		hat->Guid = 20;
			hat->HatPicShift = Vector2( -.02f,.075f );
			HatInfo.push_back( hat );
			Hat::Viking = hat;
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Fedora" ) );
		hat->Name = Localization::Words_FEDORA;
		hat->Price = Hat::Cheap;
		hat->Guid = 21;
			hat->HatPicScale *= 1.075f;
			HatInfo.push_back( hat );
			Hat::Fedora = hat;
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Afro" ) );
		hat->Name = Localization::Words_AFRO;
		hat->Price = Hat::Mid;
		hat->Guid = 22;
			hat->HatPicScale *= 1.065f;
			HatInfo.push_back( hat );
			Hat::Afro = hat;
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Halo" ) );
		hat->Name = Localization::Words_HALO;
		hat->Price = Hat::Mid;
		hat->Guid = 23;
			hat->HatPicScale *= 1.07f;
			hat->HatPicShift = Vector2( .15f,.08f );
			HatInfo.push_back( hat );
			Hat::Halo = hat;
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_FireHead" ), false );
		hat->Name = Localization::Words_FIREHEAD;
		hat->Price = Hat::Expensive;
		hat->Guid = 24;
			hat->HatPicTexture = Fireball::FlameTexture;
			hat->HatPicScale *= 1.8f;
			HatInfo.push_back( hat );
			Hat::FireHead = hat;
		//hat = new Hat("Hat_Ghost");
		//hat.Name = Localization::Words_Ghost;
		//hat.Price = Hat.Cheap;
		//hat.Guid = 25;
		//    hat.HatPicScale *= .8f;
		//    HatInfo.Add(hat);
		//    Hat.Ghost = hat;
		//hat = new Hat("Hat_CheckpointHead", false);
		//hat.Price = Hat.Mid;
		//hat.Guid = 26;
		//    HatInfo.Add(hat);
		//    Hat.CheckpointHead = hat;
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Horns" ), true, false );
		hat->Name = Localization::Words_HORNS;
		hat->Price = Hat::Mid;
		hat->Guid = 27;
			hat->HatPicTexture = Tools::TextureWad->FindByName( std::wstring( L"HatPic_Horns" ) );
			hat->HatPicScale *= 1.1f;
			HatInfo.push_back( hat );
			Hat::Horns = hat;
		//hat = new Hat("Hat_Cloud");
		//hat.Price = Hat.Mid;
		//hat.Guid = 28;
		//    hat.HatPicScale *= new Vector2(1.45f, 1.85f) * .83f;
		//    HatInfo.Add(hat);
		//    Hat.Cloud = hat;
		//hat = new Hat("", false);
		//hat.Price = Hat.Mid;
		//hat.Guid = 29;
		//    hat.HatPicTexture = Tools::TextureWad.FindByName("QM_Happy");
		//    hat.HatPicScale *= .85f;
		//    HatInfo.Add(hat);
		//    Hat.NoHead = hat;
		//hat = new Hat("Hat_FallingBlockHead", false);
		//hat.Price = Hat.Cheap;
		//hat.Guid = 30;
		//    hat.HatPicScale *= .82f;
		//    HatInfo.Add(hat);
		//    Hat.FallingBlockHead = hat;
		//hat = new Hat("Hat_BlobHead", false);
		//hat.Price = Hat.Mid;
		//hat.Guid = 31;
		//    hat.HatPicScale *= .89f;
		//    HatInfo.Add(hat);
		//    Hat.BlobHead = hat;
		//hat = new Hat("Hat_MovingBlockHead", false);
		//hat.Price = Hat.Cheap;
		//hat.Guid = 32;
		//    hat.HatPicScale *= .89f;
		//    HatInfo.Add(hat);
		//    Hat.MovingBlockHead = hat;
		//hat = new Hat("Hat_SpikeyHead", false);
		//hat.Price = Hat.Mid;
		//hat.Guid = 33;
		//    hat.HatPicScale *= 1.16f;
		//    hat.HatPicShift = new Vector2(-.015f, .2f);
		//    HatInfo.Add(hat);
		//    Hat.SpikeyHead = hat;
		//hat = new Hat("Hat_FallingBlock3Head", false);
		//hat.Price = Hat.Mid;
		//hat.Guid = 34;
		//    hat.HatPicScale *= .82f;
		//    HatInfo.Add(hat);
		//    Hat.FallingBlock3Head = hat;
		//hat = new Hat("Hat_Pink", false);
		//hat.Price = Hat.Cheap;
		//hat.Guid = 35;
		//    hat.HatPicScale *= .95f;
		//    HatInfo.Add(hat);
		//    Hat.Pink = hat;
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Bubble" ), true );
		hat->Name = Localization::Words_BUBBLE;
		hat->DrawHead = false;
		hat->Price = Hat::Mid;
		hat->Guid = 36;
			HatInfo.push_back( hat );
			Hat::Bubble = hat;


	float ScaleNew = 1.35f;
	float DefaultShiftX = -.35f;

		hat = boost::make_shared<Hat>( std::wstring( L"Hat_TopHat" ) );
		hat->Name = Localization::Words_TOP_HAT;
		hat->Price = Hat::Expensive;
		hat->Guid = 37;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.35f;
			HatInfo.push_back( hat );
			Hat::TopHat = hat;
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Knight" ), false );
		hat->Name = Localization::Words_KNIGHT_HELMET;
		hat->Price = Hat::Expensive;
		hat->Guid = 38;
			hat->HatPicShift = Vector2( DefaultShiftX,.105f );
			hat->HatPicScale *= ScaleNew * 1.145f;
			HatInfo.push_back( hat );
			Hat::Knight = hat;

            // Removed due to infringement issues.
            /*
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Toad" ) );
		hat->Name = Localization::Words_MUSHROOM_HAT;
		hat->Price = Hat::Expensive;
		hat->Guid = 39;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.115f;
			HatInfo.push_back( hat );
			Hat::Toad = hat;
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_BubbleBobble" ) );
		hat->Name = Localization::Words_OM_NOM_NOM;
		hat->Price = Hat::Expensive;
		hat->Guid = 40;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.105f;
			HatInfo.push_back( hat );
			Hat::BubbleBobble = hat;
			*/
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Brain" ) );
		hat->DrawHead = false;
		hat->Name = Localization::Words_BRAIN_HAT;
		hat->Price = Hat::Expensive;
		hat->Guid = 41;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.095f;
			hat->AllowsFacialHair = false;
			HatInfo.push_back( hat );
			Hat::Brain = hat;
		hat = boost::make_shared<Hat>( std::wstring( L"Hat_Gosu" ) );
		hat->Name = Localization::Words_GOSU;
		hat->Price = Hat::Expensive;
		hat->Guid = 42;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );
			Hat::Gosu = hat;



		// Buyables
		Hat::RobinHood = hat = boost::make_shared<Hat>( std::wstring( L"Hat_RobinHood" ) );
		hat->Name = Localization::Words_ROBIN_HOOD;
		hat->Price = Hat::Mid;
		hat->Guid = 1;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Rasta = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Rasta" ) );
		hat->Name = Localization::Words_REGGAE;
		hat->Price = Hat::Mid;
		hat->Guid = 2;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Pumpkin = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Pumpkin" ) );
		hat->DrawHead = false;
		hat->Name = Localization::Words_PUMPKIN;
		hat->Price = Hat::Mid;
		hat->Guid = 3;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			hat->AllowsFacialHair = false;
			HatInfo.push_back( hat );

		Hat::Pirate = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Pirate" ) );
		hat->Name = Localization::Words_PIRATE_HAT;
		hat->Price = Hat::Expensive;
		hat->Guid = 4;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Miner = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Miner" ) );
		hat->Name = Localization::Words_HARD_HAT;
		hat->Price = Hat::Cheap;
		hat->Guid = 5;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Glasses = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Glasses" ) );
		hat->Name = Localization::Words_FOUR_EYES;
		hat->Price = Hat::Mid;
		hat->Guid = 6;
			hat->HatPicShift = Vector2( DefaultShiftX,.1f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::BunnyEars = hat = boost::make_shared<Hat>( std::wstring( L"Hat_BunnyEars" ) );
		hat->Name = Localization::Words_BUNNY_EARS;
		hat->Price = Hat::Mid;
		hat->Guid = 7;
			hat->HatPicShift = Vector2( DefaultShiftX, -.135f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		//hat = new Hat("Hat_Beard");
		//hat.Price = Hat.Mid;
		//hat.Guid = 8;
		//    hat.HatPicShift = new Vector2(DefaultShiftX, .435f);
		//    hat.HatPicScale *= ScaleNew * 1.165f;
		//    HatInfo.Add(hat);

		Hat::Antlers = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Antlers" ) );
		hat->Name = Localization::Words_ANTLERS;
		hat->Price = Hat::Mid;
		hat->Guid = 9;
			hat->HatPicShift = Vector2( DefaultShiftX, -.135f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Arrow_Renamed = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Arrow" ) );
		hat->Name = Localization::Words_ARROW_THROUGH_HEAD;
		hat->Price = Hat::Expensive;
		hat->Guid = 10;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Bag = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Bag" ) );
		hat->Name = Localization::Words_BROWN_BAG;
		hat->DrawHead = false;
		hat->Price = Hat::Cheap;
		hat->Guid = 11;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			hat->AllowsFacialHair = false;
			HatInfo.push_back( hat );

		Hat::Cone = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Cone" ) );
		hat->Name = Localization::Words_TRAFFIC_CONE;
		hat->Price = Hat::Cheap;
		hat->Guid = 12;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Pope = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Pope" ) );
		hat->Name = Localization::Words_POPE_HAT;
		hat->Price = Hat::Expensive;
		hat->Guid = 13;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Rice = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Rice" ) );
		hat->Name = Localization::Words_RICE_HAT;
		hat->Price = Hat::Cheap;
		hat->Guid = 14;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Santa = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Santa" ) );
		hat->Name = Localization::Words_SANTA_CLAUS;
		hat->Price = Hat::Expensive;
		hat->Guid = 15;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Sombrero = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Sombrero" ) );
		hat->Name = Localization::Words_SOMBRERO;
		hat->Price = Hat::Cheap;
		hat->Guid = 16;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Tiki = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Tiki" ) );
		hat->DrawHead = false;
		hat->Name = Localization::Words_TIKI_MASK;
		hat->Price = Hat::Mid;
		hat->Guid = 17;
			hat->HatPicShift = Vector2( DefaultShiftX,.075f );
			hat->HatPicScale *= ScaleNew * 1.165f;
			HatInfo.push_back( hat );

		Hat::Wizard = hat = boost::make_shared<Hat>( std::wstring( L"Hat_Wizard" ) );
		hat->Name = Localization::Words_WIZARD;
		hat->Price = Hat::Mid;
		hat->Guid = 18;
			hat->HatPicShift = Vector2( DefaultShiftX, -.015f );
			hat->HatPicScale *= ScaleNew * 1.145f;
			HatInfo.push_back( hat );

		for ( int i = 0; i < static_cast<int>( HatInfo.size() ); i++ )
			HatList.push_back( boost::make_shared<MenuListItem>( 
				boost::static_pointer_cast<Object>( boost::make_shared<WrappedValue<int> >( i ) ),
				Localization::Words_NONE ) );


		//hat = new Hat("Hat_Cattails", true, false);
		//hat.HatPicTexture = Tools::TextureWad.FindByName("HatPic_Horns");
		//HatInfo.Add(hat);


		//colorm = LinearColorTransform(0); // Green
		//colorm = HsvTransform(1.3f, 1.2f, 100); // Gold
		//colorm = HsvTransform(1.5f, 1.5f, 100); // Gold 2
		//colorm = HsvTransform(1.3f, 1.2f, 200); // Hot pink
		//colorm = HsvTransform(1.3f, 1.2f, 250); // ?
		//colorm = HsvTransform(.5f, 0f, 0); // Black
		//colorm = HsvTransform(.15f, 0f, 0); // Dark Black
		//colorm = HsvTransform(.75f, 0f, 0); // Gray
		//colorm = HsvTransform(.8f, 1.3f, 225); // Purple
		//colorm = HsvTransform(.9f, 1.3f, 110); // Orange
		//colorm = LinearColorTransform(45); // Teal
		//colorm = LinearColorTransform(120); // Blue
		//colorm = HsvTransform(.95f, 1.3f, 0) * LinearColorTransform(240); // Red
		//colorm = HsvTransform(1.25f, 1.3f, 0) * LinearColorTransform(305); // Yellow

		// Fill the skin color list
		ColorList.push_back( _i( 3500, 0, Color( 1.f, 1.f, 1.f ), ColorHelper::HsvTransform( 1.25f, 0, 0 ), Localization::Words_WHITE ) ); // 0
		ColorList.push_back( _i( 3501, 0, Color::Silver, ColorHelper::HsvTransform( .85f, 0, 0 ), Localization::Words_SILVER ) ); // 1
		ColorList.push_back( _i( 3502, 0, Color::Gray, ColorHelper::HsvTransform( .525f, 0, 0 ), Localization::Words_GRAY ) ); // 2
		ColorList.push_back( _i( 3503, 0, Color( 0.f, 0.f, 0.f ), Color( static_cast<unsigned char>( 50 ), static_cast<unsigned char>( 50 ), static_cast<unsigned char>( 50 ) ), ColorHelper::HsvTransform( .3f, 0, 0 ), Localization::Words_BLACK ) ); // 3

		ColorList.push_back( _i( 3504, 0, Color::Cyan, ColorHelper::LinearColorTransform( 45 ), Localization::Words_CYAN ) ); // 4
		ColorList.push_back( _i( 3505, 0, Color( 0.f, 0.f, 1.f ), ColorHelper::LinearColorTransform( 120 ), Localization::Words_BLUE ) ); // 5
		ColorList.push_back( _i( 3506, 0, Color::DarkBlue, ColorHelper::LinearColorTransform( 80 ), Localization::Words_TEAL ) ); // 6
		ColorList.push_back( _i( 3507, 0, Color::Indigo, ColorHelper::HsvTransform( .8f, 1.3f, 225 ), Localization::Words_INDIGO ) ); // 7
		ColorList.push_back( _i( 3508, 0, Color::Purple, ColorHelper::HsvTransform( .85f, 1.1f, 205 ), Localization::Words_PURPLE ) ); // 8
		ColorList.push_back( _i( 3509, 0, Color::Brown, ColorHelper::HsvTransform( 1, 1, 80 ), Localization::Words_BROWN ) ); // 9
		ColorList.push_back( _i( 3510, 0, Color( 1.f, 0.f, 0.f ), ColorHelper::HsvTransform( .95f, 1.3f, 0 ) * ColorHelper::LinearColorTransform( 240 ), Localization::Words_RED ) ); // 10
		ColorList.push_back( _i( 3511, 0, Color::HotPink, ColorHelper::HsvTransform( 1.3f, 1.2f, 200 ), Localization::Words_HOT_PINK ) ); // 11
		ColorList.push_back( _i( 3512, 0, Color( 1, .6f, 0 ),ColorHelper::HsvTransform( .9f, 1.3f, 110 ), Localization::Words_ORANGE ) ); // 12
		ColorList.push_back( _i( 3513, 0, Color::Gold, ColorHelper::HsvTransform( 1.3f, 1.2f, 100 ), Localization::Words_GOLD ) ); // 13
		ColorList.push_back( _i( 3514, 0, Color::Yellow, ColorHelper::HsvTransform( 1.5f, 1.5f, 100 ), Localization::Words_YELLOW ) ); // 14
		ColorList.push_back( _i( 3515, 0, Color( 0.f, 1.f, 0.f ), ColorHelper::LinearColorTransform( 0 ), Localization::Words_GREEN ) ); // 15
		ColorList.push_back( _i( 3516, 0, Color::LimeGreen, ColorHelper::HsvTransform( 1.25f, 1.35f, 0 ), Localization::Words_LIME_GREEN ) ); // 16
		ColorList.push_back( _i( 3517, 0, Color::ForestGreen, ColorHelper::HsvTransform( .75f,.8f, 0 ), Localization::Words_FOREST_GREEN ) ); // 17

		ColorList.push_back( _i( 3518, 0, ColorHelper::GrayColor( .2f ), ColorHelper::HsvTransform( 0, 0, 1 ), Localization::Words_NINJA ) ); // 18
		ColorList.push_back( _i( 3519, 0, Color::White, ColorHelper::HsvTransform( 1.75f, 0, 1 ), Localization::Words_BRIGHT_WHITE ) ); // 19



		// Fill the textured skin list
		/*
		TextureList.Add(new MenuListItem(new ClrTextFx(3518, 1500, Color.White, "pillar_xlarge", Color.Gray), "Stone Skin"));     // 0
		TextureList.Add(new MenuListItem(new ClrTextFx(3519, 1000, Color.White, "Skins/Rainbow", Color.Red), "Rainbow Skin"));  // 1
		TextureList.Add(new MenuListItem(new ClrTextFx(3520, 1000, Color.White, "Skins/Tiger", Color.Orange), "Tiger Skin"));      // 2
		TextureList.Add(new MenuListItem(new ClrTextFx(3521, 1000, new Color(1, 1, 1, .66f),
		                                "Skins/Water", Color.LightBlue, "WaterBob"), "Aqua Skin"));                     // 3
		TextureList.Add(new MenuListItem(new ClrTextFx(3522, 1000, Color.White, "Skins/Stars2", Color.DarkBlue), "Star Skin"));      // 4
		TextureList.Add(new MenuListItem(new ClrTextFx(3523, 1000, Color.White, "Skins/Fractal1", Color.Cyan, "WaterBob"),
		                                "Psychadelic Skin"));                                           // 5
	
		 */
		Matrix m = Matrix();
		m.M11 = m.M12 = m.M13 = m.M14 = m.M21 = m.M22 = m.M23 = m.M24 = m.M31 = m.M32 = m.M33 = m.M34 = m.M41 = m.M42 = m.M43 = m.M44 = 0;
		boost::shared_ptr<MenuListItem> NoTexture = _i( 3524, 0, Color::Transparent, m, Localization::Words_CLEAR ); // 6
		TextureList.push_back( NoTexture );


		// Fill the cape color list
		boost::shared_ptr<ClrTextFx> cape;
		None = boost::make_shared<ClrTextFx>( 3525, 0, Color( 1.f, 1.f, 1.f, 0.f ), Matrix::Identity() );
		None->Name = Localization::Words_NONE;
		CapeColorList.push_back( boost::make_shared<MenuListItem>( None, Localization::Words_NONE ) );
		//CapeColorList.AddRange( ColorList );
		AddRange( CapeColorList, ColorList );

		// Fill the outline color list
		//OutlineList.AddRange( CapeColorList );
		AddRange( OutlineList, CapeColorList );
		OutlineList.push_back( NoTexture );

		// Fill the cape outline list
		// FIXME: This could be wrong.  capeoutline used to be a struct and was passed around by value.
		for ( std::vector<boost::shared_ptr<MenuListItem> >::const_iterator item = CapeColorList.begin(); item != CapeColorList.end(); ++item )
		{
			Color clr = ( boost::static_pointer_cast<ClrTextFx>( ( *item )->obj ) )->Clr;
			Color color = Color( clr.ToVector3() * .8f );
			color.A = clr.A;
			boost::shared_ptr<ClrTextFx> capeoutline = boost::static_pointer_cast<ClrTextFx>( ( *item )->obj );
			capeoutline->Clr = color;
			CapeOutlineColorList.push_back( boost::make_shared<MenuListItem>( capeoutline, ( *item )->word ) );
		}

		// Add textures to skin color list and cape color list
		//ColorList.AddRange( TextureList );
		AddRange( ColorList, TextureList );
		//CapeColorList.AddRange( TextureList );
		AddRange( CapeColorList, TextureList );
		//CapeColorList.Remove( NoTexture );
		Remove( CapeColorList, NoTexture );

		ClrTextFx fx;
		Vector2 fx_scale = Vector2( .875f, 1.195f ) *.98f;

		//fx = new ClrTextFx(3526, 500, Color.White, "FallingBlock2", false, "FallingBlock2");
		//fx.Name = "Concern;
		//fx.PicScale = fx_scale;
		//CapeColorList.Add(new MenuListItem(fx, "ConcernedCape"));

		//fx = new ClrTextFx(3527, 500, Color.White, "FallingBlock3", false, "FallingBlock3");
		//fx.Name = "AAAaahhh!;
		//fx.PicScale = fx_scale;
		//CapeColorList.Add(new MenuListItem(fx, "ScreamingCape"));

		//fx = new ClrTextFx(3528, 500, Color.White, "Capes/FallingBlock4Cape", false, "FallingBlock4");
		//fx.Name = "Anger;
		//fx.PicScale = fx_scale * new Vector2(1.022f, 1.028f);
		//CapeColorList.Add(new MenuListItem(fx, "AngryCape"));

		// Wings and cape mod functions
		std::vector<boost::shared_ptr<MenuListItem> > NewCapeList = std::vector<boost::shared_ptr<MenuListItem> >();
		for ( std::vector<boost::shared_ptr<MenuListItem> >::const_iterator item = CapeColorList.begin(); item != CapeColorList.end(); ++item )
		{
			cape = boost::static_pointer_cast<ClrTextFx>( ( *item )->obj );
			cape->ModObject = CapeOn;
			NewCapeList.push_back( boost::make_shared<MenuListItem>( cape, ( *item )->word ) );
		}
		CapeColorList = NewCapeList;

		// Combine all colors
		std::vector<boost::shared_ptr<MenuListItem> > temp;
		temp = std::vector<boost::shared_ptr<MenuListItem> >();
		//temp.AddRange( ColorList );
		AddRange( temp, ColorList );
		//temp.AddRange( CapeColorList );
		AddRange( temp, CapeColorList );
		//temp.AddRange( CapeOutlineColorList );
		AddRange( temp, CapeOutlineColorList );
		//temp.AddRange( OutlineList );
		AddRange( temp, OutlineList );
		ClrList = MakeUnique( temp );

		// Create the default color schemes
		AddScheme( ColorScheme( Localization::Words_GREEN, Localization::Words_RED, Localization::Words_BLACK, Localization::Words_NONE, Localization::Words_NONE ), true );
		AddScheme( ColorScheme( Localization::Words_HOT_PINK, Localization::Words_HOT_PINK, Localization::Words_HOT_PINK, Hat::BunnyEars->Name, Hat::Beard->Name ), false );
		AddScheme( ColorScheme( Localization::Words_GOLD, Localization::Words_GOLD, Localization::Words_GOLD, Localization::Words_NONE, Localization::Words_NONE ), false );
		AddScheme( ColorScheme( Localization::Words_PURPLE, Localization::Words_INDIGO, Localization::Words_HOT_PINK, Localization::Words_NONE, Localization::Words_VANDYKE ), false );
		AddScheme( ColorScheme( Localization::Words_FOREST_GREEN, Localization::Words_YELLOW, Localization::Words_GOLD, Localization::Words_RICE_HAT, Localization::Words_RUGGED ), false );
		AddScheme( ColorScheme( Localization::Words_RED, Localization::Words_NONE, Localization::Words_NONE, Localization::Words_ANTLERS, Localization::Words_VANDYKE ), false );
        AddScheme( ColorScheme(Localization::Words_GRAY, Localization::Words_RED, Localization::Words_BLACK, Localization::Words_NONE, Hat::Mustache->Name ), false);
        AddScheme( ColorScheme(Localization::Words_INDIGO, Localization::Words_CYAN, Localization::Words_SILVER, Localization::Words_WIZARD, Localization::Words_VANDYKE ), false);
        AddScheme( ColorScheme(Localization::Words_NINJA, Localization::Words_WHITE, Localization::Words_BLACK, Localization::Words_PUMPKIN, Localization::Words_MANHATTAN ), false);
        AddScheme( ColorScheme(Localization::Words_FOREST_GREEN, Localization::Words_FOREST_GREEN, Localization::Words_FOREST_GREEN, Localization::Words_ROBIN_HOOD, Localization::Words_VANDYKE ), false);
        AddScheme( ColorScheme(Localization::Words_SILVER, Localization::Words_GRAY, Localization::Words_GRAY, Localization::Words_KNIGHT_HELMET, Localization::Words_LUMBERJACK ), false);
	}

	std::vector<boost::shared_ptr<MenuListItem> > ColorSchemeManager::MakeUnique( std::vector<boost::shared_ptr<MenuListItem> > &list )
	{
		boost::shared_ptr<Set<int> > guids = boost::make_shared<Set<int> >();
		std::vector<boost::shared_ptr<MenuListItem> > uniques = std::vector<boost::shared_ptr<MenuListItem> >();

		for ( std::vector<boost::shared_ptr<MenuListItem> >::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			int guid = ( boost::static_pointer_cast<ClrTextFx>( ( *item )->obj ) )->Guid;

			if ( guids->Contains( guid ) )
				continue;
			else
				uniques.push_back( *item );
		}

		return uniques;
	}
}
