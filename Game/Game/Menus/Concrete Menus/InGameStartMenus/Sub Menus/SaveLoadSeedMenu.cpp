#include <global_header.h>

#include "Hacks/Clipboard.h"

namespace CloudberryKingdom
{

	SaveLoadSeedMenu::MakeSaveHelper::MakeSaveHelper( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player )
	{
		this->panel = panel;
		this->player = player;
	}

	void SaveLoadSeedMenu::MakeSaveHelper::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		SaveLoadSeedMenu::Save( _item, panel, player );
	}

	SaveLoadSeedMenu::LoadProxy::LoadProxy( const boost::shared_ptr<SaveLoadSeedMenu> &slsm )
	{
		this->slsm = slsm;
	}

	void SaveLoadSeedMenu::LoadProxy::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		slsm->Load( _item );
	}

	
#if defined(WINDOWS)
	SaveLoadSeedMenu::CopyProxy::CopyProxy( const boost::shared_ptr<SaveLoadSeedMenu> &slsm )
	{
		this->slsm = slsm;
	}

	void SaveLoadSeedMenu::CopyProxy::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		slsm->Copy( _item );
	}
#endif

	SaveLoadSeedMenu::LoadStringProxy::LoadStringProxy( const boost::shared_ptr<SaveLoadSeedMenu> &slsm )
	{
		this->slsm = slsm;
	}

	void SaveLoadSeedMenu::LoadStringProxy::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		slsm->LoadString( _item );
	}

	SaveLoadSeedMenu::SaveLoadSeedMenu( int Control, bool CanLoad, bool CanSave ) :
		VerifyBaseMenu( false ),
		CanLoad( false ), CanSave( false )
	{
	}

	boost::shared_ptr<SaveLoadSeedMenu> SaveLoadSeedMenu::SaveLoadSeedMenu_Construct( int Control, bool CanLoad, bool CanSave )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( false );

		if ( boost::dynamic_pointer_cast<NormalGameData>( Tools::CurGameData ) != 0 )
		{
            EnableBounce();
		}

        if (UseBounce)
            CallToLeft = false;
        else
			CallToLeft = true;

		this->setControl( Control );
		FixedToCamera = true;

		this->CanLoad = CanLoad;
		this->CanSave = CanSave;

		Constructor();

		return boost::static_pointer_cast<SaveLoadSeedMenu>( shared_from_this() );
	}

	void SaveLoadSeedMenu::Init()
	{
		VerifyBaseMenu::Init();

		this->FontScale *= .9f;

		// Get the activating player
		player = MenuItem::GetActivatingPlayerData();

		// Header
		HeaderText = boost::make_shared<EzText>( Localization::Words_RandomSeed, ItemFont );
		HeaderText->Name = std::wstring( L"Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );

		boost::shared_ptr<MenuItem> item;

		if ( CanSave )
		{
			// Save seed
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_SaveSeed, ItemFont ) ) );
			item->Name = std::wstring( L"Save" );
			item->setGo( MakeSave( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ), player ) );
			AddItem( item );
		}

		if ( CanLoad )
		{
			// Load seed
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_LoadSeed, ItemFont ) ) );
			item->Name = std::wstring( L"Load" );
			item->setGo( boost::make_shared<LoadProxy>( boost::static_pointer_cast<SaveLoadSeedMenu>( shared_from_this() ) ) );
			AddItem( item );
		}

	#if defined(WINDOWS)
		if ( CanSave )
		{
			// Copy seed
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_CopyToClipboard, ItemFont ) ) );
			item->Name = std::wstring( L"Copy" );
			item->setGo( boost::make_shared<CopyProxy>( boost::static_pointer_cast<SaveLoadSeedMenu>( shared_from_this() ) ) );
			AddItem( item );
		}

		if ( CanLoad )
		{
			// Load seed from string
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_LoadFromClipboard, ItemFont ) ) );
			item->Name = std::wstring( L"LoadString" );
			item->setGo( boost::make_shared<LoadStringProxy>( boost::static_pointer_cast<SaveLoadSeedMenu>( shared_from_this() ) ) );
			AddItem( item );
		}
	#endif
		
#ifdef PC_VERSION
            MakeBackButton();
#else
            MakeBackButton();
            //MakeStaticBackButton();
#endif

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		SetPosition();
		MyMenu->SortByHeight();
		MyMenu->SelectItem( 0 );
	}

	void SaveLoadSeedMenu::SetPosition()
	{
	#if defined(PC_VERSION)
		if ( CanLoad && CanSave )
		{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( std::wstring( L"Save" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 686.1115f, 633.2222f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"Load" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 694.4447f, 441.5555f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"Copy" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 672.2223f, 222.1111f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"LoadString" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 672.2225f, 27.66663f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"Back" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 727.7777f, -163.9999f ) );
			}

			MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

			MyPile->FindEzText( std::wstring( L"Header" ) )->setPos( Vector2( 402.7776f, 871.8887f ) );

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
			if ( _q != 0 )
			{
				_q->setPos( Vector2( 1181.251f, 241.6668f ) );
				_q->setSize( Vector2( 1500, 803.2258f ) );
			}

			MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
		}
		else if ( CanLoad && !CanSave )
		{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( std::wstring( L"Save" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 686.1115f, 633.2222f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"Load" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 694.4447f, 441.5555f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"Copy" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 672.2223f, 222.1111f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"LoadString" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 672.2225f, 27.66663f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"Back" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 727.7777f, -163.9999f ) );
			}

			MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

			MyPile->FindEzText( std::wstring( L"Header" ) )->setPos( Vector2( 402.7776f, 871.8887f ) );

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
			if ( _q != 0 )
			{
				_q->setPos( Vector2( 1181.251f, 241.6668f ) );
				_q->setSize( Vector2( 1500, 803.2258f ) );
			}

			MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
		}
		else
		{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( std::wstring( L"Save" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 686.1115f, 499.889f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"Copy" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 674.9999f, 269.3333f ) );
			}
			_item = MyMenu->FindItemByName( std::wstring( L"Back" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 719.4445f, 47.11124f ) );
			}

			MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( std::wstring( L"Header" ) );
			if ( _t != 0 )
			{
				_t->setPos( Vector2( 425, 807.9997f ) );
			}

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
			if ( _q != 0 )
			{
				_q->setPos( Vector2( 1181.251f, 241.6668f ) );
				_q->setSize( Vector2( 1224.558f, 736.7258f ) );
			}

			MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
		}
	#else
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2( 741.6669f, 547.111f ) ); _item->MyText->setScale( 0.7334167f ); _item->MySelectedText->setScale( 0.7334167f ); _item->SelectIconOffset = Vector2( 0.f, 0.f );  }
			_item = MyMenu->FindItemByName( L"Load" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.0004f, 330.4444f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f );  }
			_item = MyMenu->FindItemByName( L"Copy" ); if (_item != 0 ) { _item->setSetPos( Vector2( 3044.444f, -1480.667f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f );  }
			_item = MyMenu->FindItemByName( L"LoadString" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1527.778f, -1983.444f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f );  }
			_item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 758.3339f, 8.222351f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f );  }

			MyMenu->setPos( Vector2(-1125.001f, -319.4444f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2( 658.333f, 905.222f ) ); _t->setScale( 0.864f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 1181.251f, 313.889f ) ); _q->setSize( Vector2( 1089.917f, 752.6426f ) ); }

			MyPile->setPos( Vector2(-1127.779f, -322.2222f ) );
	#endif
	}


	boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > SaveLoadSeedMenu::MakeSave( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player )
	{
		return boost::make_shared<MakeSaveHelper>( panel, player );
	}

	void SaveLoadSeedMenu::Save( const boost::shared_ptr<MenuItem> &_item, const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player )
	{
		boost::shared_ptr<CkBaseMenu> ckpanel = boost::dynamic_pointer_cast<CkBaseMenu>( panel );

		boost::shared_ptr<SaveSeedAs> SaveAs = MakeMagic( SaveSeedAs, ( panel->getControl(), player ) );

			if ( 0 != ckpanel && ckpanel->UseBounce )
			{
				panel->Call( SaveAs, 0 );

				ckpanel->Hid = true;
				ckpanel->RegularSlideOut( PresetPos_RIGHT, 0 );
			}
			else
			{
				panel->Call( SaveAs, 17 );

				ckpanel->Hide( PresetPos_LEFT, 20 );
			}
	}

	void SaveLoadSeedMenu::Load( const boost::shared_ptr<MenuItem> &_item )
	{
		boost::shared_ptr<SavedSeedsGUI> LoadMenu = MakeMagic( SavedSeedsGUI, () );
		Call( LoadMenu, 0 );

        if (UseBounce)
        {
            Hid = true;
            RegularSlideOut( PresetPos_RIGHT, 0 );
        }
	}

#if defined(WINDOWS)
	void SaveLoadSeedMenu::Copy( const boost::shared_ptr<MenuItem> &_item )
	{
		std::wstring seed = Tools::CurLevel->MyLevelSeed->ToString();
		Clipboard::SetText( seed );
	}
#endif

	void SaveLoadSeedMenu::LoadString( const boost::shared_ptr<MenuItem> &_item )
	{
		boost::shared_ptr<LoadSeedAs> LoadAs = MakeMagic( LoadSeedAs, ( getControl(), player ) );
		Call( LoadAs, 0 );

        if (UseBounce)
        {
            Hid = true;
            RegularSlideOut( PresetPos_RIGHT, 0 );
        }
	}

	void SaveLoadSeedMenu::OnAdd()
	{
		VerifyBaseMenu::OnAdd();

		SetPosition();
	}
}
