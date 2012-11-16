#include <global_header.h>

using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))
using namespace Microsoft::Xna::Framework::GamerServices;
#endif

namespace CloudberryKingdom
{

	SaveLoadSeedMenu::MakeSaveHelper::MakeSaveHelper( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player )
	{
		this->panel = panel;
		this->player = player;
	}

	void SaveLoadSeedMenu::MakeSaveHelper::Apply( const std::shared_ptr<MenuItem> &_item )
	{
		SaveLoadSeedMenu::Save( _item, panel, player );
	}

	SaveLoadSeedMenu::SaveLoadSeedsMakeSaveLambda::SaveLoadSeedsMakeSaveLambda( const std::shared_ptr<PlayerData> &player )
	{
		this->player = player;
	}

	void SaveLoadSeedMenu::SaveLoadSeedsMakeSaveLambda::Apply( const std::shared_ptr<MenuItem> &item )
	{
		SaveLoadSeedMenu::Save( item, player );
	}

	SaveLoadSeedMenu::LoadProxy::LoadProxy( const std::shared_ptr<SaveLoadSeedMenu> &slsm )
	{
		this->slsm = slsm;
	}

	void SaveLoadSeedMenu::LoadProxy::Apply( const std::shared_ptr<MenuItem> &_item )
	{
		slsm->Load( _item );
	}

	SaveLoadSeedMenu::CopyProxy::CopyProxy( const std::shared_ptr<SaveLoadSeedMenu> &slsm )
	{
		this->slsm = slsm;
	}

	void SaveLoadSeedMenu::CopyProxy::Apply( const std::shared_ptr<MenuItem> &_item )
	{
		slsm->Copy( _item );
	}

	SaveLoadSeedMenu::LoadStringProxy::LoadStringProxy( const std::shared_ptr<SaveLoadSeedMenu> &slsm )
	{
		this->slsm = slsm;
	}

	void SaveLoadSeedMenu::LoadStringProxy::Apply( const std::shared_ptr<MenuItem> &_item )
	{
		slsm->LoadString( _item );
	}

	SaveLoadSeedMenu::SaveLoadSeedMenu( int Control, bool CanLoad, bool CanSave ) : VerifyBaseMenu( false )
	{
		this->CallToLeft = true;
		this->setControl( Control );
		FixedToCamera = true;

		this->CanLoad = CanLoad;
		this->CanSave = CanSave;

		Constructor();
	}

	void SaveLoadSeedMenu::Init()
	{
		VerifyBaseMenu::Init();

		this->FontScale *= .9f;

		// Get the activating player
		player = MenuItem::GetActivatingPlayerData();

		// Header
		HeaderText = std::make_shared<EzText>( Localization::Words_RANDOM_SEED, ItemFont );
		HeaderText->Name = _T( "Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );

		std::shared_ptr<MenuItem> item;

		if ( CanSave )
		{
			// Save seed
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_SAVE_SEED, ItemFont ) );
			item->Name = _T( "Save" );
			item->setGo( MakeSave( this, player ) );
			AddItem( item );
		}

		if ( CanLoad )
		{
			// Load seed
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_LOAD_SEED, ItemFont ) );
			item->Name = _T( "Load" );
			item->setGo( std::make_shared<LoadProxy>( this ) );
			AddItem( item );
		}

	#if defined(WINDOWS)
		if ( CanSave )
		{
			// Copy seed
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_COPY_TO_CLIPBOARD, ItemFont ) );
			item->Name = _T( "Copy" );
			item->setGo( std::make_shared<CopyProxy>( this ) );
			AddItem( item );
		}

		if ( CanLoad )
		{
			// Load seed from string
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_LOAD_FROM_CLIPBOARD, ItemFont ) );
			item->Name = _T( "LoadString" );
			item->setGo( std::make_shared<LoadStringProxy>( this ) );
			AddItem( item );
		}
	#endif
		MakeBackButton();

		MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		SetPosition();
		MyMenu->SortByHeight();
		MyMenu->SelectItem( 0 );
	}

	void SaveLoadSeedMenu::SetPosition()
	{
	#if defined(PC_VERSION)
		if ( CanLoad && CanSave )
		{
			std::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( _T( "Save" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 686.1115f, 633.2222f ) );
			}
			_item = MyMenu->FindItemByName( _T( "Load" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 694.4447f, 441.5555f ) );
			}
			_item = MyMenu->FindItemByName( _T( "Copy" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 672.2223f, 222.1111f ) );
			}
			_item = MyMenu->FindItemByName( _T( "LoadString" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 672.2225f, 27.66663f ) );
			}
			_item = MyMenu->FindItemByName( _T( "Back" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 727.7777f, -163.9999f ) );
			}

			MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

			MyPile->FindEzText( _T( "Header" ) )->setPos( Vector2( 402.7776f, 871.8887f ) );

			std::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( _T( "Backdrop" ) );
			if ( _q != 0 )
			{
				_q->setPos( Vector2( 1181.251f, 241.6668f ) );
				_q->setSize( Vector2( 1500, 803.2258f ) );
			}

			MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
		}
		else if ( CanLoad && !CanSave )
		{
			std::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( _T( "Save" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 686.1115f, 633.2222f ) );
			}
			_item = MyMenu->FindItemByName( _T( "Load" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 694.4447f, 441.5555f ) );
			}
			_item = MyMenu->FindItemByName( _T( "Copy" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 672.2223f, 222.1111f ) );
			}
			_item = MyMenu->FindItemByName( _T( "LoadString" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 672.2225f, 27.66663f ) );
			}
			_item = MyMenu->FindItemByName( _T( "Back" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 727.7777f, -163.9999f ) );
			}

			MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

			MyPile->FindEzText( _T( "Header" ) )->setPos( Vector2( 402.7776f, 871.8887f ) );

			std::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( _T( "Backdrop" ) );
			if ( _q != 0 )
			{
				_q->setPos( Vector2( 1181.251f, 241.6668f ) );
				_q->setSize( Vector2( 1500, 803.2258f ) );
			}

			MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
		}
		else
		{
			std::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( _T( "Save" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 686.1115f, 499.889f ) );
			}
			_item = MyMenu->FindItemByName( _T( "Copy" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 674.9999f, 269.3333f ) );
			}
			_item = MyMenu->FindItemByName( _T( "Back" ) );
			if ( _item != 0 )
			{
				_item->setSetPos( Vector2( 719.4445f, 47.11124f ) );
			}

			MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

			std::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( _T( "Header" ) );
			if ( _t != 0 )
			{
				_t->setPos( Vector2( 425, 807.9997f ) );
			}

			std::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( _T( "Backdrop" ) );
			if ( _q != 0 )
			{
				_q->setPos( Vector2( 1181.251f, 241.6668f ) );
				_q->setSize( Vector2( 1224.558f, 736.7258f ) );
			}

			MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
		}
	#else
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Save" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 686.1115f, 633.2222f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Load" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 694.4447f, 441.5555f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Copy" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 672.2223f, 222.1111f ) );
		}
		_item = MyMenu->FindItemByName( _T( "LoadString" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 672.2225f, 27.66663f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 727.7777f, -163.9999f ) );
		}

		MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

		MyPile->FindEzText( _T( "Header" ) )->setPos( Vector2( 402.7776f, 871.8887f ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 1181.251f, 241.6668f ) );
			_q->setSize( Vector2( 1500, 803.2258f ) );
		}

		MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
	#endif
	}

#if defined(WINDOWS)
	std::shared_ptr<Lambda_1<MenuItem*> > SaveLoadSeedMenu::MakeSave( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player )
	{
		return std::make_shared<MakeSaveHelper>( panel, player );
	}
#endif

#if defined(WINDOWS)
	void SaveLoadSeedMenu::Save( const std::shared_ptr<MenuItem> &_item, const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player )
	{
		std::shared_ptr<SaveSeedAs> SaveAs = std::make_shared<SaveSeedAs>( panel->getControl(), player );
		panel->Call( SaveAs, 0 );
	}
#endif

#if ! defined(WINDOWS)
	std::shared_ptr<Lambda_1<MenuItem*> > SaveLoadSeedMenu::MakeSave( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player )
	{
		return std::make_shared<SaveLoadSeedsMakeSaveLambda>( player );
	}
#endif

#if ! defined(WINDOWS)
std::shared_ptr<IAsyncResult> SaveLoadSeedMenu::kyar = 0;
#endif

#if ! defined(WINDOWS)
std::shared_ptr<PlayerData> SaveLoadSeedMenu::_player = 0;
#endif

#if ! defined(WINDOWS)
	void SaveLoadSeedMenu::Save( const std::shared_ptr<MenuItem> &_item, const std::shared_ptr<PlayerData> &activeplayer )
	{
		_player = activeplayer;
		kyar = Guide::BeginShowKeyboardInput( _player->MyPlayerIndex, _T( "Save random seed as..." ), _T( "Choose a name to save this level as." ), Tools::CurLevel->MyLevelSeed->SuggestedName(), OnKeyboardComplete, 0 );
	}
#endif

#if ! defined(WINDOWS)
	void SaveLoadSeedMenu::OnKeyboardComplete( const std::shared_ptr<IAsyncResult> &ar )
	{
		// Get the input from the virtual keyboard
		std::wstring input = Guide::EndShowKeyboardInput( kyar );

		if ( input == _T( "" ) )
			return;

		// Strip anything after a semicolon (because this will confuse the seed parser)
		if ( input.find( _T( ";" ) ) != string::npos )
		{
			input = input.substr( 0, input.find( _T( ";" ) ) );
		}

		// Save the seed
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		_player->MySavedSeeds->SaveSeed( Tools::CurLevel->MyLevelSeed->ToString(), input );
	}
#endif

	void SaveLoadSeedMenu::Load( const std::shared_ptr<MenuItem> &_item )
	{
		std::shared_ptr<SavedSeedsGUI> LoadMenu = std::make_shared<SavedSeedsGUI>();
		Call( LoadMenu, 0 );
	}

#if defined(WINDOWS)
	void SaveLoadSeedMenu::Copy( const std::shared_ptr<MenuItem> &_item )
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		std::wstring seed = Tools::CurLevel->MyLevelSeed->ToString();
		System::Windows::Forms::Clipboard::SetText( seed );
	}
#endif

	void SaveLoadSeedMenu::LoadString( const std::shared_ptr<MenuItem> &_item )
	{
		std::shared_ptr<LoadSeedAs> LoadAs = std::make_shared<LoadSeedAs>( getControl(), player );
		Call( LoadAs, 0 );
	}

	void SaveLoadSeedMenu::OnAdd()
	{
		VerifyBaseMenu::OnAdd();

		SetPosition();
	}
}
