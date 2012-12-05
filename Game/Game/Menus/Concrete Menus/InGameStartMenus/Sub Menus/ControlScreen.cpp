#include <global_header.h>

namespace CloudberryKingdom
{

	ControlScreen::ControlScreen( int Control ) : CkBaseMenu( false )
	{
		this->setControl( Control );

		Constructor();
	}

#if defined(PC_VERSION)
	std::shared_ptr<QuadClass> ControlScreen::MakeQuad( Keys key )
	{
		std::shared_ptr<QuadClass> quad = std::make_shared<QuadClass>( ButtonString::KeyToTexture( key ), 90.f );
		MyPile->Add( quad );
		quad->Quad_Renamed.SetColor( CustomControlsMenu::SecondaryKeyColor );
		return quad;
	}
#endif

	void ControlScreen::Init()
	{
		 CkBaseMenu::Init();

		setPauseGame( true );

		SlideInFrom = SlideOutTo = PresetPos_LEFT;

		//ReturnToCallerDelay = SlideLength = 0;
		setSlideLength( 29 );
		DestinationScale *= 1.02f;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		std::shared_ptr<QuadClass> Backdrop = std::make_shared<QuadClass>( _T( "Backplate_1230x740" ), 1500.f, true );
		Backdrop->Name = _T( "Backdrop" );
		MyPile->Add( Backdrop );

		ReturnToCallerDelay = 10;

		std::shared_ptr<EzText> text;

	#if defined(PC_VERSION)
		text = std::make_shared<EzText>( Localization::Words_QUICK_SPAWN, Resources::Font_Grobold42 );
		MyPile->Add( text, _T( "quickspawn" ) );
		text->MyFloatColor = ColorHelper::Gray( .955f );

		text = std::make_shared<EzText>( Localization::Words_POWER_UP_MENU, Resources::Font_Grobold42 );
		MyPile->Add( text, _T( "powerups" ) );
		text->MyFloatColor = ColorHelper::Gray( .955f );

		text = std::make_shared<EzText>( Localization::Words_MENU, Resources::Font_Grobold42 );
		MyPile->Add( text, _T( "menu" ) );
		text->MyFloatColor = CampaignHelper::DifficultyColor[ 1 ].ToVector4();

		text = std::make_shared<EzText>( Localization::Words_ACCEPT, Resources::Font_Grobold42 );
		MyPile->Add( text, _T( "accept" ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;

		text = std::make_shared<EzText>( Localization::Words_BACK, Resources::Font_Grobold42 );
		MyPile->Add( text, _T( "back" ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;

		text = std::make_shared<EzText>( _T( "b" ), Resources::Font_Grobold42 );
		text->SubstituteText( _T( "<" ) );
		MyPile->Add( text, _T( "split" ) );

		std::shared_ptr<QuadClass> q;

		q = std::make_shared<QuadClass>( _T( "Enter_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, _T( "enter" ) );

		q = std::make_shared<QuadClass>( _T( "Esc_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, _T( "esc" ) );

		q = std::make_shared<QuadClass>( _T( "Backspace_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, _T( "backspace" ) );

		q = std::make_shared<QuadClass>( _T( "Space_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, _T( "space" ) );

		SetPos();
	#endif
	}

#if defined(PC_VERSION)
	void ControlScreen::SetPos()
	{
		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "quickspawn" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -288.0965f, 435.3178f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( _T( "powerups" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -267.0644f, 133.7302f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( _T( "menu" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -280.1582f, 731.7462f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( _T( "accept" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -286.109f, -156.3493f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( _T( "back" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -264.2847f, -432.5391f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( _T( "split" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -536.5085f, 14.28584f ) );
			_t->setScale( 1.46f );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1500, 902.2556f ) );
		}
		_q = MyPile->FindQuad( _T( "enter" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -771.4287f, -234.9209f ) );
			_q->setSize( Vector2( 271.0638f, 130 ) );
		}
		_q = MyPile->FindQuad( _T( "esc" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -638.8887f, 520.2384f ) );
			_q->setSize( Vector2( 138.2979f, 130 ) );
		}
		_q = MyPile->FindQuad( _T( "backspace" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -773.8103f, -603.5712f ) );
			_q->setSize( Vector2( 271.0638f, 130 ) );
		}
		_q = MyPile->FindQuad( _T( "space" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -768.6523f, 205.9521f ) );
			_q->setSize( Vector2( 271.0638f, 130 ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}
#endif

	void ControlScreen::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;

		if ( ButtonCheck::State( ControllerButtons_A, -1 ).Pressed || ButtonCheck::State( ControllerButtons_B, -1 ).Pressed )
		{
			Active = false;
			ReturnToCaller();
		}
	}
}
