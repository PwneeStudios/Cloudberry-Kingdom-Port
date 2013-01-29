#include <global_header.h>

#include <Core\Tools\Set.h>

#include <Game\Video.h>

namespace CloudberryKingdom
{

	CinematicsLevelItem::CinematicsLevelItem( const boost::shared_ptr<EzText> &Text, const std::wstring &Movie ) : MenuItem( Text )
	{
		InitializeInstanceFields();
	}
	boost::shared_ptr<CinematicsLevelItem> CinematicsLevelItem::CinematicsLevelItem_Construct( const boost::shared_ptr<EzText> &Text, const std::wstring &Movie )
	{
		MenuItem::MenuItem_Construct( Text );

		this->Movie = Movie;

		return boost::static_pointer_cast<CinematicsLevelItem>( shared_from_this() );
	}

	void CinematicsLevelItem::InitializeInstanceFields()
	{
		Movie = std::wstring( L"" );
	}

	StartMenu_MW_Cinematics::CinematicsGoLambda::CinematicsGoLambda( const boost::shared_ptr<StartMenu_MW_Cinematics> &cine )
	{
		this->cine = cine;
	}

	void StartMenu_MW_Cinematics::CinematicsGoLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		cine->Go( item );
	}

	StartMenu_MW_Cinematics::StartMenu_MW_Cinematics( const boost::shared_ptr<TitleGameData_MW> &Title ) : StartMenu() { }
	boost::shared_ptr<StartMenu_MW_Cinematics> StartMenu_MW_Cinematics::StartMenu_MW_Cinematics_Construct( const boost::shared_ptr<TitleGameData_MW> &Title )
	{
		StartMenu::StartMenu_Construct();

		this->Title = Title;

		return boost::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() );
	}

	void StartMenu_MW_Cinematics::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_PRINCESS );

		StartMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Cinematics::SlideOut( PresetPos Preset, int Frames )
	{
		StartMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW_Cinematics::SetText( const boost::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = ( bColor( 34, 214, 47 ) ).ToVector4();
		text->OutlineColor = ( bColor( 0, 0, 0, 0 ) ).ToVector4();
	}

	void StartMenu_MW_Cinematics::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
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
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		MyMenu->ClearList();

		MakeHeader();

		CreateMenu();
	}

	void StartMenu_MW_Cinematics::CreateMenu()
	{
		boost::shared_ptr<MenuItem> item;

		// Chapter 1
		item = MakeMagic( CinematicsLevelItem, ( boost::make_shared<EzText>( std::wstring( L"Over the Edge" ), ItemFont ), std::wstring( L"Cutscene_1" ) ) );
		item->Name = std::wstring( L"1" );
		item->setGo( boost::make_shared<CinematicsGoLambda>( boost::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 2
		item = MakeMagic( CinematicsLevelItem, ( boost::make_shared<EzText>( std::wstring( L"Into the Forest" ), ItemFont ), std::wstring( L"Cutscene_2" ) ) );
		item->Name = std::wstring( L"2" );
		item->setGo( boost::make_shared<CinematicsGoLambda>( boost::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 3
		item = MakeMagic( CinematicsLevelItem, ( boost::make_shared<EzText>( std::wstring( L"Woes of a Kidnapper" ), ItemFont ), std::wstring( L"Cutscene_3" ) ) );
		item->Name = std::wstring( L"3" );
		item->setGo( boost::make_shared<CinematicsGoLambda>( boost::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 4
		item = MakeMagic( CinematicsLevelItem, ( boost::make_shared<EzText>( std::wstring( L"Welterweight" ), ItemFont ), std::wstring( L"Cutscene_4" ) ) );
		item->Name = std::wstring( L"4" );
		item->setGo( boost::make_shared<CinematicsGoLambda>( boost::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 5
		item = MakeMagic( CinematicsLevelItem, ( boost::make_shared<EzText>( std::wstring( L"Cloudberry Pie" ), ItemFont ), std::wstring( L"Cutscene_5" ) ) );
		item->Name = std::wstring( L"5" );
		item->setGo( boost::make_shared<CinematicsGoLambda>( boost::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ));
		AddItem( item );

		// Chapter 6
		item = MakeMagic( CinematicsLevelItem, ( boost::make_shared<EzText>( std::wstring( L"I Always Told You" ), ItemFont ), std::wstring( L"Cutscene_6" ) ) );
		item->Name = std::wstring( L"6" );
		item->setGo( boost::make_shared<CinematicsGoLambda>( boost::static_pointer_cast<StartMenu_MW_Cinematics>( shared_from_this() ) ) );
		AddItem( item );

		MyMenu->SelectItem( 0 );

		SetPos();
	}

	void StartMenu_MW_Cinematics::MakeHeader()
	{
		boost::shared_ptr<EzText> Header = boost::make_shared<EzText>( Localization::Words_StoryMode, ItemFont );
		Header->Name = std::wstring( L"Header" );
		Header->setScale( Header->getScale() * 1.3f );
		SetText( Header );
		Header->OutlineColor = Color::Black.ToVector4();
		MyPile->Add( Header );

		Header->setPos( Vector2( -800.0029f, 863.8889f ) );
	}

	void StartMenu_MW_Cinematics::Go( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<CinematicsLevelItem> c_item = boost::dynamic_pointer_cast<CinematicsLevelItem>( item );
		if ( 0 == c_item )
			return;

		MainVideo::StartVideo_CanSkipIfWatched_OrCanSkipAfterXseconds( c_item->Movie, 1 );
	}

	void StartMenu_MW_Cinematics::SetPos()
	{
	}
}
