#include <global_header.h>
namespace CloudberryKingdom
{

	PerfectScoreObject::OnCoinGrabProxy::OnCoinGrabProxy( const std::shared_ptr<PerfectScoreObject> &pso )
	{
		this->pso = pso;
	}

	void PerfectScoreObject::OnCoinGrabProxy::Apply( const std::shared_ptr<ObjectBase> &obj )
	{
		pso->OnCoinGrab( obj );
	}

	PerfectScoreObject::OnLevelRetryProxy::OnLevelRetryProxy( const std::shared_ptr<PerfectScoreObject> &pso )
	{
		this->pso = pso;
	}

	void PerfectScoreObject::OnLevelRetryProxy::Apply()
	{
		pso->OnLevelRetry();
	}

	const bool &PerfectScoreObject::getObtained() const
	{
		return _Obtained;
	}

	void PerfectScoreObject::setObtained( const bool &value )
	{
		_Obtained = value;
		if ( Global )
			GlobalObtained = _Obtained;
	}

	void PerfectScoreObject::OnAdd()
	{
		GUI_Panel::OnAdd();

		// Remove other perfect score objects
		for ( GameObjVec::const_iterator obj = MyGame->MyGameObjects.begin(); obj != MyGame->MyGameObjects.end(); ++obj )
		{
			if ( ( *obj ).get() == this )
				continue;
			if ( dynamic_cast<PerfectScoreObject*>( *obj ) != 0 )
				( *obj )->Release();
		}

		// If the player didn't get the bonus last level, reset the multiplier
		if ( !getObtained() )
			ResetMultiplier();
		setObtained( false );

		Eligible = true;

		MyGame->OnCoinGrab->Add( std::make_shared<OnCoinGrabProxy>( shared_from_this() ) );
		MyGame->OnLevelRetry->Add( std::make_shared<OnLevelRetryProxy>( shared_from_this() ) );

		OnAdd_GUI();
	}

	void PerfectScoreObject::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();

		//MyGame.OnCoinGrab -= OnCoinGrab;
		//MyGame.OnLevelRetry -= OnLevelRetry;
	}

	const int &PerfectScoreObject::getBaseBonus() const
	{
		return _BaseBonus;
	}

	void PerfectScoreObject::setBaseBonus( const int &value )
	{
		_BaseBonus = value;
		if ( getNextBonus() < getBaseBonus() )
			setNextBonus( getBaseBonus() );
	}

	const int &PerfectScoreObject::getNextBonus() const
	{
		return _NextBonus;
	}

	void PerfectScoreObject::setNextBonus( const int &value )
	{
		_NextBonus = __min( value, MaxBonus );
		if ( Global )
			GlobalBonus = _NextBonus;
	}

	void PerfectScoreObject::OnCoinGrab( const std::shared_ptr<ObjectBase> &obj )
	{
		if ( !Eligible )
			return;

		// Give the bonus?
		if ( PlayerManager::GetLevelCoins() == MyGame->MyLevel->NumCoins )
		{
			setObtained( true );
			BonusCount++;

			std::shared_ptr<PlayerData> player = obj->getCore()->InteractingPlayer;

			if ( player != 0 )
				player->LevelStats->Score += BonusValue();

			// Remove last coin score text
			MyGame->RemoveLastCoinText();

			// Add the visual effect
			Effect( obj->getCore()->Data.Position );

			// Increase the bonus
			setNextBonus( getNextBonus() + BonusIncrement );
		}

		UpdateScoreText();
	}

	int PerfectScoreObject::BonusValue()
	{
		return static_cast<int>( getNextBonus() * MyGame->ScoreMultiplier );
	}

	void PerfectScoreObject::Effect( Vector2 pos )
	{
		// Berries
		if ( BonusCount % 5 == 0 )
		{
			Tools::CurGameData->AddGameObject( std::make_shared<Cheer>() );
		}

		pos += Vector2( 110, 70 );

		// Text float
		std::shared_ptr<TextFloat> text = std::make_shared<TextFloat>( Localization::Words_PERFECT, pos + Vector2( 21, 22.5f ) );
		std::shared_ptr<TextFloat> text2 = std::make_shared<TextFloat>( StringConverterHelper::toString( BonusValue() ), pos + Vector2(21, -42.5f) );

		text->MyText->setScale( text->MyText->getScale() * 1.5f );
		MyGame->AddGameObject( text );

		text2->MyText->setScale( text2->MyText->getScale() * 1.5f );
		MyGame->AddGameObject( text2 );

		//ParticleEffects.CoinExplosion(MyGame.MyLevel, pos);
	}

	void PerfectScoreObject::OnLevelRetry()
	{
		if ( Count == 0 )
			return;
		if ( MyGame->FreeReset )
			return;

		if ( IneligibleOnDeath )
			Eligible = false;

		ResetMultiplier();
	}

	void PerfectScoreObject::ResetMultiplier()
	{
		setNextBonus( getBaseBonus() );
		BonusCount = 0;

		UpdateScoreText();
	}

bool PerfectScoreObject::GlobalObtained = false;
int PerfectScoreObject::GlobalBonus = 0;

	PerfectScoreObject::PerfectScoreObject( bool Global, bool ShowMultiplier )
	{
		// Object is carried over through multiple levels, so prevent it from being released.
		InitializeInstanceFields();
		PreventRelease = true;

		PauseOnPause = true;

		setBaseBonus( 1000 );
		BonusIncrement = 1000;
		MaxBonus = 8000;

		// Global modifer, keep track of multiplier across levels/games
		if ( Global )
		{
			this->Global = true;
			setObtained( GlobalObtained );
			setNextBonus( GlobalBonus );
		}

		this->ShowMultiplier = ShowMultiplier;

		Init_GUI();
	}

	const float &PerfectScoreObject::getMultiplier() const
	{
		if ( MyGame == 0 )
			return getNextBonus() / getBaseBonus();
		else
			return MyGame->ScoreMultiplier * getNextBonus() / getBaseBonus();
	}

	void PerfectScoreObject::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		Count++;
	}

	std::wstring PerfectScoreObject::ToString()
	{
		return _T( "x" ) + Format( _T( "{0:0.0}" ), getMultiplier() );
	}

	void PerfectScoreObject::OnAdd_GUI()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			//SlideOut(PresetPos.Top, 0);
			//SlideIn();
			//Show();
			SlideIn( 0 );
			Show();
		}

		AddedOnce = true;
	}

	void PerfectScoreObject::UpdateScoreText()
	{
		float Hold = getMultiplier();
		Text->SubstituteText( ToString() );

		if ( Hold != getMultiplier() )
			MyPile->BubbleUp( false );
	}

	void PerfectScoreObject::Init_GUI()
	{
		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		MyPile->setPos( Vector2( 1350, -800 ) );

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		std::shared_ptr<EzFont> font;
		float scale;
		Color c, o;

		font = Resources::Font_Grobold42;
		scale = .666f;
		c = Color( 228, 0, 69 );
		o = Color::White;

		Text = std::make_shared<EzText>( ToString(), font, 950, false, true );
		Text->setScale( scale );
		Text->setPos( Vector2( 0, 0 ) );
		Text->MyFloatColor = c.ToVector4();
		Text->OutlineColor = o.ToVector4();

		Text->RightJustify = true;

		MyPile->Add( Text );
	}

	void PerfectScoreObject::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints || !ShowMultiplier )
			return;

		GUI_Panel::MyDraw();
	}

	void PerfectScoreObject::InitializeInstanceFields()
	{
		Eligible = false;
		_Obtained = false;
		BonusCount = 0;
		IneligibleOnDeath = false;
		Count = 0;
		Global = false;
		ShowMultiplier = true;
		AddedOnce = false;
	}
}
