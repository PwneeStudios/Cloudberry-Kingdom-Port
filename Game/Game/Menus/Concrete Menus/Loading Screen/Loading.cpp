#include <global_header.h>

using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Audio;
using namespace Microsoft::Xna::Framework::Content;

namespace CloudberryKingdom
{

	std::vector<std::wstring> ProgressBar::GetViewables()
	{
		return std::vector<std::wstring*> ();
	}

	const Microsoft::Xna::Framework::Vector2 &ProgressBar::getFull_BL() const
	{
		return Outline->getBL();
	}

	const Microsoft::Xna::Framework::Vector2 &ProgressBar::getFull_TR() const
	{
		return Outline->getTR();
	}

	const Microsoft::Xna::Framework::Vector2 &ProgressBar::getCurrent_TR() const
	{
		return Vector2( getFull_BL().X + (getFull_TR().X - getFull_BL().X) * PercentDone / 100, getFull_TR().Y );
	}

	const Microsoft::Xna::Framework::Vector2 &ProgressBar::getPos() const
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
		MyPile = std::make_shared<DrawPile>();

		Outline = std::make_shared<QuadClass>();
		Outline->SetToDefault();
		MyPile->Add( Outline );

		Fill = std::make_shared<QuadClass>();
		Fill->SetToDefault();
		MyPile->Add( Fill );
	}

	void ProgressBar::InitStandardBar()
	{
		Outline->setTextureName( _T( "LoadOutline" ) );
		Outline->ScaleYToMatchRatio( 192 );

		Fill->setTextureName( _T( "LoadFill" ) );
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
				Fill->Quad_Renamed->v1->Vertex->uv->X = PercentDone / 100;
				Fill->Quad_Renamed->v3->Vertex->uv->X = PercentDone / 100;

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
		MyType = BarType_SCALE;
	}

	InitialLoadingScreen::InitialLoadingScreen( const std::shared_ptr<ContentManager> &Content, const std::shared_ptr<WrappedFloat> &ResourceCount )
	{
		InitializeInstanceFields();
		this->ResourceCount = ResourceCount;

		Whinney = Content->Load<SoundEffect*>( _T( "Whinney" ) );

		Tools::TextureWad->FindOrLoad( Content, _T( "Art\\LoadScreen_Initial\\LoadOutline" ) );
		Tools::TextureWad->FindOrLoad( Content, _T( "Art\\LoadScreen_Initial\\LoadFill" ) );

		MyPile = std::make_shared<DrawPile>();

		//Tools.TextureWad.FindOrLoad(Content, "Splash");
		//Splash = new QuadClass("Splash", 1400);
		//MyPile.Add(Splash);

		MyProgressBar = std::make_shared<ProgressBar>();
		MyProgressBar->setPos( Vector2( 900, -400 ) );

		BlackQuad = std::make_shared<QuadClass>( _T( "White" ), 1400 );
		BlackQuad->Quad_Renamed->SetColor( Color( 0, 0, 0, 255 ) );
		BlackQuad->setAlpha( 0 );
		BlackQuad->Layer = 1;
		MyPile->Add( BlackQuad );
	}

int InitialLoadingScreen::TotalResources = 805;

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
				ResourceCount->MyFloat = CoreMath::Restrict( 0, TotalResources, ResourceCount->MyFloat + .033f * ( TotalResources ) );
		}

		// Fade
		if ( LoadingPercent > 97.6f && Accelerate || !Resources::LoadingResources->MyBool )
		{
			BlackQuad->setAlpha( BlackQuad->getAlpha() + .0223f );
			if ( BlackQuad->getAlpha() >= 1 )
				DoneCount++;
		}

		if ( NoShow )
		{
			if ( !Resources::LoadingResources->MyBool )
				IsDone = true;
		}
		else
		{
			if ( !Resources::LoadingResources->MyBool && DoneCount > 1 )
				//if (!Resources.LoadingResources.MyBool)
				IsDone = true;
		}
	}

	void InitialLoadingScreen::Draw()
	{
		if ( NoShow )
			return;

		MyProgressBar->setPos( Vector2( 1100, -800 ) );

		MyPile->Draw( 0 );

		MyProgressBar->Draw();

		MyPile->Draw( 1 );
	}

	void InitialLoadingScreen::InitializeInstanceFields()
	{
		IsDone = false;
		LogoCount = 0;
		Accelerate = false;
		DoneCount = 0;
	}
}
