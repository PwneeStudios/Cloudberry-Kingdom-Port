#include <global_header.h>



#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

namespace CloudberryKingdom
{

	CharacterSelectManager::SignInGamerLambda::SignInGamerLambda( const std::shared_ptr<SignedInEventArgs> &e )
	{
		this->e = e;
	}

	void CharacterSelectManager::SignInGamerLambda::Apply()
	{
		int index = static_cast<int>( e->Gamer.MyPlayerIndex );
		std::shared_ptr<CharacterSelect> select = CharSelect[ index ];
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

	bool CharacterSelectManager::NullLambda::Apply( const std::shared_ptr<CharacterSelect> &select )
	{
		return select == 0;
	}

	void CharacterSelectManager::AfterFinishedHelper::Apply()
	{
		CharacterSelectManager::AfterFinished();
	}

	std::shared_ptr<Lambda> OnBack, CharacterSelectManager::OnDone = 0;
	std::shared_ptr<GUI_Panel> CharacterSelectManager::ParentPanel = 0;

	const std::shared_ptr<CharacterSelectManager> CharacterSelectManager::instance = std::make_shared<CharacterSelectManager>();

	const std::shared_ptr<CharacterSelectManager> &CharacterSelectManager::getInstance()
	{
		return instance;
	}

	const std::shared_ptr<CharacterSelect>  tempVector[] = { 0, 0, 0, 0 };
	std::vector<std::shared_ptr<CharacterSelect> > CharacterSelectManager::CharSelect = std::vector<std::shared_ptr<CharacterSelect> >( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	bool CharacterSelectManager::IsShowing = false;
	std::shared_ptr<FancyVector2> CharacterSelectManager::CamPos = 0;
	std::shared_ptr<EzText> CharacterSelectManager::ChooseYourHero_Text = 0;
	bool CharacterSelectManager::Show_ChooseYourHero = false;
	int CharacterSelectManager::ChooseYourHero_LerpLength = 100;
	Vector2 HidePos, CharacterSelectManager::ShowPos = Vector2( 50.79541f, 900.1587f );

	CharacterSelectManager::CharacterSelectManager()
	{
		CamPos = std::make_shared<FancyVector2>();

	#if defined(XBOX) || defined(XBOX_SIGNIN)
		SignedInGamer::SignedIn += std::make_shared<System::EventHandler<SignedInEventArgs*> >( shared_from_this(), &CharacterSelectManager::SignedInGamer_SignedIn );
	#endif
	}

#if defined(XBOX) || defined(XBOX_SIGNIN)
	void CharacterSelectManager::SignedInGamer_SignedIn( const std::shared_ptr<void> &sender, const std::shared_ptr<SignedInEventArgs> &e )
	{
		if ( CharSelect.empty() )
			return;

		UpdateAvailableHats();

		// Get the signed in player's saved color scheme and set the character select accordingly
		Tools::CurGameData->AddToDo( std::make_shared<SignInGamerLambda>( e ) );
	}
#endif

std::shared_ptr<Set<std::shared_ptr<Hat> > > CharacterSelectManager::AvailableHats = 0;

	void CharacterSelectManager::UpdateAvailableHats()
	{
		UpdateAvailableBeards();

		// Determine which hats are availabe
		AvailableHats = std::make_shared<Set<std::shared_ptr<Hat> > >();
		for ( std::vector<std::shared_ptr<Hat> >::const_iterator hat = ColorSchemeManager::HatInfo.begin(); hat != ColorSchemeManager::HatInfo.end(); ++hat )
			if ( *hat == Hat::None || ( *hat )->AssociatedAward == 0 && PlayerManager::Bought( *hat ) || ( *hat )->AssociatedAward != 0 && PlayerManager::Awarded( ( *hat )->AssociatedAward ) || CloudberryKingdomGame::UnlockAll )
				AvailableHats->Add( *hat );
	}

	std::shared_ptr<Set<std::shared_ptr<Hat> > > CharacterSelectManager::AvailableBeards = 0;

	void CharacterSelectManager::UpdateAvailableBeards()
	{
		// Determine which Beards are availabe
		AvailableBeards = std::make_shared<Set<std::shared_ptr<Hat> > >();
		for ( std::vector<std::shared_ptr<Hat> >::const_iterator Beard = ColorSchemeManager::BeardInfo.begin(); Beard != ColorSchemeManager::BeardInfo.end(); ++Beard )
			if ( *Beard == Hat::None || ( *Beard )->AssociatedAward == 0 && PlayerManager::Bought( *Beard ) || ( *Beard )->AssociatedAward != 0 && PlayerManager::Awarded( ( *Beard )->AssociatedAward ) || CloudberryKingdomGame::UnlockAll )
				AvailableBeards->Add( *Beard );
	}

	std::shared_ptr<CharSelectBackdrop> CharacterSelectManager::Backdrop = 0;

	void CharacterSelectManager::Start( const std::shared_ptr<GUI_Panel> &Parent )
	{
		ParentPanel = Parent;

		// Add the backdrop
		Backdrop = std::make_shared<CharSelectBackdrop>();
		Parent->MyGame->AddGameObject( Backdrop );

		// Start the selects for each player
		Parent->MyGame->WaitThenDo( 0, std::make_shared<_StartAllProxy>(), _T("StartCharSelect") );
	}

	void CharacterSelectManager::_StartAll()
	{
		for ( int i = 0; i < 4; i++ )
			Start( i, false );
	}

	void CharacterSelectManager::Start( int PlayerIndex, bool QuickJoin )
	{
		Active = true;
		IsShowing = true;
		UpdateAvailableHats();

		// If the character select is already up just return
		if ( CharSelect[ PlayerIndex ] != 0 )
			return;

		CharSelect[ PlayerIndex ] = std::make_shared<CharacterSelect>( PlayerIndex, QuickJoin );
	}

	void CharacterSelectManager::FinishAll()
	{
		for ( int i = 0; i < 4; i++ )
			if ( CharSelect[ i ] != 0 )
				Finish( i, false );
	}

	void CharacterSelectManager::Finish( int PlayerIndex, bool Join )
	{
		if ( Join )
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
	}

	void CharacterSelectManager::Cleanup()
	{
		std::shared_ptr<CloudberryKingdom::GameData> game = Tools::CurGameData;

		CharacterSelectManager::FinishAll();

		game->KillToDo( _T( "StartCharSelect" ) );

		game->RemoveGameObjects( GameObject::Tag_CHAR_SELECT );
		Backdrop->Release();
	}

	bool CharacterSelectManager::AllExited()
	{
		bool All = true;
		for ( int i = 0; i < 4; i++ )
			if ( CharSelect[ i ] != 0 && CharSelect[ i ]->MyState != CharacterSelect::SelectState_BEGINNING )
				All = false;
		return All;
	}

	bool CharacterSelectManager::AllFinished()
	{
		// False if no one has joined
		bool SomeOneIsHere = false;
		for ( int i = 0; i < 4; i++ )
			if ( CharSelect[ i ] != 0 && CharSelect[ i ]->MyState != CharacterSelect::SelectState_BEGINNING )
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
		return Tools::All<std::shared_ptr<CharacterSelect> >( CharSelect, NullLambda_static );
	}

	std::shared_ptr<CharacterSelectManager::NullLambda> CharacterSelectManager::NullLambda_static = std::make_shared<CharacterSelectManager::NullLambda>();
	int CharacterSelectManager::DrawLayer = 10;
	float CharacterSelectManager::BobZoom = 2.6f;
	float CharacterSelectManager::ZoomMod = 1.1f;

	void CharacterSelectManager::Draw()
	{
		if ( !IsShowing )
			return;

		std::shared_ptr<Camera> cam = Tools::CurLevel->getMainCamera();
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

	void CharacterSelectManager::AfterFinished()
	{
		IsShowing = false;

		Cleanup();
		if ( OnDone != 0 )
			OnDone->Apply();
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
			Tools::CurGameData->SlideOut_FadeIn( 0, std::make_shared<AfterFinishedHelper>() );
		}

		// Check for ready to exit from character selection
		if ( AllExited() && IsShowing )
		{
			if ( ButtonCheck::State( ControllerButtons_B, -2 ).Pressed )
			{
				Active = false;
				EndCharSelect( 0, 0 );
			}
		}
	}
}
