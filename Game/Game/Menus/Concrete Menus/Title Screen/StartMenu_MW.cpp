#include <global_header.h>

namespace CloudberryKingdom
{

	void StartMenu_MW::MenuGo_Options( const std::shared_ptr<MenuItem> &item )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );
		Call( std::make_shared<StartMenu_MW_Options>( getControl(), true ), 0 );
	}

	void StartMenu_MW::Exit()
	{
		SelectSound.reset();
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );
		Call( std::make_shared<StartMenu_MW_Exit>( getControl() ), 0 );
	}

	void StartMenu_MW::BringNextMenu()
	{
		StartMenu::BringNextMenu();

		GUI_Panel::Hide();
	}

	StartMenu_MW::StartMenu_MW( const std::shared_ptr<TitleGameData_MW> &Title ) : StartMenu() { }
	void StartMenu_MW::StartMenu_MW_Construct( const std::shared_ptr<TitleGameData_MW> &Title )
	{
		this->Title = Title;
	}

	void StartMenu_MW::SlideIn( int Frames )
	{
		//Title.BackPanel.SetState(StartMenu_MW_Backpanel.State.Scene_Blur);
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_TITLE );
		StartMenu::SlideIn( 0 );
	}

	void StartMenu_MW::SlideOut( const PresetPos &Preset, int Frames )
	{
		StartMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW::BringCampaign()
	{
		StartMenu::BringCampaign();

		GUI_Panel::Call( std::make_shared<StartMenu_MW_Campaign>( Title ) );
	}

	void StartMenu_MW::BringArcade()
	{
		StartMenu::BringArcade();

		GUI_Panel::Call( std::make_shared<StartMenu_MW_Arcade>( Title ) );
	}

	void StartMenu_MW::BringFreeplay()
	{
		StartMenu::BringFreeplay();

		GUI_Panel::Call( std::make_shared<StartMenu_MW_CustomLevel>( Title ) );
	}

	void StartMenu_MW::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		StartMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
	}

	void StartMenu_MW::OnAdd()
	{
		StartMenu::OnAdd();
	}

	bool StartMenu_MW::MenuReturnToCaller( const std::shared_ptr<Menu> &menu )
	{
		if ( NoBack )
			return false;

		return StartMenu::MenuReturnToCaller( menu );
	}

	void StartMenu_MW::Init()
	{
		 StartMenu::Init();

		CallDelay = ReturnToCallerDelay = 0;
		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		std::shared_ptr<MenuItem> Header = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_MENU, ItemFont ) );
		Header->ScaleText( 1.3f );
		SetItemProperties( Header );
		Header->Selectable = false;
		MyMenu->Add( Header, 0 );
		MyMenu->SelectItem( 1 );

		BackBox = std::make_shared<QuadClass>( _T( "Title_Strip" ) );
		BackBox->setAlpha( .9f );
		MyPile->Add( BackBox, _T( "Back" ) );

		MyPile->FadeIn( .33f );

		//BlackBox();
		SmallBlackBox();
	}

	void StartMenu_MW::BlackBox()
	{
		EnsureFancy();
	}

	void StartMenu_MW::SmallBlackBox()
	{
		BackBox->setTextureName( _T( "White" ) );
		BackBox->Quad_Renamed.SetColor( ColorHelper::Gray( .1f ) );
		BackBox->setAlpha( .73f );

		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 255.5566f, -8.333374f ) );
			_item->MyText->setScale( 0.66f );
			_item->MySelectedText->setScale( 0.66f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Arcade" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2232.778f, 337.7501f ) );
			_item->MyText->setScale( 0.66f );
			_item->MySelectedText->setScale( 0.66f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Campaign" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2233.943f, 149.1946f ) );
			_item->MyText->setScale( 0.66f );
			_item->MySelectedText->setScale( 0.66f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Freeplay" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2156.22f, -34.80548f ) );
			_item->MyText->setScale( 0.66f );
			_item->MySelectedText->setScale( 0.66f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Options" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -2090.221f, -213.25f ) );
			_item->MyText->setScale( 0.66f );
			_item->MySelectedText->setScale( 0.66f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Exit" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1950.778f, -413.5834f ) );
			_item->MyText->setScale( 0.66f );
			_item->MySelectedText->setScale( 0.66f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( 1709.92f, -246.1907f ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Back" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -61.11133f, -336.1111f ) );
			_q->setSize( Vector2( 524.4158f, 524.4158f ) );
		}

		MyPile->setPos( Vector2( -27.77734f, -33.33337f ) );
	}
}
