#include <small_header.h>
#include "Game/Objects/Door/PressNote.h"

#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Core/Input/ButtonCheck.h"
#include "Core/Text/EzText.h"
#include "Core/Tools/ColorHelper.h"
#include "Game/Objects/Door/Door.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"


namespace CloudberryKingdom
{

	const float PressNote::TextScale = .555f / .7f *.8f;

	PressNote::PressNote( const boost::shared_ptr<Door> &Parent )
	{
	}

	boost::shared_ptr<PressNote> PressNote::PressNote_Construct( const boost::shared_ptr<Door> &Parent )
	{
#if defined(PC_VERSION)
		GUI_Text_Construct( Format( Localization::WordString( Localization::Words_Press ).c_str(), ButtonString::Up( ButtonScale ).c_str() ), Parent->getPos(), true );
#elif defined(CAFE)
		if ( ButtonTexture::UseGamepad )
			GUI_Text_Construct( Format( Localization::WordString( Localization::Words_Press_WiiU ).c_str(), ButtonString::X(    ButtonScale ).c_str() ), Parent->getPos(), true );
		else
			GUI_Text_Construct( Format( Localization::WordString( Localization::Words_Press_WiiU ).c_str(), ButtonString::Back( ButtonScale ).c_str() ), Parent->getPos(), true );
#elif defined(PS3)
		GUI_Text_Construct( Format( Localization::WordString( Localization::Words_Press_PS3 ).c_str(), ButtonString::X( ButtonScale ).c_str() ), Parent->getPos(), true );
#else
		GUI_Text_Construct( Format( Localization::WordString( Localization::Words_Press ).c_str(), ButtonString::X( ButtonScale ).c_str() ), Parent->getPos(), true );
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

		// Set Position SetPos()
			boost::shared_ptr<EzText> _t;
			if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_KOREAN )
			{
				_t = MyPile->FindEzText( L"" ); if (_t != 0 ) { _t->setPos( Vector2( 0.f, 0.f ) ); _t->setScale( 0.6342857f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2(-60.f, -47.22223f ) ); _q->setSize( Vector2( 388.2494f, 146.3333f ) ); }

				MyPile->setPos( Vector2( 33.f, 340.f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_CHINESE )
			{
				_t = MyPile->FindEzText( L"" ); if (_t != 0 ) { _t->setPos( Vector2(-13.88867f, 2.777771f ) ); _t->setScale( 0.6342857f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2(-25.f, -47.22223f ) ); _q->setSize( Vector2( 388.2494f, 146.3333f ) ); }

				MyPile->setPos( Vector2( 33.f, 340.f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
			{
				_t = MyPile->FindEzText( L"" ); if (_t != 0 ) { _t->setPos( Vector2(-5.554688f, 0.f ) ); _t->setScale( 0.575303f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2(-25.f, -47.22223f ) ); _q->setSize( Vector2( 388.2494f, 146.3333f ) ); }

				MyPile->setPos( Vector2( 33.f, 340.f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
			{
				_t = MyPile->FindEzText( L"" ); if (_t != 0 ) { _t->setPos( Vector2(-16.66699f, -2.777771f ) ); _t->setScale( 0.4835555f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2(-25.f, -47.22223f ) ); _q->setSize( Vector2( 388.2494f, 146.3333f ) ); }

				MyPile->setPos( Vector2( 33.f, 340.f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_JAPANESE )
			{
				_t = MyPile->FindEzText( L"" ); if (_t != 0 ) { _t->setPos( Vector2( 36.11133f, -2.777832f ) ); _t->setScale( 0.5663899f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2(-25.f, -47.22223f ) ); _q->setSize( Vector2( 388.2494f, 146.3333f ) ); }

				MyPile->setPos( Vector2( 33.f, 340.f ) );
			}
			else
			{
				_t = MyPile->FindEzText( L"" ); if (_t != 0 ) { _t->setPos( Vector2( 0.f, 0.f ) ); _t->setScale( 0.6342857f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2(-25.f, -47.22223f ) ); _q->setSize( Vector2( 388.2494f, 146.3333f ) ); }

				MyPile->setPos( Vector2( 33.f, 340.f ) );
			}
			
			
			float w = _t->GetWorldWidth();
			if ( w > 810.0f )
			{
				_t->setScale( _t->getScale() * 810.0f / w );
			}

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
