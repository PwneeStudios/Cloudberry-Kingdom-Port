#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include "Game/Menus/Concrete Menus/ShopMenu.h"

#include <SaveSeedSettings.h>

namespace CloudberryKingdom
{
		
	ScoreScreen::EOL_WaitThenDoEndActionWaitProxy::EOL_WaitThenDoEndActionWaitProxy( const boost::shared_ptr<StringWorldGameData> &sw, const boost::shared_ptr<Door> &door )
	{
		this->sw = sw;
		this->door = door;
	}

	void ScoreScreen::EOL_WaitThenDoEndActionWaitProxy::Apply()
	{
		sw->EOL_StringWorldDoorEndAction( door );
	}

	ScoreScreen::EOL_WaitThenDoEndActionProxy::EOL_WaitThenDoEndActionProxy( boost::shared_ptr<ScoreScreen> ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::EOL_WaitThenDoEndActionProxy::Apply( const boost::shared_ptr<Door> &door )
	{
		ss->EOL_WaitThenDoEndAction( door );
	}

	ScoreScreen::OnAddHelper::OnAddHelper( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::OnAddHelper::Apply()
	{
		ss->MyMenu->Active = true;
	}

	ScoreScreen::VariableCoinsLambda::VariableCoinsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableCoinsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->Coins;
	}

	ScoreScreen::VariableTotalCoinsLambda::VariableTotalCoinsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableTotalCoinsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->TotalCoins;
	}

	ScoreScreen::VariableBlobsLambda::VariableBlobsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableBlobsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->Blobs;
	}

	ScoreScreen::VariableTotalBlobsLambda::VariableTotalBlobsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableTotalBlobsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->TotalBlobs;
	}

	ScoreScreen::ScoreScreenEndGameHelper::ScoreScreenEndGameHelper( const boost::shared_ptr<ScoreScreen> &ss, bool parameter )
	{
		this->ss = ss;
		this->parameter = parameter;
	}

	void ScoreScreen::ScoreScreenEndGameHelper::Apply()
	{
		ss->MyGame->EndGame->Apply( parameter );
	}

	ScoreScreen::MenuGo_NewLevelProxy::MenuGo_NewLevelProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_NewLevelProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_NewLevel( item );
	}

	ScoreScreen::MenuGo_ContinueProxy::MenuGo_ContinueProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_ContinueProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_Continue( item );
	}

	ScoreScreen::MenuGo_WatchReplayHelper::MenuGo_WatchReplayHelper( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_WatchReplayHelper::Apply()
	{
		ss->OnReturnTo(); // Re-activate the Score Screen object
		ss->getCore()->MyLevel->WatchReplay(true); // Start the replay
	}

	ScoreScreen::MenuGo_WatchReplayProxy::MenuGo_WatchReplayProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_WatchReplayProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_WatchReplay( item );
	}

	ScoreScreen::MenuGo_SaveProxy::MenuGo_SaveProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_SaveProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_Save( item );
	}

	ScoreScreen::MenuGo_ExitCampaignProxy::MenuGo_ExitCampaignProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_ExitCampaignProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_ExitCampaign( item );
	}

	ScoreScreen::MenuGo_ExitFreeplayProxy::MenuGo_ExitFreeplayProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_ExitFreeplayProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_ExitFreeplay( item );
	}

	void ScoreScreen::MakeMenu()
	{
		if ( AsMenu )
		{
			MyMenu = boost::make_shared<Menu>( false );

			MyMenu->setControl( -1 );

			MyMenu->OnB.reset();

			_Add_Watch = MyGame->MyLevel->getReplayAvailable();
			_Add_Save = MyGame->MyLevel->MyLevelSeed != 0 && MyGame->MyLevel->MyLevelSeed->Saveable;

			boost::shared_ptr<MenuItem> item, go;

				if (InCampaign)
				{
					go = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Continue, ItemFont ) ) );
					item->setGo( boost::make_shared<MenuGo_ContinueProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
				}
				else
				{
					go = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_KeepSettings, ItemFont ) ) );
					item->setGo( boost::make_shared<MenuGo_NewLevelProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
				}

			item->Name = std::wstring( L"Continue" );
			AddItem( item );
			item->MySelectedText->setScale( item->MySelectedText->getScale() * 1.3f );
			item->MyText->setScale( item->MySelectedText->getScale() );
			item->Shift( Vector2( -86, 65 ) );
			item->SelectedPos.X += 6;

			if ( _Add_Watch )
			{
				item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_WatchReplay, ItemFont ) ) );
				item->Name = std::wstring( L"Replay" );
				item->setGo( boost::make_shared<MenuGo_WatchReplayProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
				AddItem( item );
			}

			if ( _Add_Save )
			{
				item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_SaveSeed, ItemFont ) ) );
				item->Name = std::wstring( L"Save" );
				item->setGo( boost::make_shared<MenuGo_SaveProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
				item->Selectable = CloudberryKingdomGame::CanSave();
				AddItem( item );

				if ( PlayerManager::Players[ 0 ] && PlayerManager::Players[ 0 ]->MySavedSeeds->SeedStrings.size() >= MAX_SEED_STRINGS )
				{
					item->Selectable = false;
					item->GrayOutOnUnselectable = true;
					item->GrayOut();

					CloudberryKingdomGame::ChangeSaveGoFunc( item );
				}
			}

			boost::shared_ptr<MenuItem> back;
			if (InCampaign)
			{
				back = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::WordString( Localization::Words_Exit), ItemFont ) ) );
				AddItem(back);
				back->setGo( boost::make_shared<MenuGo_ExitCampaignProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
			}
			else
			{
				if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_RUSSIAN )
					back = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::WordString( Localization::Words_Back ), ItemFont ) ) );
				else
					back = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::WordString( Localization::Words_BackToFreeplay ), ItemFont ) ) );
				AddItem(back);
				back->setGo( boost::make_shared<MenuGo_ExitFreeplayProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
			}

			MyMenu->OnB.reset();;
			//MyMenu->OnB = Cast::ToMenu( go->getGo() );

			EnsureFancy();
			MyMenu->FancyPos->RelVal = Vector2( 869.0476f, -241.6667f );
		}
		else
		{
			boost::shared_ptr<QuadClass> ContinueButton = boost::make_shared<QuadClass>( ButtonTexture::getGo(), 90.f, false );
			ContinueButton->Name = std::wstring( L"GoButton" );
			MyPile->Add( ContinueButton );
			ContinueButton->setPos( Vector2( 180, -477.7778f ) + ShiftAll );

			boost::shared_ptr<EzText> ContinueText = boost::make_shared<EzText>( Localization::Words_Continue, ItemFont );
			ContinueText->Name = std::wstring( L"Continue" );
			SetHeaderProperties( ContinueText );
			ContinueText->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;
			MyPile->Add( ContinueText );
			ContinueText->setPos( Vector2( 180, -477.7778f ) + ShiftAll );

			if ( MyGame->MyLevel->getReplayAvailable() )
			{
				boost::shared_ptr<QuadClass> XButton = boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.f, false );
				XButton->Name = std::wstring( L"XButton" );
				MyPile->Add( XButton );
				XButton->setPos( Vector2( 180, -325.3333f ) + ShiftAll );

				boost::shared_ptr<EzText> ReplayText = boost::make_shared<EzText>( Localization::Words_WatchReplay, ItemFont );
				SetHeaderProperties( ReplayText );
				ReplayText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
				ReplayText->MyFloatColor = ( bColor( 184, 231, 231 ) ).ToVector4();
				MyPile->Add( ReplayText );
				ReplayText->setPos( Vector2( 180, -325.3333f ) + ShiftAll );
			}
		}
	}
	
	ScoreScreen::ScoreScreen( bool CallBaseConstructor ) :
		CkBaseMenu( CallBaseConstructor ),
		InCampaign( false ), _Add_Watch( false ), _Add_Save( false ), DelayPhsx( false ), MyStatGroup( static_cast<StatGroup>( 0 ) ), LastActive( false )
	{
	}
	boost::shared_ptr<ScoreScreen> ScoreScreen::ScoreScreen_Construct( bool CallBaseConstructor )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct( CallBaseConstructor );

		return boost::static_pointer_cast<ScoreScreen>( shared_from_this() );
	}

	ScoreScreen::ScoreScreen( StatGroup group, const boost::shared_ptr<GameData> &game, const bool InCampaign ) :
		CkBaseMenu( false ),
		InCampaign( InCampaign ), _Add_Watch( false ), _Add_Save( false ), DelayPhsx( false ), MyStatGroup( static_cast<StatGroup>( 0 ) ), LastActive( false )
	{
	}
	boost::shared_ptr<ScoreScreen> ScoreScreen::ScoreScreen_Construct( StatGroup group, const boost::shared_ptr<GameData> &game, const bool InCampaign )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct( false );
		
		MyGame = game;
		MyStatGroup = group;
		FontScale = .6f;

		Constructor();

		return boost::static_pointer_cast<ScoreScreen>( shared_from_this() );
	}

	void ScoreScreen::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		//StartMenu::SetItemProperties_Red( item );
		//CkColorHelper::GreenItem( item );
	}

	void ScoreScreen::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;

		//text.MyFloatColor = ColorHelper::Gray(.85f);
		//text->OutlineColor = ColorHelper::Gray(.05f);
		text->MyFloatColor = ColorHelper::Gray(.925f);
		text->OutlineColor = ColorHelper::Gray(.05f);

		text->Shadow = true;
		text->ShadowColor = Color(.2f, .2f, .2f, .25f);
		text->ShadowOffset = Vector2(12, 12);

		text->setScale( FontScale * .9f );
	}

#if defined(PC_VERSION)
bool ScoreScreen::AsMenu = true;
#endif

#if ! defined(PC_VERSION)
bool ScoreScreen::AsMenu = true;
#endif

	void ScoreScreen::Init()
	{
		CkBaseMenu::Init();

		MyPile = boost::make_shared<DrawPile>();

		MakeDarkBack();

		boost::shared_ptr<QuadClass> Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1230x740" ), std::wstring( L"Backdrop" ) );
		MyPile->Add( Backdrop );
		//MyPile->Add( Backdrop );

		EpilepsySafe( .5f );

		boost::shared_ptr<EzText> lc = boost::make_shared<EzText>( Localization::Words_LevelCleared, Resources::Font_Grobold42_2, std::wstring( L"LevelCleared" ) );
		SetHeaderProperties( lc );
		lc->Shadow = true;
		lc->ShadowOffset = Vector2(20, 20);
		lc->ShadowColor = Color(.36f, .36f, .36f, .86f);
		MyPile->Add( lc );


		MyPile->Add( boost::make_shared<QuadClass>( std::wstring( L"Coin_Blue" ), std::wstring( L"Coin" ) ) );
		MyPile->Add( boost::make_shared<QuadClass>( std::wstring( L"Stopwatch_Black" ), std::wstring( L"Stopwatch" ) ) );
		MyPile->Add( boost::make_shared<QuadClass>( std::wstring( L"Bob_Dead" ), std::wstring( L"Death" ) ) );

		MakeMenu();

		ScoreSound = Tools::SoundWad->FindByName( std::wstring( L"Coin" ) );
		BonusSound = Tools::SoundWad->FindByName( std::wstring( L"Coin" ) );
		ScoreSound->MaxInstances = 2;

		SetPos();
	}

	void ScoreScreen::SetPos()
	{
			if ( InCampaign )
			{
				if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_CHINESE )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-224.5549f, 663.889f ) ); _item->MyText->setScale( 0.9387498f ); _item->MySelectedText->setScale( 0.9387498f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-302.4446f, 313.8959f ) ); _item->MyText->setScale( 0.6167499f ); _item->MySelectedText->setScale( 0.6167499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-294.1105f, 125.0071f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-310.7764f, -297.2153f ) ); _item->MyText->setScale( 0.6325002f ); _item->MySelectedText->setScale( 0.6325002f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-1119.443f, 791.6667f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_KOREAN )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-38.44455f, 566.6667f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-244.1106f, 291.6737f ) ); _item->MyText->setScale( 0.6167499f ); _item->MySelectedText->setScale( 0.6167499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-227.4435f, 66.67379f ) ); _item->MyText->setScale( 0.5970834f ); _item->MySelectedText->setScale( 0.5970834f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-369.1104f, -341.6597f ) ); _item->MyText->setScale( 0.6360001f ); _item->MySelectedText->setScale( 0.6360001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_RUSSIAN )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-621.7766f, 533.3334f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-335.7776f, 288.8959f ) ); _item->MyText->setScale( 0.6167499f ); _item->MySelectedText->setScale( 0.6167499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-749.6661f, 83.34048f ) ); _item->MyText->setScale( 0.4923335f ); _item->MySelectedText->setScale( 0.4923335f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-571.8877f, -355.5486f ) ); _item->MyText->setScale( 0.6360001f ); _item->MySelectedText->setScale( 0.6360001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-1136.11f, 816.6666f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-477.3322f, 563.8889f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-680.2219f, 263.896f ) ); _item->MyText->setScale( 0.6167499f ); _item->MySelectedText->setScale( 0.6167499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-460.7775f, 61.11825f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-594.1104f, -355.5486f ) ); _item->MyText->setScale( 0.6360001f ); _item->MySelectedText->setScale( 0.6360001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-441.2219f, 550.0001f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-707.9993f, 227.7848f ) ); _item->MyText->setScale( 0.5110831f ); _item->MySelectedText->setScale( 0.5110831f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-571.8878f, 41.67381f ) ); _item->MyText->setScale( 0.4922499f ); _item->MySelectedText->setScale( 0.4922499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-377.4434f, -363.8819f ) ); _item->MyText->setScale( 0.5636668f ); _item->MySelectedText->setScale( 0.5636668f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_ITALIAN )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-444.0002f, 563.8889f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-435.7776f, 283.3404f ) ); _item->MyText->setScale( 0.6167499f ); _item->MySelectedText->setScale( 0.6167499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-710.7775f, 86.11825f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-566.332f, -355.5486f ) ); _item->MyText->setScale( 0.6360001f ); _item->MySelectedText->setScale( 0.6360001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-1161.11f, 791.6667f ) ); _t->setScale( 1.057333f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-471.7776f, 563.8889f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-485.7776f, 288.896f ) ); _item->MyText->setScale( 0.6167499f ); _item->MySelectedText->setScale( 0.6167499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-582.9991f, 72.22939f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-477.4443f, -349.9931f ) ); _item->MyText->setScale( 0.6360001f ); _item->MySelectedText->setScale( 0.6360001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-302.3342f, 552.7779f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-735.7776f, 294.4515f ) ); _item->MyText->setScale( 0.6167499f ); _item->MySelectedText->setScale( 0.6167499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-485.7775f, 91.67379f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-696.8877f, -330.5486f ) ); _item->MyText->setScale( 0.6360001f ); _item->MySelectedText->setScale( 0.6360001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_JAPANESE )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-221.7776f, 588.8889f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-435.7776f, 283.3404f ) ); _item->MyText->setScale( 0.6167499f ); _item->MySelectedText->setScale( 0.6167499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-438.5548f, 75.00716f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-438.5547f, -274.993f ) ); _item->MyText->setScale( 0.6337501f ); _item->MySelectedText->setScale( 0.6337501f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-719.4434f, 824.9999f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-491.2219f, 566.6667f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-435.7776f, 283.3404f ) ); _item->MyText->setScale( 0.6167499f ); _item->MySelectedText->setScale( 0.6167499f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-594.1105f, 86.11825f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-413.5547f, -311.1042f ) ); _item->MyText->setScale( 0.6360001f ); _item->MySelectedText->setScale( 0.6360001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
			}
			else
			{
				if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_KOREAN )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-427.3342f, 536.1111f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-308.0003f, 277.7849f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-313.5558f, 94.45162f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-774.666f, -338.8819f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_CHINESE )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-594.0002f, 738.889f ) ); _item->MyText->setScale( 0.9545831f ); _item->MySelectedText->setScale( 0.9545831f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-344.1106f, 397.2292f ) ); _item->MyText->setScale( 0.67125f ); _item->MySelectedText->setScale( 0.67125f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-346.8889f, 213.896f ) ); _item->MyText->setScale( 0.67125f ); _item->MySelectedText->setScale( 0.67125f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-602.4443f, -302.7708f ) ); _item->MyText->setScale( 0.67125f ); _item->MySelectedText->setScale( 0.67125f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-655.5558f, 22.22227f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-649.9994f, -402.7777f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-655.5553f, 411.1111f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -141.6665f ) ); _q->setSize( Vector2( 190.8688f, 190.8688f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-913.8881f, -513.8888f ) ); _q->setSize( Vector2( 180.9532f, 211.6065f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-983.3334f, 230.5556f ) ); _q->setSize( Vector2( 301.7774f, 221.3034f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_RUSSIAN )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-830.111f, 500.0001f ) ); _item->MyText->setScale( 0.6186666f ); _item->MySelectedText->setScale( 0.6186666f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-177.4445f, 275.007f ) ); _item->MyText->setScale( 0.540917f ); _item->MySelectedText->setScale( 0.540917f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-827.4455f, 97.22939f ) ); _item->MyText->setScale( 0.5631669f ); _item->MySelectedText->setScale( 0.5631669f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2( 36.44333f, -247.2152f ) ); _item->MyText->setScale( 0.5860835f ); _item->MySelectedText->setScale( 0.5860835f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 885.7141f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-688.8889f, 22.22227f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-677.7777f, -402.7777f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-691.6666f, 411.1111f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-944.4442f, -169.4443f ) ); _q->setSize( Vector2( 150.3689f, 150.3689f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-886.1108f, -513.8888f ) ); _q->setSize( Vector2( 159.8058f, 186.773f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-983.3334f, 219.4445f ) ); _q->setSize( Vector2( 281.6637f, 206.5533f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-793.9996f, 516.6667f ) ); _item->MyText->setScale( 0.6325831f ); _item->MySelectedText->setScale( 0.6325831f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-538.5558f, 266.6737f ) ); _item->MyText->setScale( 0.5548335f ); _item->MySelectedText->setScale( 0.5548335f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-410.7795f, 91.67379f ) ); _item->MyText->setScale( 0.5871667f ); _item->MySelectedText->setScale( 0.5871667f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-866.3331f, -424.993f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-688.8889f, 22.22227f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-677.7777f, -402.7777f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-691.6666f, 411.1111f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-944.4442f, -169.4443f ) ); _q->setSize( Vector2( 150.3689f, 150.3689f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-886.1108f, -513.8888f ) ); _q->setSize( Vector2( 159.8058f, 186.773f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-983.3334f, 219.4445f ) ); _q->setSize( Vector2( 281.6637f, 206.5533f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1055.111f, 516.6667f ) ); _item->MyText->setScale( 0.6325831f ); _item->MySelectedText->setScale( 0.6325831f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-774.6672f, 275.007f ) ); _item->MyText->setScale( 0.5548335f ); _item->MySelectedText->setScale( 0.5548335f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-724.6672f, 91.67379f ) ); _item->MyText->setScale( 0.5871667f ); _item->MySelectedText->setScale( 0.5871667f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-780.2227f, -424.993f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-688.8889f, 22.22227f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-677.7777f, -402.7777f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-691.6666f, 411.1111f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-944.4442f, -169.4443f ) ); _q->setSize( Vector2( 150.3689f, 150.3689f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-886.1108f, -513.8888f ) ); _q->setSize( Vector2( 159.8058f, 186.773f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-983.3334f, 219.4445f ) ); _q->setSize( Vector2( 281.6637f, 206.5533f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_ITALIAN )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1180.111f, 505.5556f ) ); _item->MyText->setScale( 0.6251668f ); _item->MySelectedText->setScale( 0.6251668f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-646.8889f, 266.6737f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-641.3332f, 91.67379f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-808.f, -424.993f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-1138.888f, 788.8889f ) ); _t->setScale( 1.1235f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8879f, -133.3333f ) ); _t->setScale( 0.7865838f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5541f, -391.6666f ) ); _t->setScale( 0.7871667f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-652.777f, 127.7778f ) ); _t->setScale( 0.84325f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-847.2215f, -286.111f ) ); _q->setSize( Vector2( 130.5354f, 130.5354f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-844.4448f, -522.2222f ) ); _q->setSize( Vector2( 101.0536f, 118.1064f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-913.8881f, -38.88887f ) ); _q->setSize( Vector2( 220.6411f, 161.8035f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1063.444f, 513.8889f ) ); _item->MyText->setScale( 0.5346668f ); _item->MySelectedText->setScale( 0.5346668f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-508.0002f, 330.5626f ) ); _item->MyText->setScale( 0.5419167f ); _item->MySelectedText->setScale( 0.5419167f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-291.3332f, 147.2363f ) ); _item->MyText->setScale( 0.5166666f ); _item->MySelectedText->setScale( 0.5166666f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-880.2227f, -341.6455f ) ); _item->MyText->setScale( 0.5209166f ); _item->MySelectedText->setScale( 0.5209166f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-719.4445f, 22.22227f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-661.1107f, -402.7777f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-655.5553f, 411.1111f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-955.5555f, -141.6665f ) ); _q->setSize( Vector2( 168.1188f, 168.1188f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-886.1108f, -513.8888f ) ); _q->setSize( Vector2( 180.9532f, 211.6065f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-983.3334f, 230.5556f ) ); _q->setSize( Vector2( 321.4366f, 235.7202f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1018.999f, 508.3333f ) ); _item->MyText->setScale( 0.6360832f ); _item->MySelectedText->setScale( 0.6360832f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-646.8889f, 266.6737f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-641.3332f, 91.67379f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-808.f, -424.993f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-719.4445f, 22.22227f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-661.1107f, -402.7777f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-655.5553f, 411.1111f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-955.5555f, -141.6665f ) ); _q->setSize( Vector2( 168.1188f, 168.1188f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-886.1108f, -513.8888f ) ); _q->setSize( Vector2( 180.9532f, 211.6065f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-983.3334f, 230.5556f ) ); _q->setSize( Vector2( 321.4366f, 235.7202f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_JAPANESE )
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-624.5549f, 522.2223f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-416.3333f, 269.4515f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-441.3332f, 94.45156f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-630.2217f, -330.5486f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
				else
				{
					boost::shared_ptr<MenuItem> _item;
					_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-846.7776f, 516.6667f ) ); _item->MyText->setScale( 0.78f ); _item->MySelectedText->setScale( 0.78f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Save" ); if (_item != 0 ) { _item->setSetPos( Vector2(-416.3333f, 269.4515f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"Replay" ); if (_item != 0 ) { _item->setSetPos( Vector2(-591.3332f, 86.11825f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
					_item = MyMenu->FindItemByName( L"" ); if (_item != 0 ) { _item->setSetPos( Vector2(-774.666f, -338.8819f ) ); _item->MyText->setScale( 0.6f ); _item->MySelectedText->setScale( 0.6f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

					MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"LevelCleared" ); if (_t != 0 ) { _t->setPos( Vector2(-930.5547f, 797.2222f ) ); _t->setScale( 1.195833f ); }
					_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-638.8889f, -2.777716f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Blobs" ); if (_t != 0 ) { _t->setPos( Vector2(-630.5551f, -386.1111f ) ); _t->setScale( 1.f ); }
					_t = MyPile->FindEzText( L"Deaths" ); if (_t != 0 ) { _t->setPos( Vector2(-636.111f, 388.8889f ) ); _t->setScale( 1.f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Dark" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 8888.887f, 5000.f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77808f, -6.666618f ) ); _q->setSize( Vector2( 1509.489f, 943.4307f ) ); }
					_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5555f, -163.8887f ) ); _q->setSize( Vector2( 174.7021f, 174.7021f ) ); }
					_q = MyPile->FindQuad( L"Stopwatch" ); if (_q != 0 ) { _q->setPos( Vector2(-916.6664f, -522.2221f ) ); _q->setSize( Vector2( 177.0607f, 206.9397f ) ); }
					_q = MyPile->FindQuad( L"Death" ); if (_q != 0 ) { _q->setPos( Vector2(-969.4437f, 202.7778f ) ); _q->setSize( Vector2( 291.891f, 214.0534f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
			}
	}

bool ScoreScreen::UseZoomIn = true;

	void ScoreScreen::OnAdd()
	{
		 CkBaseMenu::OnAdd();

		if ( UseZoomIn )
		{
			SlideIn( 0 );
			std::vector<Vector2> copy = std::vector<Vector2>( DrawPile::BubbleScale.size() );
			for ( int i = 0; i < static_cast<int>( DrawPile::BubbleScale.size() ); ++i )
			{
				copy[ i ] = ( DrawPile::BubbleScale[ i ] - Vector2(1) ) *.3f + Vector2(1);
			}
			zoom->MultiLerp( 6, copy );
		}

		// Calculate scores
		PlayerManager::CalcScore( MyStatGroup );

		int Coins = PlayerManager::PlayerSum( boost::make_shared<VariableCoinsLambda>( MyStatGroup ) );
		int CoinTotal = PlayerManager::PlayerMax( boost::make_shared<VariableTotalCoinsLambda>( MyStatGroup ) );
		int Blobs = PlayerManager::PlayerSum( boost::make_shared<VariableBlobsLambda>( MyStatGroup ) );
		int BlobTotal = PlayerManager::PlayerMax( boost::make_shared<VariableTotalBlobsLambda>( MyStatGroup ) );

		boost::shared_ptr<EzText> text;

		text = boost::make_shared<EzText>( Tools::ScoreString( Coins, CoinTotal ), ItemFont, std::wstring( std::wstring( L"Coins" ) ) );
		MyPile->Add( text );
		SetHeaderProperties( text);

		text = boost::make_shared<EzText>( CoreMath::ShortTime( PlayerManager::Score_Time ), ItemFont, std::wstring( std::wstring( L"Blobs" ) ) );
		MyPile->Add( text );
		SetHeaderProperties( text);

		text = boost::make_shared<EzText>( Tools::ScoreString( PlayerManager::Score_Attempts ), ItemFont, std::wstring( std::wstring( L"Deaths" ) ) );
		MyPile->Add( text );
		SetHeaderProperties( text);


		// Prevent menu interactions for a second
		MyMenu->Active = false;

		SetPos();
		MyMenu->SortByHeight();

		MyGame->WaitThenDo( DelayPhsx, boost::make_shared<OnAddHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
	}

	void ScoreScreen::MyDraw()
	{
		if ( getCore()->MyLevel->Replay || getCore()->MyLevel->Watching )
			return;

		Vector2 SaveZoom = MyGame->getCam()->getZoom();
		Vector2 SaveHoldZoom = MyGame->getCam()->HoldZoom;
		Tools::QDrawer->Flush();

		if ( zoom != 0 )
		{
			MyGame->getCam()->setZoom(.001f * zoom->Update());
			MyGame->getCam()->SetVertexCamera();
			EzText::ZoomWithCamera_Override = true;
		}

		Pos->SetCenter( getCore()->MyLevel->getMainCamera(), true );
		Pos->Update();

		CkBaseMenu::MyDraw();

		Tools::Render->EndSpriteBatch();

		if ( zoom != 0 )
		{
			MyGame->getCam()->setZoom(SaveZoom);
			MyGame->getCam()->HoldZoom = SaveHoldZoom;
			MyGame->getCam()->SetVertexCamera();
			EzText::ZoomWithCamera_Override = false;
			Tools::QDrawer->Flush();
		}
	}

	void ScoreScreen::MyPhsxStep()
	{
		boost::shared_ptr<Level> level = getCore()->MyLevel;

		if ( level != 0 )
			level->setPreventReset( true );

		if ( level->Replay || level->Watching )
			return;

		if ( Active )
		{
			if ( !ShouldSkip() )
			{
				if ( ( !Tools::CurLevel->CanLoadLevels && !Tools::CurLevel->CanSaveLevel )
					|| ( PlayerManager::Players[ 0 ] && PlayerManager::Players[ 0 ]->MySavedSeeds->SeedStrings.size() >= MAX_SEED_STRINGS ) )
				{
					boost::shared_ptr<MenuItem> item = MyMenu->FindItemByName( L"Save" );
					if ( item != 0 && !item->GrayOutOnUnselectable )
					{
						item->Selectable = false;
						item->GrayOutOnUnselectable = true;
						item->GrayOut();
						MyMenu->SelectItem( 0 );

						CloudberryKingdomGame::ChangeSaveGoFunc( item );
					}
				}

				if ( AsMenu )
					CkBaseMenu::MyPhsxStep();
				else
					GUI_Phsx();
			}
		}
	}

	void ScoreScreen::MenuGo_NewLevel( const boost::shared_ptr<MenuItem> &item )
	{
		GUI_Panel::SlideOut( PresetPos_LEFT );

		Active = false;

		//Tools::SongWad->FadeOut();
		MyGame->EndMusicOnFinish = false;

		MyGame->WaitThenDo( 36, boost::make_shared<ScoreScreenEndGameHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ), true ) );
		return;
	}

	void ScoreScreen::MenuGo_Continue( const boost::shared_ptr<MenuItem> &item )
	{
		SaveGroup::SaveAll();

		GUI_Panel::SlideOut( PresetPos_LEFT );

		if (InCampaign)
		{
			boost::shared_ptr<StringWorldGameData> stringworld = boost::dynamic_pointer_cast<StringWorldGameData>( Tools::WorldMap );

			boost::shared_ptr<Door> door = boost::dynamic_pointer_cast<Door>( Tools::CurLevel->FindIObject( LevelConnector::EndOfLevelCode ) );
			door->setOnOpen( boost::make_shared<LevelSeedData::EOL_DoorActionProxy>() );

			if ( stringworld != 0 )
			{
				bool fade = door->getMyLevel()->MyLevelSeed != 0 && door->getMyLevel()->MyLevelSeed->FadeOut;
				if (fade)
					door->setOnEnter( boost::make_shared<LevelSeedData::EOL_StringWorldDoorEndAction_WithFadeProxy>( stringworld ) );
				else
					door->setOnEnter( boost::make_shared<EOL_WaitThenDoEndActionProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
								   
				stringworld->EOL_StringWorldDoorAction( door );
			}
		}
		else
		{
			MyGame->WaitThenDo( SlideOutLength + 2, boost::make_shared<ScoreScreenEndGameHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ), false ) );
		}
	}

	void ScoreScreen::EOL_WaitThenDoEndAction( boost::shared_ptr<Door> door )
	{
		boost::shared_ptr<StringWorldGameData> stringworld = boost::dynamic_pointer_cast<StringWorldGameData>( Tools::WorldMap );

		if ( stringworld != 0 )
		{
			door->getGame()->WaitThenDo( 35, boost::make_shared<EOL_WaitThenDoEndActionWaitProxy>( stringworld, door ) );
		}
	}

	void ScoreScreen::MenuGo_ExitFreeplay( const boost::shared_ptr<MenuItem> &item )
	{
		GUI_Panel::SlideOut( PresetPos_LEFT );

		//if ( MyGame->ParentGame != 0 )
		//{
		//	CustomLevel_GUI::ExitFreeplay = true;
		//}

		MyGame->WaitThenDo( SlideOutLength + 2, boost::make_shared<ScoreScreenEndGameHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ), false ) );
	}

	void ScoreScreen::MenuGo_ExitCampaign( boost::shared_ptr<MenuItem> item )
	{
		Tools::CurrentAftermath = boost::make_shared<AftermathData>();
		Tools::CurrentAftermath->Success = false;
		Tools::CurrentAftermath->EarlyExit = true;

		Tools::CurGameData->EndGame->Apply( false );
	}

	void ScoreScreen::MenuGo_Stats( const boost::shared_ptr<MenuItem> &item )
	{
		Call( MakeMagic( StatsMenu, ( MyStatGroup ) ), 19 );
	}

	void ScoreScreen::MenuGo_WatchReplay( const boost::shared_ptr<MenuItem> &item )
	{
		if ( AsMenu )
		{
			Active = false;

			MyGame->WaitThenDo( 35, boost::make_shared<MenuGo_WatchReplayHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
		}
		else
		{
			getCore()->MyLevel->WatchReplay(true);
		}
	}

	void ScoreScreen::MenuGo_Save( const boost::shared_ptr<MenuItem> &item )
	{
        if ( CloudberryKingdomGame::getIsDemo() )
        {
            Call( MakeMagic( UpSellMenu, ( Localization::Words_UpSell_SaveLoad, MenuItem::ActivatingPlayer ) ), 0);
            Hide( PresetPos_LEFT, 0 );
        }
        else if ( CloudberryKingdomGame::CanSave() )
        {
			boost::shared_ptr<PlayerData> player = MenuItem::GetActivatingPlayerData();
			SaveLoadSeedMenu::MakeSave( boost::static_pointer_cast<SaveLoadSeedMenu>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ), player )->Apply( item );
			Hide( PresetPos_LEFT );
		}
		else
		{
			CloudberryKingdomGame::ShowError_CanNotSaveNoDevice();
		}
	}

	bool ScoreScreen::ShouldSkip()
	{
		if ( LastActive + 5 < Tools::TheGame->PhsxCount )
		{
			LastActive = Tools::TheGame->PhsxCount;
			return true;
		}
		else
		{
			LastActive = Tools::TheGame->PhsxCount;
			return false;
		}
	}

	void ScoreScreen::GUI_Phsx()
	{
		boost::shared_ptr<Level> level = getCore()->MyLevel;

		if ( MyGame->MyLevel->getReplayAvailable() )
		{
			bool WatchReplay = false;
			if ( level->CanWatchReplay && ButtonCheck::State( ControllerButtons_X, -1 ).Pressed )
				WatchReplay = true;
	#if defined(PC_VERSION)
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Escape ) || KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_Escape ) )
			WatchReplay = false;
	#endif

			if ( WatchReplay )
				MenuGo_WatchReplay( 0 );
		}

		if ( ButtonCheck::State( ControllerButtons_A, -1 ).Pressed )
			MenuGo_Continue( 0 );
	}

	void ScoreScreen::InitializeInstanceFields()
	{
		DelayPhsx = 5;
		ShiftAll = Vector2( -110, -20 );
		zoom = boost::make_shared<FancyVector2>();
		MyStatGroup = StatGroup_LEVEL;
	}
}
