#include <global_header.h>

namespace CloudberryKingdom
{

const float PressNote::TextScale = .555f / .7f *.8f;

#if defined(PC_VERSION)
	PressNote::PressNote( const std::shared_ptr<Door> &Parent ) :
		GUI_Text( _T( "Press " ) + ButtonString::Up( ButtonScale ), Parent->getPos(), true ),
		Life( 0 ),
		LifeSpeed( 0 ),
		DelayToFadeOut( 0 ),
		Count( 0 )

#endif
#if ! defined(PC_VERSION)
	PressNote::PressNote( const std::shared_ptr<Door> &Parent ) :
		GUI_Text( _T( "Press " ) + ButtonString::X( ButtonScale ), Parent->getPos(), true )
		Life( 0 ),
		LifeSpeed( 0 ),
		DelayToFadeOut( 0 ),
		Count( 0 )
	#endif
	{
		this->Parent = Parent;
		Oscillate_Renamed = true;
		OscillationSpeed = .0125f;

		MyText->setScale( TextScale );
		MyText->ZoomWithCam = true;

		getCore()->DrawLayer = Level::LastInLevelDrawLayer;
		getCore()->RemoveOnReset = true;

		getCore()->ParentObject = Parent;

		std::shared_ptr<QuadClass> backdrop;
		backdrop = std::make_shared<QuadClass>( _T( "Cloud1" ), 300.f, true );
		MyPile->Add( backdrop );
		backdrop->setPos( Vector2( -189.0432f, -27.00623f ) );
		backdrop->setSize( Vector2( 303.8582f, 157.471f ) );
		backdrop = std::make_shared<QuadClass>( _T( "Cloud1" ), 300.f, true );
		MyPile->Add( backdrop );
		backdrop->setPos( Vector2( 106.59253f, -69.44446f ) );
		backdrop->setSize( Vector2( 288.4258f, 149.755f ) );

		Pos->RelVal = Parent->getPos();

		MyPile->FancyPos->RelVal = Vector2( 33, 340 );

		Active = true;
	}

	void PressNote::FadeIn()
	{
		Count = 0;
		Life = __min( 255, Life + LifeSpeed );
	}

	void PressNote::FadeOut()
	{
		Life = __max( -50, Life - LifeSpeed );

		if ( Life < 0 )
		{
			Kill();
			Active = false;
			Parent->ClearNote();
		}
	}

	void PressNote::MyPhsxStep()
	{
		GUI_Text::MyPhsxStep();

		if ( !Active )
			return;

		// Fade out if we haven't been activated in a while.
		if ( Count > DelayToFadeOut || Count > 1 && Life < 255 )
			FadeOut();
		else
			Count++;
	}

	void PressNote::Draw()
	{
		GUI_Text::Draw();
	}

	void PressNote::InitializeInstanceFields()
	{
		Life = 255;
		LifeSpeed = 11;
		DelayToFadeOut = 60;
		Count = 0;
	}
}
