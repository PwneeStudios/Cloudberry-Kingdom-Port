#include <global_header.h>

#include "Hacks/Clipboard.h"

namespace CloudberryKingdom
{

#if defined(WINDOWS)
	SaveLoadSeedMenu::MakeSaveHelper::MakeSaveHelper( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player )
	{
		this->panel = panel;
		this->player = player;
	}

	void SaveLoadSeedMenu::MakeSaveHelper::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		SaveLoadSeedMenu::Save( _item, panel, player );
	}
#else
	SaveLoadSeedMenu::SaveLoadSeedsMakeSaveLambda::SaveLoadSeedsMakeSaveLambda( const boost::shared_ptr<PlayerData> &player )
	{
		this->player = player;
	}

	void SaveLoadSeedMenu::SaveLoadSeedsMakeSaveLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		SaveLoadSeedMenu::Save( item, player );
	}
#endif

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

		this->CallToLeft = true;
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
		HeaderText = boost::make_shared<EzText>( Localization::Words_RANDOM_SEED, ItemFont );
		HeaderText->Name = std::wstring( L"Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );

		boost::shared_ptr<MenuItem> item;

		if ( CanSave )
		{
			// Save seed
			item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_SAVE_SEED, ItemFont ) );
			item->Name = std::wstring( L"Save" );
			item->setGo( MakeSave( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ), player ) );
			AddItem( item );
		}

		if ( CanLoad )
		{
			// Load seed
			item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_LOAD_SEED, ItemFont ) );
			item->Name = std::wstring( L"Load" );
			item->setGo( boost::make_shared<LoadProxy>( boost::static_pointer_cast<SaveLoadSeedMenu>( shared_from_this() ) ) );
			AddItem( item );
		}

	#if defined(WINDOWS)
		if ( CanSave )
		{
			// Copy seed
			item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_COPY_TO_CLIPBOARD, ItemFont ) );
			item->Name = std::wstring( L"Copy" );
			item->setGo( boost::make_shared<CopyProxy>( boost::static_pointer_cast<SaveLoadSeedMenu>( shared_from_this() ) ) );
			AddItem( item );
		}

		if ( CanLoad )
		{
			// Load seed from string
			item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_LOAD_FROM_CLIPBOARD, ItemFont ) );
			item->Name = std::wstring( L"LoadString" );
			item->setGo( boost::make_shared<LoadStringProxy>( boost::static_pointer_cast<SaveLoadSeedMenu>( shared_from_this() ) ) );
			AddItem( item );
		}
	#endif
		MakeBackButton();

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
	#endif
	}

#if defined(WINDOWS)
	boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > SaveLoadSeedMenu::MakeSave( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player )
	{
		return boost::make_shared<MakeSaveHelper>( panel, player );
	}
#endif

#if defined(WINDOWS)
	void SaveLoadSeedMenu::Save( const boost::shared_ptr<MenuItem> &_item, const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player )
	{
		boost::shared_ptr<SaveSeedAs> SaveAs = MakeMagic( SaveSeedAs, ( panel->getControl(), player ) );
		panel->Call( SaveAs, 0 );
	}
#endif

#if ! defined(WINDOWS)
	boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > SaveLoadSeedMenu::MakeSave( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player )
	{
		return boost::make_shared<SaveLoadSeedsMakeSaveLambda>( player );
	}
#endif

#if ! defined(WINDOWS)
boost::shared_ptr<IAsyncResult> SaveLoadSeedMenu::kyar = 0;
#endif

#if ! defined(WINDOWS)
boost::shared_ptr<PlayerData> SaveLoadSeedMenu::_player = 0;
#endif

#if ! defined(WINDOWS)
	void SaveLoadSeedMenu::Save( const boost::shared_ptr<MenuItem> &_item, const boost::shared_ptr<PlayerData> &activeplayer )
	{
		_player = activeplayer;
		
		// FIXME: Uncomment this.
		//kyar = Guide::BeginShowKeyboardInput( _player->MyPlayerIndex, std::wstring( L"Save random seed as..." ), std::wstring( L"Choose a name to save this level as." ), Tools::CurLevel->MyLevelSeed->SuggestedName(), OnKeyboardComplete, 0 );
	}
#endif

#if ! defined(WINDOWS)
	void SaveLoadSeedMenu::OnKeyboardComplete( const boost::shared_ptr<IAsyncResult> &ar )
	{
		// Get the input from the virtual keyboard

		// FIXME: Uncomment this.
		std::wstring input;// = Guide::EndShowKeyboardInput( kyar );

		if ( input == std::wstring( L"" ) )
			return;

		// Strip anything after a semicolon (because this will confuse the seed parser)
		if ( input.find( std::wstring( L";" ) ) != std::string::npos )
		{
			input = input.substr( 0, input.find( std::wstring( L";" ) ) );
		}

		// Save the seed
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		_player->MySavedSeeds->SaveSeed( Tools::CurLevel->MyLevelSeed->ToString(), input );
	}
#endif

	void SaveLoadSeedMenu::Load( const boost::shared_ptr<MenuItem> &_item )
	{
		boost::shared_ptr<SavedSeedsGUI> LoadMenu = MakeMagic( SavedSeedsGUI, () );
		Call( LoadMenu, 0 );
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
	}

	void SaveLoadSeedMenu::OnAdd()
	{
		VerifyBaseMenu::OnAdd();

		SetPosition();
	}
}
