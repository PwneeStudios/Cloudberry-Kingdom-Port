#include <global_header.h>

namespace CloudberryKingdom
{

	const float PressNote::TextScale = .555f / .7f *.8f;

	PressNote::PressNote( const boost::shared_ptr<Door> &Parent )
	{
	}

	boost::shared_ptr<PressNote> PressNote::PressNote_Construct( const boost::shared_ptr<Door> &Parent )
	{
#if defined(PC_VERSION)
		GUI_Text_Construct( std::wstring( L"Press " ) + ButtonString::Up( ButtonScale ), Parent->getPos(), true );
#else
		GUI_Text_Construct( std::wstring( L"Press " ) + ButtonString::X( ButtonScale ), Parent->getPos(), true );
#endif

		Life = 0;
		LifeSpeed = 0;
		DelayToFadeOut = 0;
		Count = 0;

		MyText->Shadow = true;
		MyText->ShadowOffset = Vector2(15);
		MyText->ShadowColor = ColorHelper::GrayColor(.5f);
		MyText->ShadowColor.A = 30;

		this->Parent = Parent;
		Oscillate_Renamed = true;
		OscillationSpeed = .0125f;

		MyText->setScale( TextScale );
		MyText->ZoomWithCam = true;

		getCore()->DrawLayer = Level::LastInLevelDrawLayer;
		getCore()->RemoveOnReset = true;

		getCore()->ParentObject = Parent;

		boost::shared_ptr<QuadClass> backdrop;
		backdrop = boost::make_shared<QuadClass>( std::wstring( L"WidePlaque" ), 300.f, true );
		MyPile->Add( backdrop );

		Pos->RelVal = Parent->getPos();

		Active = true;

		// Set Position
		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( L"" ); if (_t != 0 ) { _t->setPos( Vector2( 0.f, 0.f ) ); _t->setScale( 0.6342857f ); }

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2(-25.f, -47.22223f ) ); _q->setSize( Vector2( 388.2494f, 146.3333f ) ); }

		MyPile->setPos( Vector2( 33.f, 340.f ) );

		return boost::static_pointer_cast<PressNote>( shared_from_this() );
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

		if ( Parent == 0 || Parent->getOnOpen() == 0 )
		{
			Life = __min( Life, 90 );
			FadeOut();
			//Kill();
			//Active = false;
		}
		else
		{
			// Fade out if we haven't been activated in a while.
			if ( Count > DelayToFadeOut || Count > 1 && Life < 255 )
				FadeOut();
			else
				Count++;
		}
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
