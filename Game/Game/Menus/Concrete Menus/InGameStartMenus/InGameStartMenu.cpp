#include <global_header.h>

#include <Core\Tools\Set.h>

#include "Game/Menus/Concrete Menus/ShopMenu.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	InGameStartMenu::UnpauseLambda::UnpauseLambda( boost::shared_ptr<InGameStartMenu> igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::UnpauseLambda::Apply()
	{
		igsm->Unpause();
	}

	boost::shared_ptr<GUI_Panel> InGameStartMenu::MakeListenerHelper::Apply( const boost::shared_ptr<Listener> &listener )
	{
		return MakeMagic( InGameStartMenu, ( listener->TriggeringPlayerIndex ) );
	}

	InGameStartMenu::PreventMenuHelper::PreventMenuHelper( const boost::shared_ptr<Listener> &listener, const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > &Make )
	{
		this->listener = listener;
		this->Make = Make;
	}

	void InGameStartMenu::PreventMenuHelper::Apply()
	{
		if ( !InGameStartMenu::PreventMenu )
			listener->Call( Make->Apply( listener ) );
	}

	InGameStartMenu::GoRemoveProxy::GoRemoveProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoRemoveProxy::Apply()
	{
		igsm->GoRemove();
	}

	InGameStartMenu::GoControlsHelper::GoControlsHelper( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoControlsHelper::Apply()
	{
		igsm->Hide( PresetPos_LEFT, 40 );
		igsm->setPauseGame( true );
	}

	InGameStartMenu::GoControlsProxy::GoControlsProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoControlsProxy::Apply()
	{
		igsm->GoControls();
	}

	InGameStartMenu::GoOptionsProxy::GoOptionsProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoOptionsProxy::Apply()
	{
		igsm->GoOptions();
	}

	InGameStartMenu::GoSaveLoadProxy::GoSaveLoadProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoSaveLoadProxy::Apply()
	{
		igsm->GoSaveLoad();
	}

	InGameStartMenu::GoStatsProxy::GoStatsProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoStatsProxy::Apply()
	{
		igsm->GoStats();
	}

	InGameStartMenu::VerifyExitProxy::VerifyExitProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::VerifyExitProxy::Apply()
	{
		igsm->VerifyExit();
	}

bool InGameStartMenu::PreventMenu = false;
	

	InGameStartMenu::InGameStartMenu( int Control ) : CkBaseMenu( false )
	{
		CenterItems = false;
	}
	boost::shared_ptr<InGameStartMenu> InGameStartMenu::InGameStartMenu_Construct( int Control )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		EnableBounce();

		this->setControl( Control );

		Constructor();

		return boost::static_pointer_cast<InGameStartMenu>( shared_from_this() );
	}

	boost::shared_ptr<GameObject> InGameStartMenu::MakeListener()
	{
		return MakeListener_Base( boost::make_shared<MakeListenerHelper>() );
	}

	boost::shared_ptr<GameObject> InGameStartMenu::MakeListener_Base( const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > &Make )
	{
		boost::shared_ptr<Listener> listener = MakeMagic( Listener, () );
		listener->MyButton = ControllerButtons_START;

		listener->Tags->Add( GameObject::Tag_REMOVE_ON_LEVEL_FINISH );

		listener->MyAction = boost::make_shared<PreventMenuHelper>( listener, Make );

		return listener;
	}

	void InGameStartMenu::OnAdd()
    {
		CkBaseMenu::OnAdd();

        MyMenu->setControl( getControl() );
    }

	void InGameStartMenu::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->setScale( FontScale * 1.45f );
	}

	void InGameStartMenu::OnReturnTo()
	{
		CkBaseMenu::OnReturnTo();

		if ( MyMenu->getCurItem() == RemoveMe && VerifyRemoveMenu::YesChosen )
			ReturnToCaller( false );
	}

	void InGameStartMenu::Init()
	{
		CkBaseMenu::Init();

		setPauseGame( true );

		CallDelay = 15;

		FontScale = .775f;

		MyPile = boost::make_shared<DrawPile>();

		this->CallDelay = 5;
		this->setSlideLength( 14 );
		this->SelectedItemShift = Vector2( 0, 0 );

		MakeDarkBack();

		// Make the backdrop
        boost::shared_ptr<QuadClass> backdrop;
        if (UseSimpleBackdrop)
		{
            backdrop = boost::make_shared<QuadClass>( L"Arcade_BoxLeft", 1500.0f, true );
			backdrop->Name = L"Backdrop";
		}
        else
		{
            backdrop = boost::make_shared<QuadClass>( L"Backplate_1080x840", 1500.0f, true );		
			backdrop->Name = L"Backdrop";
		}
		
		backdrop->Name = L"Backdrop";

		MyPile->Add( backdrop );

		if ( !UseSimpleBackdrop )
		{
			EpilepsySafe( .9f );
		}
		backdrop->setPos( Vector2( -975.6945f, 54.86111f ) );

		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );

		MyMenu->OnB.reset();

		boost::shared_ptr<MenuItem> item;


		ItemPos = Vector2( -1560.333f, 600 );
		PosAdd = Vector2( 0, -270 );

		bool RemoveMeOption = false;
		if ( PlayerManager::GetNumPlayers() > 1 && getControl() >= 0 )
		{
			RemoveMeOption = true;
			PosAdd.Y += 44;
		}

		// Resume
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Resume, ItemFont, CenterItems ) ) );
		item->Name = std::wstring( L"Resume" );
		item->setGo( Cast::ToItem( boost::make_shared<ReturnToCallerProxy>( boost::static_pointer_cast<CkBaseMenu>( shared_from_this() ) ) ) );
		item->MyText->setScale( item->MyText->getScale() * 1.1f );
		item->MySelectedText->setScale( item->MySelectedText->getScale() * 1.1f );
		AddItem( item );
		item->SelectSound.reset();


		// Statistics
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Statistics, ItemFont, CenterItems ) ) );
		item->Name = std::wstring( L"Stats" );
		item->setGo( Cast::ToItem( boost::make_shared<GoStatsProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
		AddItem( item );

		// SaveLoadSeed
		Localization::Words word = Tools::CurLevel->CanLoadLevels ? Localization::Words_SaveLoad : Localization::Words_SaveSeed;
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( word, ItemFont, CenterItems ) ) );
		item->Name = std::wstring( L"SaveLoadSeed" );
		item->setGo( Cast::ToItem( boost::make_shared<GoSaveLoadProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
		if ( !Tools::CurLevel->CanLoadLevels && !Tools::CurLevel->CanSaveLevel )
		{
			item->Selectable = false;
			item->GrayOut();
		}
		AddItem( item );

		// Options
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Options, ItemFont, CenterItems ) ) );
		item->Name = std::wstring( L"Options" );
		item->setGo( Cast::ToItem( boost::make_shared<GoOptionsProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
		AddItem( item );

		//// Controls
		//item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Controls, ItemFont, CenterItems ) ) );
		//item->Name = std::wstring( L"Controls" );
		//item->setGo( Cast::ToItem( boost::make_shared<GoControlsProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
		//AddItem( item );

		// Remove player
		if ( RemoveMeOption )
		{
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_RemoveMe, ItemFont, CenterItems ) ) );
			item->Name = std::wstring( L"Remove" );
			item->setGo( Cast::ToItem( boost::make_shared<GoRemoveProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
			AddItem( item );
			RemoveMe = item;
		}

		// Exit level
		MakeExitItem();

		// Button interactions
		MyMenu->OnStart = MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Shift everything
		EnsureFancy();
		Shift( Vector2( 1045.139f, -10.41669f ) );

        if ( RemoveMeOption )
            SetPos_WithRemoveMe();
        else
            SetPos();

		MyMenu->SortByHeight();
		MyMenu->SelectItem( 0 );
	}

        bool InGameStartMenu::MenuReturnToCaller( boost::shared_ptr<Menu> menu )
        {
			//getMyLevel()->ReplayPaused = true;

   //         HoldLevel = getMyLevel();
   //         MyGame->WaitThenDo( 7, boost::make_shared<UnpauseLambda>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) );

            return CkBaseMenu::MenuReturnToCaller( menu );
        }

        boost::shared_ptr<Level> HoldLevel;
        void InGameStartMenu::Unpause()
        {
            if ( HoldLevel != 0 ) HoldLevel->ReplayPaused = false;
            HoldLevel.reset();
        }

		//protected override void ReleaseBody()
		//{
		//	base.ReleaseBody();

		//	HoldLevel = null;
		//}

	void InGameStartMenu::GoRemove()
	{
		boost::shared_ptr<VerifyRemoveMenu> verify = MakeMagic( VerifyRemoveMenu, ( getControl() ) );
		GUI_Panel::Call( verify );
		
        if (UseBounce)
        {
            Hid = true;
            RegularSlideOut( PresetPos_RIGHT, 0 );
        }
        else
        {		
			Hide( PresetPos_LEFT );
		}

		setPauseGame( true );
	}

	void InGameStartMenu::GoControls()
	{
        if (UseBounce)
        {
            Hid = true;
            RegularSlideOut( PresetPos_RIGHT, 0 );
        }
        else
        {
			MyGame->WaitThenDo( 4, boost::make_shared<GoControlsHelper>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) );
		}

		boost::shared_ptr<ControlScreen> screen = MakeMagic( ControlScreen, ( getControl() ) );
		Call( screen, 22 );
	}

	void InGameStartMenu::GoOptions()
	{
		Call( MakeMagic( SoundMenu, ( getControl(), false ) ), 0 );

        if (UseBounce)
        {
            Hid = true;
            RegularSlideOut( PresetPos_RIGHT, 0 );
        }
        else
        {
			Hide( PresetPos_LEFT );
		}

		setPauseGame( true );
	}

	void InGameStartMenu::GoSaveLoad()
	{
        if ( CloudberryKingdomGame::getIsDemo() )
        {
            Call( MakeMagic( UpSellMenu, ( Localization::Words_UpSell_SaveLoad, MenuItem::ActivatingPlayer ) ), 0);
        }
        else
        {
#if XBOX
			PlayerData player = MenuItem.GetActivatingPlayerData();

            //if (CloudberryKingdomGame.CanSave() && EzStorage.Device[(int)player.MyIndex] != null &&
            //    !EzStorage.Device[(int)player.MyIndex].IsReady)
            //{
            //    EzStorage.Device[(int)player.MyIndex].state = EasyStorage.SaveDevicePromptState.PromptForCanceled;
            //    return;
            //}

            if (!CloudberryKingdomGame.CanSave(player.MyPlayerIndex))
            {
                CloudberryKingdomGame.ShowError_CanNotSaveNoDevice();
                return;
            }
#endif

			// If this isn't a PC, and we can't load seeds right now, then go directly to the SaveAs menu.
		#if !defined(PC_VERSION)
			if ( !getMyLevel()->CanLoadLevels )
			{
				Call( MakeMagic( SaveSeedAs, ( getControl(), MenuItem::GetActivatingPlayerData() ) ), 0 );
			}
			else
		#endif
			{
		#if defined(PC_VERSION)
				Call( MakeMagic( SaveLoadSeedMenu, ( getControl(), getMyLevel()->CanLoadLevels, getMyLevel()->CanSaveLevel ) ), 0 );
		#else
				Call( MakeMagic( SaveLoadSeedMenu, ( getControl(), getMyLevel()->CanLoadLevels, getMyLevel()->CanSaveLevel ) ), 0 );
		#endif
			}
		}

        if ( UseBounce )
        {
            Hid = true;
            RegularSlideOut( PresetPos_RIGHT, 0 );
        }
        else
        {
			Hide( PresetPos_LEFT );
		}

		setPauseGame( true );
	}

	void InGameStartMenu::GoStats()
	{
		Call( MakeMagic( StatsMenu, ( StatGroup_LIFETIME ) ), UseBounce ? 0 : 19 );
		
        if (UseBounce)
        {
            Hid = true;
            RegularSlideOut( PresetPos_RIGHT, 0 );
        }
        else
        {		
			Hide( PresetPos_LEFT );
		}

		setPauseGame( true );
	}

    void InGameStartMenu::SetPos()
    {
        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"Resume" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1501.999f, 708.3334f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
        _item = MyMenu->FindItemByName( L"Stats" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1504.778f, 469.9999f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
        _item = MyMenu->FindItemByName( L"SaveLoadSeed" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1504.777f, 231.6667f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
        _item = MyMenu->FindItemByName( L"Options" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1496.443f, -3.88887f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
        _item = MyMenu->FindItemByName( L"Exit" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1496.444f, -252.7777f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }

        MyMenu->setPos( Vector2(1109.028f, -40.97224f) );

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"Backdrop" ); if ( _q != 0 ) { _q->setPos( Vector2(-972.9169f, 29.86109f) ); _q->setSize( Vector2(1132.148f, 880.288f) ); }

        MyPile->setPos( Vector2(995.1394f, -13.19449f) );
    }

    void InGameStartMenu::SetPos_WithRemoveMe()
    {
        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"Resume" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1501.999f, 708.3334f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
        _item = MyMenu->FindItemByName( L"Stats" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1504.778f, 469.9999f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
        _item = MyMenu->FindItemByName( L"SaveLoadSeed" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1504.777f, 231.6667f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
        _item = MyMenu->FindItemByName( L"Options" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1496.443f, -3.88887f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
        _item = MyMenu->FindItemByName( L"Exit" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1488.11f, -488.8888f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
        _item = MyMenu->FindItemByName( L"Remove" ); if ( _item != 0 ) { _item->setSetPos( Vector2(-1488.11f, -249.4445f) ); _item->MyText->setScale( 0.775f ); _item->MySelectedText->setScale( 0.775f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }

        MyMenu->setPos( Vector2(1106.25f, 50.69439f) );

        boost::shared_ptr<EzText> _t;
        _t = MyPile->FindEzText( L"Header" ); if ( _t != 0 ) { _t->setPos( Vector2(-1463.89f, 1474.667f) ); _t->setScale( 1.12375f ); }

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"Dark" ); if ( _q != 0 ) { _q->setPos( Vector2(0.f, 0.f) ); _q->setSize( Vector2(8888.889f, 5000.f) ); }
        _q = MyPile->FindQuad( L"Backdrop" ); if ( _q != 0 ) { _q->setPos( Vector2(-942.361f, 27.08332f) ); _q->setSize( Vector2(1167.945f, 908.121f) ); }

        MyPile->setPos( Vector2(995.1394f, -13.19449f) );
    }

	void InGameStartMenu::MakeExitItem()
	{
		boost::shared_ptr<MenuItem> item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_ExitLevel, ItemFont, CenterItems ) ) );
		item->setGo( Cast::ToItem( boost::make_shared<VerifyExitProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
		item->Name = L"Exit";
		AddItem( item );
	}

	void InGameStartMenu::VerifyExit()
	{
		Call( MakeMagic( VerifyQuitLevelMenu, ( getControl() ) ), 0 );
		
        if (UseBounce)
        {
            Hid = true;
            RegularSlideOut( PresetPos_RIGHT, 0 );
        }
        else
        {		
			Hide( PresetPos_LEFT );
		}

		setPauseGame( true );
	}

	void InGameStartMenu::MyDraw()
	{
		Pos->Update();

		CkBaseMenu::MyDraw();
	}
}
