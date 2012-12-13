#include <global_header.h>

namespace CloudberryKingdom
{

	GUI_LivesLeft::BringStartDelayHelper::BringStartDelayHelper( const std::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::BringStartDelayHelper::Apply()
	{
		if ( guiLl->PauseOnShow )
		{
			guiLl->setPauseLevel( false );
			guiLl->MyGame->MyLevel->setPreventReset( false );
		}
	}

	GUI_LivesLeft::BringShowLengthHelper::BringShowLengthHelper( const std::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::BringShowLengthHelper::Apply()
	{
		guiLl->MyPile->AlphaVel = guiLl->FadeOutVel;
		guiLl->MyGame->CinematicToDo( guiLl->StartDelay, std::make_shared<BringStartDelayHelper>( guiLl ) );
	}

	GUI_LivesLeft::BringInitialDelayHelper::BringInitialDelayHelper( const std::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::BringInitialDelayHelper::Apply()
	{
		guiLl->MyPile->AlphaVel = guiLl->FadeInVel;
		guiLl->MyGame->CinematicToDo( guiLl->ShowLength, std::make_shared<BringShowLengthHelper>( guiLl ) );
	}

	GUI_LivesLeft::OnResetProxy::OnResetProxy( const std::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::OnResetProxy::Apply()
	{
		guiLl->OnReset();
	}

	GUI_LivesLeft::OnDoneDyingProxy::OnDoneDyingProxy( const std::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::OnDoneDyingProxy::Apply()
	{
		guiLl->OnDoneDying();
	}

	GUI_LivesLeft::OnDeathProxy::OnDeathProxy( const std::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::OnDeathProxy::Apply()
	{
		guiLl->OnDeath();
	}

	const int &GUI_LivesLeft::getNumLives() const
	{
		return _NumLives;
	}

	void GUI_LivesLeft::setNumLives( const int &value )
	{
		_NumLives = value;
		UpdateLivesLeftText();
	}

	std::wstring GUI_LivesLeft::ToString()
	{
		return _T( "x " ) + StringConverterHelper::toString( getNumLives() );
	}

	void GUI_LivesLeft::UpdateLivesLeftText()
	{
		LivesLeftText->SubstituteText( ToString() );
	}

	GUI_LivesLeft::GUI_LivesLeft( int Lives ) { }
	void GUI_LivesLeft::GUI_LivesLeft_Construct( int Lives )
	{
		GUI_Panel::GUI_Panel_Construct();

		InitializeInstanceFields();
		SetParams();

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		_NumLives = Lives;

		MyPile = std::make_shared<DrawPile>();
		MyPile->FancyPos->UpdateWithGame = true;

		MyPile->Add( std::make_shared<QuadClass>( _T( "Bob_Stand_0001" ), 130.f, true ), _T( "Bob" ) );

		LivesLeftText = std::make_shared<EzText>( ToString(), Resources::Font_Grobold42, 450.f, false, true );
		LivesLeftText->Name = _T( "Text" );
		LivesLeftText->setScale( .53f );
		LivesLeftText->setPos( Vector2( 187, -16 ) );
		LivesLeftText->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		LivesLeftText->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();

		LivesLeftText->ShadowOffset = Vector2( -11, 11 );
		LivesLeftText->ShadowColor = bColor( 65, 65, 65, 160 );
		LivesLeftText->PicShadow = false;
		MyPile->Add( LivesLeftText );

		SetPos();

		// Hide initially
		MyPile->setAlpha( 0 );
	}

	void GUI_LivesLeft::SetPos()
	{
		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Text" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 195.3334f, -43.77777f ) );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Bob" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 133.3333f, -27.77774f ) );
			_q->ScaleYToMatchRatio( 82.5f );
		}

		MyPile->setPos( Vector2( -222.2232f, 897.222f ) );
	}

	void GUI_LivesLeft::SetParams()
	{
		FadeInVel = .04325f;
		FadeOutVel = -FadeInVel;

		//UseBlackBack = true;
		//FadeInVel = 1f;
		//FadeOutVel = -.07f;

		InitialDelay = 20;
		ShowLength = 90;
		StartDelay = 30;
	}

	void GUI_LivesLeft::Bring()
	{
		if ( PauseOnShow )
		{
			setPauseLevel( true );
			MyGame->MyLevel->setPreventReset( true );
		}

		// Fade in and out
		MyPile->setAlpha( 0 );
		MyGame->WaitThenDo( InitialDelay, std::make_shared<BringInitialDelayHelper>( std::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ), _T( "Start lives left bring" ), true, false );
	}

	void GUI_LivesLeft::Reset( bool BoxesOnly )
	{
		GUI_Panel::Reset( BoxesOnly );

		if ( !getCore()->MyLevel->Watching && getCore()->MyLevel->PlayMode == 0 )
			Bring();
	}

	void GUI_LivesLeft::OnAdd()
	{
		GUI_Panel::OnAdd();

		// Black background
		if ( UseBlackBack )
		{
			std::shared_ptr<QuadClass> Black = std::make_shared<QuadClass>( _T( "White" ), 1.f );
			Black->FullScreen( MyGame->getCam() );
			Black->Quad_Renamed.SetColor( Color::Black );
			Black->Scale( 2 );
			MyPile->Insert( 0, Black );
		}

		MyGame->ToDoOnReset.push_back( std::make_shared<OnResetProxy>( std::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );
		//MyGame.ToDoOnDoneDying.Add(OnDoneDying);
		MyGame->ToDoOnDeath.push_back( std::make_shared<OnDeathProxy>( std::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );

		if ( MyGame->MyLevel != 0 )
			PreventResetOnLastLife( MyGame->MyLevel );
	}

	void GUI_LivesLeft::OnReset()
	{
		MyGame->ToDoOnReset.push_back( std::make_shared<OnResetProxy>( std::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );

		std::shared_ptr<Level> level = getCore()->MyLevel;

		 if ( !MyGame->FreeReset )
			setNumLives( getNumLives() - 1 );

		PreventResetOnLastLife( level );
	}

	void GUI_LivesLeft::PreventResetOnLastLife( const std::shared_ptr<Level> &level )
	{
		// If only 1 life remains.
		if ( getNumLives() == LastLife )
		{
			// Prevent quickspawn and watching the computer from afar
			level->MyGame->SuppressQuickSpawn_External = true;
			level->CanWatchComputerFromAfar_External = false;
		}
		else if ( getNumLives() > LastLife )
		{
			level->MyGame->SuppressQuickSpawn_External = false;
			level->CanWatchComputerFromAfar_External = true;
		}
	}

	void GUI_LivesLeft::OnDoneDying()
	{
		MyGame->ToDoOnDoneDying.push_back( std::make_shared<OnDoneDyingProxy>( std::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );

		if ( getNumLives() == LastLife )
		{
			//Core.MyLevel.MyGame.AddGameObject(new GameOverPanel());
			if ( OnOutOfLives != 0 )
				OnOutOfLives->Apply( std::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) );

			Release();
			return;
		}
	}

	void GUI_LivesLeft::OnDeath()
	{
		MyGame->ToDoOnDeath.push_back( std::make_shared<OnDeathProxy>( std::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );

		if ( getNumLives() == LastLife )
		{
			//Core.MyLevel.MyGame.AddGameObject(new GameOverPanel());
			if ( OnOutOfLives != 0 )
				OnOutOfLives->Apply( std::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) );

			Release();
			return;
		}
	}

	void GUI_LivesLeft::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( MyGame->MyLevel != 0 )
			PreventResetOnLastLife( MyGame->MyLevel );
	}

	void GUI_LivesLeft::MyDraw()
	{
		GUI_Panel::MyDraw();
	}

	void GUI_LivesLeft::InitializeInstanceFields()
	{
		OnOutOfLives = std::make_shared<Multicaster_1<std::shared_ptr<GUI_LivesLeft> > >();
		_NumLives = 2;
		UseBlackBack = false;
		PauseOnShow = false;
		LastLife = 0;
	}
}
