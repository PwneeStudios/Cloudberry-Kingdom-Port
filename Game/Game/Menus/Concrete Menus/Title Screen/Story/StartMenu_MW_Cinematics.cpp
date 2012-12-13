#include <global_header.h>

namespace CloudberryKingdom
{

	CinematicsLevelItem::CinematicsLevelItem( const std::shared_ptr<EzText> &Text, const std::wstring &Movie ) : MenuItem( Text )
	{
		InitializeInstanceFields();
		this->Movie = Movie;
	}

	void CinematicsLevelItem::InitializeInstanceFields()
	{
		Movie = _T( "" );
	}

	StartMenu_MW_Cinematics::CinematicsGoLambda::CinematicsGoLambda( const std::shared_ptr<StartMenu_MW_Cinematics> &cine )
	{
		this->cine = cine;
	}

	void StartMenu_MW_Cinematics::CinematicsGoLambda::Apply( const std::shared_ptr<MenuItem> &item )
	{
		cine->Go( item );
	}

	StartMenu_MW_Cinematics::StartMenu_MW_Cinematics( const std::shared_ptr<TitleGameData_MW> &Title ) : StartMenu() { }
	std::shared_ptr<StartMenu_MW_Cinematics> StartMenu_MW_Cinematics::StartMenu_MW_Cinematics_Construct( const std::shared_ptr<TitleGameData_MW> &Title )
	{
		StartMenu::StartMenu_Construct();

		this->Title = Title;
	}

	void StartMenu_MW_Cinematics::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_PRINCESS );

		StartMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Cinematics::SlideOut( const PresetPos &Preset, int Frames )
	{
		StartMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW_Cinematics::SetText( const std::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = ( bColor( 34, 214, 47 ) ).ToVector4();
		text->OutlineColor = ( bColor( 0, 0, 0, 0 ) ).ToVector4();
	}

	void StartMenu_MW_Cinematics::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		StartMenu::SetItemProperties( item );

		SetText( item->MyText );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
		item->MySelectedText->MyFloatColor = ( bColor( 73, 255, 86 ) ).ToVector4();
		item->MySelectedText->OutlineColor = ( bColor( 0, 0, 0, 0 ) ).ToVector4();

		item->MyOscillateParams.Set( 1, 1.01f,.005f );
	}

	void StartMenu_MW_Cinematics::OnAdd()
	{
		StartMenu::OnAdd();
	}

	void StartMenu_MW_Cinematics::Init()
	{
		 StartMenu::Init();

		CallDelay = ReturnToCallerDelay = 0;
		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		MyMenu->ClearList();

		MakeHeader();

		CreateMenu();
	}

	void StartMenu_MW_Cinematics::CreateMenu()
	{
		std::shared_ptr<MenuItem> item;

		// Chapter 1
		item = std::make_shared<CinematicsLevelItem>( std::make_shared<EzText>( _T( "Over the Edge" ), ItemFont ), _T( "Cutscene_1" ) );
		item->Name = _T( "1" );
		item->setGo( std::make_shared<CinematicsGoLambda>( std::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 2
		item = std::make_shared<CinematicsLevelItem>( std::make_shared<EzText>( _T( "Into the Forest" ), ItemFont ), _T( "Cutscene_2" ) );
		item->Name = _T( "2" );
		item->setGo( std::make_shared<CinematicsGoLambda>( std::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 3
		item = std::make_shared<CinematicsLevelItem>( std::make_shared<EzText>( _T( "Woes of a Kidnapper" ), ItemFont ), _T( "Cutscene_3" ) );
		item->Name = _T( "3" );
		item->setGo( std::make_shared<CinematicsGoLambda>( std::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 4
		item = std::make_shared<CinematicsLevelItem>( std::make_shared<EzText>( _T( "Welterweight" ), ItemFont ), _T( "Cutscene_4" ) );
		item->Name = _T( "4" );
		item->setGo( std::make_shared<CinematicsGoLambda>( std::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 5
		item = std::make_shared<CinematicsLevelItem>( std::make_shared<EzText>( _T( "Cloudberry Pie" ), ItemFont ), _T( "Cutscene_5" ) );
		item->Name = _T( "5" );
		item->setGo( std::make_shared<CinematicsGoLambda>( std::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ));
		AddItem( item );

		// Chapter 6
		item = std::make_shared<CinematicsLevelItem>( std::make_shared<EzText>( _T( "I Always Told You" ), ItemFont ), _T( "Cutscene_6" ) );
		item->Name = _T( "6" );
		item->setGo( std::make_shared<CinematicsGoLambda>( std::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		MyMenu->SelectItem( 0 );

		SetPos();
	}

	void StartMenu_MW_Cinematics::MakeHeader()
	{
		std::shared_ptr<EzText> Header = std::make_shared<EzText>( Localization::Words_STORY_MODE, ItemFont );
		Header->Name = _T( "Header" );
		Header->setScale( Header->getScale() * 1.3f );
		SetText( Header );
		Header->OutlineColor = Color::Black.ToVector4();
		MyPile->Add( Header );

		Header->setPos( Vector2( -800.0029f, 863.8889f ) );
	}

	void StartMenu_MW_Cinematics::Go( const std::shared_ptr<MenuItem> &item )
	{
		std::shared_ptr<CinematicsLevelItem> c_item = std::dynamic_pointer_cast<CinematicsLevelItem>( item );
		if ( 0 == c_item )
			return;

		MainVideo::StartVideo_CanSkipIfWatched_OrCanSkipAfterXseconds( c_item->Movie, 1 );
	}

	void StartMenu_MW_Cinematics::SetPos()
	{
	}
}
