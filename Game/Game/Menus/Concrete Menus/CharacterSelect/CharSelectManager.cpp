#include <global_header.h>

#include <Hacks/List.h>
#include <MasterHack.h>
#include <Core\Tools\Set.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

namespace CloudberryKingdom
{

	void CharacterSelectManager::InitializeStatics()
	{
		CharacterSelectManager::instance = boost::make_shared<CharacterSelectManager>();
	}

	// Statics
	boost::shared_ptr<Lambda> CharacterSelectManager::OnBack, CharacterSelectManager::OnDone;
	boost::shared_ptr<GUI_Panel> CharacterSelectManager::ParentPanel;
	boost::shared_ptr<CharacterSelectManager> CharacterSelectManager::instance;



	CharacterSelectManager::SignInGamerLambda::SignInGamerLambda( const boost::shared_ptr<SignedInEventArgs> &e )
	{
		this->e = e;
	}

	void CharacterSelectManager::SignInGamerLambda::Apply()
	{
		int index = static_cast<int>( e->_Gamer.MyPlayerIndex );
		boost::shared_ptr<CharacterSelect> select = CharSelect[ index ];
		if ( select != 0 )
		{
			select->InitColorScheme( index );
		}
	}

	void CharacterSelectManager::_StartAllProxy::Apply()
	{
		CharacterSelectManager::_StartAll();
	}

	CharacterSelectManager::NullLambda::NullLambda()
	{
	}

	bool CharacterSelectManager::NullLambda::Apply( const boost::shared_ptr<CharacterSelect> &select )
	{
		return select == 0;
	}
	
	void CharacterSelectManager::AfterFinishedHelper::Apply()
	{
		CharacterSelectManager::AfterFinished();
	}

	void CharacterSelectManager::QuickJoinFinishHelper::Apply()
	{
		CharacterSelectManager::QuickJoinFinish();
	}

	const boost::shared_ptr<CharacterSelectManager> &CharacterSelectManager::getInstance()
	{
		return instance;
	}

	static boost::shared_ptr<CharacterSelect>  tempVector[] = { 0, 0, 0, 0 };
	std::vector<boost::shared_ptr<CharacterSelect> > CharacterSelectManager::CharSelect = VecFromArray( tempVector );
	bool CharacterSelectManager::IsShowing = false;
	boost::shared_ptr<FancyVector2> CharacterSelectManager::CamPos = 0;
	boost::shared_ptr<EzText> CharacterSelectManager::ChooseYourHero_Text = 0;
	bool CharacterSelectManager::Show_ChooseYourHero = false;
	int CharacterSelectManager::ChooseYourHero_LerpLength = 100;
	Vector2 HidePos, CharacterSelectManager::ShowPos = Vector2( 50.79541f, 900.1587f );

	CharacterSelectManager::CharacterSelectManager()
	{
		CamPos = boost::make_shared<FancyVector2>();

	#if defined(XBOX) || defined(XBOX_SIGNIN)
		SignedInGamer::SignedIn += boost::make_shared<System::EventHandler<SignedInEventArgs*> >( shared_from_this(), &CharacterSelectManager::SignedInGamer_SignedIn );
	#endif
	}

#if defined(XBOX) || defined(XBOX_SIGNIN)
	void CharacterSelectManager::SignedInGamer_SignedIn( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<SignedInEventArgs> &e )
	{
		if ( CharSelect.empty() )
			return;

		UpdateAvailableHats();

		// Get the signed in player's saved color scheme and set the character select accordingly
		Tools::CurGameData->AddToDo( boost::make_shared<SignInGamerLambda>( e ) );
	}
#endif

boost::shared_ptr<Set<boost::shared_ptr<Hat> > > CharacterSelectManager::AvailableHats = 0;

	void CharacterSelectManager::UpdateAvailableHats()
	{
		UpdateAvailableBeards();

		// Determine which hats are availabe
		AvailableHats = boost::make_shared<Set<boost::shared_ptr<Hat> > >();
		for ( std::vector<boost::shared_ptr<Hat> >::const_iterator hat = ColorSchemeManager::HatInfo.begin(); hat != ColorSchemeManager::HatInfo.end(); ++hat )
			//if ( *hat == Hat::None || ( *hat )->AssociatedAward == 0 && PlayerManager::Bought( *hat ) || ( *hat )->AssociatedAward != 0 && PlayerManager::Awarded( ( *hat )->AssociatedAward ) || CloudberryKingdomGame::UnlockAll )
				AvailableHats->Add( *hat );
	}

	boost::shared_ptr<Set<boost::shared_ptr<Hat> > > CharacterSelectManager::AvailableBeards = 0;

	void CharacterSelectManager::UpdateAvailableBeards()
	{
		// Determine which Beards are availabe
		AvailableBeards = boost::make_shared<Set<boost::shared_ptr<Hat> > >();
		for ( std::vector<boost::shared_ptr<Hat> >::const_iterator Beard = ColorSchemeManager::BeardInfo.begin(); Beard != ColorSchemeManager::BeardInfo.end(); ++Beard )
			//if ( *Beard == Hat::None || ( *Beard )->AssociatedAward == 0 && PlayerManager::Bought( *Beard ) || ( *Beard )->AssociatedAward != 0 && PlayerManager::Awarded( ( *Beard )->AssociatedAward ) || CloudberryKingdomGame::UnlockAll )
				AvailableBeards->Add( *Beard );
	}

	boost::shared_ptr<CharSelectBackdrop> CharacterSelectManager::Backdrop = 0;
	bool CharacterSelectManager::QuickJoin = false;

	void CharacterSelectManager::Start( const boost::shared_ptr<GUI_Panel> &Parent, bool QuickJoin )
	{
		if ( !QuickJoin )
		{
			CloudberryKingdomGame::SetPresence( Presence_TitleScreen );
		}

        FakeHide = false;
        CharacterSelectManager::QuickJoin = QuickJoin;

        boost::shared_ptr<GameData> game = 0;
        if ( Parent == 0 )
            game = Tools::CurGameData;
        else
            game = Parent->MyGame;

		ParentPanel = Parent;

		// Add the backdrop
		Backdrop = MakeMagic( CharSelectBackdrop, () );
		game->AddGameObject( Backdrop );

		// Start the selects for each player
		game->WaitThenDo( 0, boost::make_shared<_StartAllProxy>(), std::wstring( L"StartCharSelect" ) );
	}

	void CharacterSelectManager::_StartAll()
	{
		for ( int i = 0; i < 4; i++ )
			Start( i, CharacterSelectManager::QuickJoin );
	}

	void CharacterSelectManager::Start( int PlayerIndex, bool QuickJoin )
	{
		Active = true;
		IsShowing = true;
		UpdateAvailableHats();

		// If the character select is already up just return
		if ( CharSelect[ PlayerIndex ] != 0 )
			return;

		//CharSelect[ PlayerIndex ] = boost::make_shared<CharacterSelect>( PlayerIndex, QuickJoin );
		//CharSelect[ PlayerIndex ] = MakeMagic( CharacterSelect, ( PlayerIndex, QuickJoin ) );
		
		CharSelect[ PlayerIndex ] = boost::make_shared<CharacterSelect>( CharacterSelect( PlayerIndex, QuickJoin ) );
		CharacterSelect_PostConstruct( CharSelect[ PlayerIndex ], PlayerIndex, QuickJoin );
	}

	void CharacterSelectManager::FinishAll()
	{
		for ( int i = 0; i < 4; i++ )
			if ( CharSelect[ i ] != 0 )
				Finish( i, CharacterSelectManager::QuickJoin );
	}

	void CharacterSelectManager::Finish( int PlayerIndex, bool Join )
	{
		if ( Join && !CharSelect[ PlayerIndex ]->Fake && CharSelect[ PlayerIndex ]->MyState == CharacterSelect::SelectState_WAITING )
		{
			Tools::CurGameData->CreateBob( PlayerIndex, true );
		}

		CharSelect[ PlayerIndex ]->Release();
		CharSelect[ PlayerIndex ].reset();
	}

	void CharacterSelectManager::EndCharSelect( int DelayOnReturn, int DelayKillCharSelect )
	{
		Cleanup();

		if ( CharacterSelectManager::ParentPanel != 0 )
			CharacterSelectManager::ParentPanel->Show();

		CharacterSelectManager::ParentPanel = 0;
	}

	void CharacterSelectManager::Cleanup()
	{
		boost::shared_ptr<CloudberryKingdom::GameData> game = Tools::CurGameData;

		CharacterSelectManager::FinishAll();

		game->KillToDo( std::wstring( L"StartCharSelect" ) );

		game->RemoveGameObjects( GameObject::Tag_CHAR_SELECT );
		if ( Backdrop != 0 ) Backdrop->Release();
	}

    void CharacterSelectManager::SuddenCleanup()
    {
        CharacterSelectManager::IsShowing = false;
        CharacterSelectManager::FakeHide = false;

        for ( int i = 0; i < 4; i++ )
        {
            if ( CharacterSelectManager::CharSelect[i] != 0 )
            {
                CharacterSelectManager::CharSelect[i]->Release();
                CharacterSelectManager::CharSelect[i].reset();
            }
        }

        boost::shared_ptr<GameData> game = Tools::CurGameData;

        game->KillToDo( std::wstring( L"StartCharSelect" ) );

        game->RemoveGameObjects( GameObject::Tag_CHAR_SELECT );
        if ( CharacterSelectManager::Backdrop != 0 ) CharacterSelectManager::Backdrop->Release();

        CharacterSelectManager::OnDone.reset();
        CharacterSelectManager::ParentPanel.reset();
    }

	bool CharacterSelectManager::AllExited()
	{
		bool All = true;
		for ( int i = 0; i < 4; i++ )
			if ( CharSelect[ i ] != 0 && !CharSelect[ i ]->Fake && CharSelect[ i ]->MyState != CharacterSelect::SelectState_BEGINNING )
				All = false;
		return All;
	}

	bool CharacterSelectManager::AllFinished()
	{
		// False if no one has joined
		bool SomeOneIsHere = false;
		for ( int i = 0; i < 4; i++ )
			if ( CharSelect[ i ] != 0 && 
				 !( CharSelect[ i ]->QuickJoin && CharSelect[ i ]->Fake ) &&
				 CharSelect[ i ]->MyState != CharacterSelect::SelectState_BEGINNING )
				SomeOneIsHere = true;

		if ( !SomeOneIsHere )
			return false;

		// Otherwise true if no one is still selecting
		bool All = true;
		for ( int i = 0; i < 4; i++ )
			if ( CharSelect[ i ] != 0 && CharSelect[ i ]->MyState == CharacterSelect::SelectState_SELECTING )
				All = false;
		return All;
	}

	bool CharacterSelectManager::AllNull()
	{
		return Tools::All<boost::shared_ptr<CharacterSelect> >( CharSelect, NullLambda_static );
	}

	boost::shared_ptr<CharacterSelectManager::NullLambda> CharacterSelectManager::NullLambda_static = boost::make_shared<CharacterSelectManager::NullLambda>();
	int CharacterSelectManager::DrawLayer = 10;
	float CharacterSelectManager::BobZoom = 2.6f;
	float CharacterSelectManager::ZoomMod = 1.1f;

	void CharacterSelectManager::Draw()
	{
        if ( FakeHide )
            return;

		if ( !IsShowing )
			return;

		boost::shared_ptr<Camera> cam = Tools::CurLevel->getMainCamera();
		Vector2 HoldZoom = cam->getZoom();
		cam->setZoom( Vector2( .001f,.001f ) / ZoomMod );
		cam->SetVertexCamera();

		CamPos->AbsVal = CamPos->RelVal = cam->Data.Position;

		// Draw the stickmen
		float setzoom = 0;
		for ( int i = 0; i < 4; i++ )
			if ( CharSelect[ i ] != 0 )
			{
				float _zoom = BobZoom;

				if ( setzoom != _zoom )
				{
					Tools::QDrawer->Flush();
					cam->SetVertexZoom( Vector2( _zoom ) );
					setzoom = BobZoom;
				}
				CharSelect[ i ]->MyDoll->DrawBob();
			}
		Tools::QDrawer->Flush();
		cam->SetVertexCamera();

		cam->setZoom( HoldZoom );
		cam->SetVertexCamera();
	}

	bool CharacterSelectManager::FakeHide = false;
	void CharacterSelectManager::AfterFinished()
	{
		IsShowing = false;
		FakeHide = false;

		Cleanup();
		if ( OnDone != 0 ) OnDone->Apply(); OnDone = 0;
		CharacterSelectManager::ParentPanel = 0;
	}

bool CharacterSelectManager::Active = false;

	void CharacterSelectManager::PhsxStep()
	{
		if ( !Active )
			return;

		if ( !IsShowing )
			return;

		if ( AllNull() )
			IsShowing = false;

		// Check for finishing from character selection
		if ( AllFinished() && IsShowing )
		{
			Active = false;

            if (QuickJoin)
                Tools::CurGameData->SlideOut_FadeIn( 0, boost::make_shared<QuickJoinFinishHelper>() );
                //Tools::CurGameData.WaitThenDo(0, AfterFinished);
            else
				Tools::CurGameData->SlideOut_FadeIn( 0, boost::make_shared<AfterFinishedHelper>() );
		}

		// Check for ready to exit from character selection
		if ( AllExited() && IsShowing )
		{
			if ( ButtonCheck::State( ControllerButtons_B, -2 ).Pressed )
			{
				Active = false;
				IsShowing = false;
				EndCharSelect( 0, 0 );
			}
		}
	}

    void CharacterSelectManager::QuickJoinFinish()
    {
        FakeHide = true;
        Tools::CurGameData->WaitThenDo( 12, boost::make_shared<AfterFinishedHelper>() );
    }
}
