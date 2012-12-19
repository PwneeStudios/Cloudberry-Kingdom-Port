#include <global_header.h>

namespace CloudberryKingdom
{

	GUI_LivesLeft::BringStartDelayHelper::BringStartDelayHelper( const boost::shared_ptr<GUI_LivesLeft> &guiLl )
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

	GUI_LivesLeft::BringShowLengthHelper::BringShowLengthHelper( const boost::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::BringShowLengthHelper::Apply()
	{
		guiLl->MyPile->AlphaVel = guiLl->FadeOutVel;
		guiLl->MyGame->CinematicToDo( guiLl->StartDelay, boost::make_shared<BringStartDelayHelper>( guiLl ) );
	}

	GUI_LivesLeft::BringInitialDelayHelper::BringInitialDelayHelper( const boost::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::BringInitialDelayHelper::Apply()
	{
		guiLl->MyPile->AlphaVel = guiLl->FadeInVel;
		guiLl->MyGame->CinematicToDo( guiLl->ShowLength, boost::make_shared<BringShowLengthHelper>( guiLl ) );
	}

	GUI_LivesLeft::OnResetProxy::OnResetProxy( const boost::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::OnResetProxy::Apply()
	{
		guiLl->OnReset();
	}

	GUI_LivesLeft::OnDoneDyingProxy::OnDoneDyingProxy( const boost::shared_ptr<GUI_LivesLeft> &guiLl )
	{
		this->guiLl = guiLl;
	}

	void GUI_LivesLeft::OnDoneDyingProxy::Apply()
	{
		guiLl->OnDoneDying();
	}

	GUI_LivesLeft::OnDeathProxy::OnDeathProxy( const boost::shared_ptr<GUI_LivesLeft> &guiLl )
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
		return std::wstring( L"x " ) + StringConverterHelper::toString( getNumLives() );
	}

	void GUI_LivesLeft::UpdateLivesLeftText()
	{
		LivesLeftText->SubstituteText( ToString() );
	}

	GUI_LivesLeft::GUI_LivesLeft( int Lives ) :
		PauseOnShow( false ),
		_NumLives( 0 ),
		UseBlackBack( false ),
		FadeInVel( 0 ), FadeOutVel( 0 ),
		InitialDelay( 0 ), ShowLength( 0 ), StartDelay( 0 ),
		LastLife( 0 )
	{
	}
	boost::shared_ptr<GUI_LivesLeft> GUI_LivesLeft::GUI_LivesLeft_Construct( int Lives )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		SetParams();

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		_NumLives = Lives;

		MyPile = boost::make_shared<DrawPile>();
		MyPile->FancyPos->UpdateWithGame = true;

		MyPile->Add( boost::make_shared<QuadClass>( std::wstring( L"Bob_Stand_0001" ), 130.f, true ), std::wstring( L"Bob" ) );

		LivesLeftText = boost::make_shared<EzText>( ToString(), Resources::Font_Grobold42, 450.f, false, true );
		LivesLeftText->Name = std::wstring( L"Text" );
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

		return boost::static_pointer_cast<GUI_LivesLeft>( shared_from_this() );
	}

	void GUI_LivesLeft::SetPos()
	{
		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"Text" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 195.3334f, -43.77777f ) );
		}

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"Bob" ) );
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
		MyGame->WaitThenDo( InitialDelay, boost::make_shared<BringInitialDelayHelper>( boost::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ), std::wstring( L"Start lives left bring" ), true, false );
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
			boost::shared_ptr<QuadClass> Black = boost::make_shared<QuadClass>( std::wstring( L"White" ), 1.f );
			Black->FullScreen( MyGame->getCam() );
			Black->Quad_Renamed.SetColor( Color::Black );
			Black->Scale( 2 );
			MyPile->Insert( 0, Black );
		}

		MyGame->ToDoOnReset.push_back( boost::make_shared<OnResetProxy>( boost::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );
		//MyGame.ToDoOnDoneDying.Add(OnDoneDying);
		MyGame->ToDoOnDeath.push_back( boost::make_shared<OnDeathProxy>( boost::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );

		if ( MyGame->MyLevel != 0 )
			PreventResetOnLastLife( MyGame->MyLevel );
	}

	void GUI_LivesLeft::OnReset()
	{
		MyGame->ToDoOnReset.push_back( boost::make_shared<OnResetProxy>( boost::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );

		boost::shared_ptr<Level> level = getCore()->MyLevel;

		 if ( !MyGame->FreeReset )
			setNumLives( getNumLives() - 1 );

		PreventResetOnLastLife( level );
	}

	void GUI_LivesLeft::PreventResetOnLastLife( const boost::shared_ptr<Level> &level )
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
		MyGame->ToDoOnDoneDying.push_back( boost::make_shared<OnDoneDyingProxy>( boost::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );

		if ( getNumLives() == LastLife )
		{
			//Core.MyLevel.MyGame.AddGameObject(new GameOverPanel());
			if ( OnOutOfLives != 0 )
				OnOutOfLives->Apply( boost::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) );

			Release();
			return;
		}
	}

	void GUI_LivesLeft::OnDeath()
	{
		MyGame->ToDoOnDeath.push_back( boost::make_shared<OnDeathProxy>( boost::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) ) );

		if ( getNumLives() == LastLife )
		{
			//Core.MyLevel.MyGame.AddGameObject(new GameOverPanel());
			if ( OnOutOfLives != 0 )
				OnOutOfLives->Apply( boost::static_pointer_cast<GUI_LivesLeft>( shared_from_this() ) );

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
		OnOutOfLives = boost::make_shared<Multicaster_1<boost::shared_ptr<GUI_LivesLeft> > >();
		_NumLives = 2;
		UseBlackBack = false;
		PauseOnShow = false;
		LastLife = 0;
	}
}
