#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu_MW_Arcade::StartMenu_MW_Arcade( const std::shared_ptr<TitleGameData_MW> &Title ) : ArcadeMenu() { }
	std::shared_ptr<StartMenu_MW_Arcade> StartMenu_MW_Arcade::StartMenu_MW_Arcade_Construct( const std::shared_ptr<TitleGameData_MW> &Title )
	{
		ArcadeMenu::ArcadeMenu_Construct();

		this->Title = Title;
	}

	void StartMenu_MW_Arcade::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_KOBBLER );
		ArcadeMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Arcade::SlideOut( const PresetPos &Preset, int Frames )
	{
		ArcadeMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW_Arcade::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		ArcadeMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;

		StartMenu::SetItemProperties_Green( item, false );

		item->MySelectedText->setScale( 1 );
	item->MyText->setScale( item->MySelectedText->getScale() );
	}

	void StartMenu_MW_Arcade::Go( const std::shared_ptr<MenuItem> &item )
	{
		MyArcadeItem = std::dynamic_pointer_cast<ArcadeItem>( item );
		if ( MyArcadeItem->Locked )
			return;

		if ( MyArcadeItem->MyChallenge == Challenge_Escalation::getInstance() || MyArcadeItem->MyChallenge == Challenge_TimeCrisis::getInstance() )
		{
			GUI_Panel::Call( MakeMagic( StartMenu_MW_HeroSelect, ( Title, std::static_pointer_cast<ArcadeMenu>( shared_from_this() ), MyArcadeItem ) ) );
		}
		else
		{
			Challenge::ChosenHero.reset();
			std::shared_ptr<StartLevelMenu> levelmenu = MakeMagic( StartLevelMenu, ( MyArcadeItem->MyChallenge->TopLevel() ) );

			levelmenu->MyMenu->SelectItem( StartLevelMenu::PreviousMenuIndex );
			levelmenu->StartFunc = std::make_shared<StartFuncProxy>( std::static_pointer_cast<ArcadeBaseMenu>( shared_from_this() ) );
			levelmenu->ReturnFunc.reset();

			GUI_Panel::Call( levelmenu );
		}

		Hide();
	}

	void StartMenu_MW_Arcade::OnAdd()
	{
		ArcadeMenu::OnAdd();
	}

	void StartMenu_MW_Arcade::Init()
	{
		 ArcadeMenu::Init();

		CallDelay = ReturnToCallerDelay = 0;
		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		SetPos();
	}

	void StartMenu_MW_Arcade::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Header" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2771.113f, 901.9052f ) );
			_item->MyText->setScale( 1.960415f );
			_item->MySelectedText->setScale( 1 );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( -2490.635f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Escalation" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2458.969f, 320.413f ) );
			_item->MyText->setScale( 1 );
			_item->MySelectedText->setScale( 1 );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( -2490.635f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Time Crisis" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2467.301f, 117.0817f ) );
			_item->MyText->setScale( 1 );
			_item->MySelectedText->setScale( 1 );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( -2490.635f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Hero Rush" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2456.189f, -97.36035f ) );
			_item->MyText->setScale( 1 );
			_item->MySelectedText->setScale( 1 );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( -2490.635f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Hero Rush 2" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2472.857f, -297.9135f ) );
			_item->MyText->setScale( 1 );
			_item->MySelectedText->setScale( 1 );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( -2490.635f, -1 ) );
		}

		MyMenu->setPos( Vector2( 1070.889f, -45.5556f ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -290.4752f, -2200.793f ) );
			_q->setSize( Vector2( 1234.721f, 740.8326f ) );
		}

		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
	}
}
