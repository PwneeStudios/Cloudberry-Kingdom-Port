#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	void InitialLoadingScreen::InitializeStatics()
	{
		InitialLoadingScreen::TotalResources = 805;
	}

	// Statics
	int InitialLoadingScreen::TotalResources;


	const Vector2 &ProgressBar::getFull_BL() const
	{
		return Outline->getBL();
	}

	const Vector2 &ProgressBar::getFull_TR() const
	{
		return Outline->getTR();
	}

	const Vector2 ProgressBar::getCurrent_TR() const
	{
		return Vector2( getFull_BL().X + (getFull_TR().X - getFull_BL().X) * PercentDone / 100, getFull_TR().Y );
	}

	const Vector2 &ProgressBar::getPos() const
	{
		return MyPile->getPos();
	}

	void ProgressBar::setPos( const Vector2 &value )
	{
		MyPile->setPos( value );
	}

	ProgressBar::ProgressBar()
	{
		InitializeInstanceFields();
		Initialize();

		InitStandardBar();
	}

	void ProgressBar::Initialize()
	{
		MyPile = boost::make_shared<DrawPile>();

		Outline = boost::make_shared<QuadClass>();
		Outline->SetToDefault();
		MyPile->Add( Outline );

		Fill = boost::make_shared<QuadClass>();
		Fill->SetToDefault();
		MyPile->Add( Fill );
	}

	void ProgressBar::InitStandardBar()
	{
		Outline->setTextureName( std::wstring( L"LoadOutline" ) );
		Outline->ScaleYToMatchRatio( 192 );

		Fill->setTextureName( std::wstring( L"LoadFill" ) );
		Fill->ScaleYToMatchRatio( 192 );
		Width = Fill->getSize().X;
	}

	ProgressBar::ProgressBar( const std::wstring &FillName, const std::wstring &OutlineName, float Width )
	{
		InitializeInstanceFields();
		Initialize();

		this->Width = Width;
		InitCustomBar( FillName, OutlineName, Width );
	}

	void ProgressBar::InitCustomBar( const std::wstring &FillName, const std::wstring &OutlineName, float Width )
	{
		Fill->setTextureName( FillName );
		Fill->ScaleYToMatchRatio( Width );

		Outline->setTextureName( OutlineName );
		Outline->ScaleYToMatchRatio( Width );

		this->Width = Width;

		Outline->Shadow = true;
		Outline->ShadowColor = Color( .2f,.2f,.2f, 1 );
		Outline->ShadowOffset = Vector2( 12, 12 );
	}

	void ProgressBar::SetPercent( float Percent )
	{
		setPos( Vector2( 0, -150 ) );

		PercentDone = Percent;

		float FillWidth = Width * PercentDone / 100;
		if ( FillWidth < .01f )
			FillWidth = .01f;
		Fill->setSize( Vector2( FillWidth, Fill->getSize().Y ) );
		Fill->setPos( Vector2( FillWidth - Width, Fill->getPos().Y ) );

		switch ( MyType )
		{
			case BarType_SCALE:
				break;

			case BarType_REVEAL:
				Fill->Quad_Renamed.v1.Vertex.uv.X = PercentDone / 100;
				Fill->Quad_Renamed.v3.Vertex.uv.X = PercentDone / 100;

				break;
		}
	}

	void ProgressBar::Draw()
	{
		MyPile->Draw();
	}

	void ProgressBar::Draw( bool Selected )
	{
		MyPile->Draw( Selected );
	}

	void ProgressBar::InitializeInstanceFields()
	{
		PercentDone = 0;
		Width = 0;

		MyType = BarType_SCALE;
	}

	InitialLoadingScreen::InitialLoadingScreen( const boost::shared_ptr<ContentManager> &Content, const boost::shared_ptr<WrappedFloat> &ResourceCount )
	{
		InitializeInstanceFields();
		this->ResourceCount = ResourceCount;

		//Whinney = Content->Load<SoundEffect>( std::wstring( L"Whinney" ) );

		//Tools::TextureWad->FindOrLoad( Content, std::wstring( L"Art/LoadScreen_Initial/LoadOutline" ) );
		//Tools::TextureWad->FindOrLoad( Content, std::wstring( L"Art/LoadScreen_Initial/LoadFill" ) );

		MyPile = boost::make_shared<DrawPile>();

		//Tools::TextureWad.FindOrLoad(Content, "Splash");
		//Splash = new QuadClass("Splash", 1400);
		//MyPile.Add(Splash);

		MyProgressBar = boost::make_shared<ProgressBar>();
		MyProgressBar->setPos( Vector2( 900, -400 ) );

		BlackQuad = boost::make_shared<QuadClass>( std::wstring( L"White" ), 2000.f );
		BlackQuad->Quad_Renamed.SetColor( bColor( 0, 0, 0, 255 ) );
		BlackQuad->setAlpha( 0 );
		BlackQuad->Layer = 1;
		MyPile->Add( BlackQuad );

        Legal = boost::make_shared<EzText>( 
L"{pCopyRightSymbol,78,?} 2013 by Pwnee Studios, Corp. All Rights Reserved.\n"
L"Distributed by Ubisoft Entertainment under license from Pwnee Studios, Corp.\n"
L"Cloudberry Kingdom, Pwnee, and Pwnee Studios are trademarks of Pwnee Studios, Corp. and is used under license.\n"
L"Ubisoft and the Ubisoft logo are trademarks of Ubisoft Entertainment in the US and/or other countries.",
			Resources::Font_Grobold42, 10000.f, false, false, .66f );

        Legal->MyFloatColor = ColorHelper::Gray( .9f );

        BlackQuad->setAlpha( 1 );

		if ( !CloudberryKingdomGame::HideLogos )
			MyPile->Add( Legal );
	}

	void InitialLoadingScreen::PhsxStep()
	{
		LogoCount++;

		float LoadingPercent;

		LoadingPercent = 100 * ResourceCount->MyFloat / TotalResources;
		MyProgressBar->SetPercent( LoadingPercent );

		// 'Load' the fake resources
		if ( ResourceCount->MyFloat >= TotalResources - 5 )
		{
			ResourceCount->MyFloat += .5f;
			if ( Accelerate )
				ResourceCount->MyFloat = CoreMath::RestrictVal( 0.f, static_cast<float>( TotalResources ), ResourceCount->MyFloat + .033f * ( TotalResources ) );
		}

		// Fade
		//if ( LoadingPercent > 97.6f && Accelerate || !Resources::LoadingResources->MyBool )
		if ( Resources::FinalLoadDone || LogoCount > LogoCount_Max )
		{
            if ( ReadyToFade )
            {
				BlackQuad->setAlpha( BlackQuad->getAlpha() + .0223f );
				if ( BlackQuad->getAlpha() >= 1 )
					DoneCount++;
			}
		}

		if ( !Resources::LoadingResources->MyBool && ReadyToFade && BlackQuad->getAlpha() >= 1 && DoneCount > 25 )
			IsDone = true;

		//IsDone = false;
	}

	void InitialLoadingScreen::Draw()
	{
        Legal->setScale( .25f );
        Legal->setPos( Vector2(-1500, -500) );

        DrawCount++;
        if ( !ReadyToFade && DrawCount > 2 )
            BlackQuad->setAlpha( BlackQuad->getAlpha() - .0633f );
        
#ifdef PS3
		if ( DrawCount > 240 )
#elif CAFE
		if ( DrawCount > 235 )
#else
		//if ( DrawCount > 68 )
		if ( DrawCount > 90 )
#endif
            ReadyToFade = true;

		MyProgressBar->setPos( Vector2( 1100, -800 ) );

		MyPile->Draw( 0 );

		//MyProgressBar->Draw();

		MyPile->Draw( 1 );
	}

	void InitialLoadingScreen::InitializeInstanceFields()
	{
	    DrawCount = 0;
        ReadyToFade = false;

		IsDone = false;
		LogoCount = 0;
		LogoCount_Max = 60 * 5 - 50; // 5 seconds, minus 50 frames to fade out
		Accelerate = false;
		DoneCount = 0;
	}
}
