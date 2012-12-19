#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu_MW_PressStart::StartMenu_MW_PressStart( const boost::shared_ptr<TitleGameData_MW> &Title ) :
		CkBaseMenu(),
		t( 0 ), DelayToAllowInput( 0 )
	{
	}
	boost::shared_ptr<StartMenu_MW_PressStart> StartMenu_MW_PressStart::StartMenu_MW_PressStart_Construct( const boost::shared_ptr<TitleGameData_MW> &Title )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();
		
		this->Title = Title;

		return boost::static_pointer_cast<StartMenu_MW_PressStart>( shared_from_this() );
	}

	void StartMenu_MW_PressStart::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_TITLE );
		CkBaseMenu::SlideIn( 0 );
	}

	void StartMenu_MW_PressStart::SlideOut( PresetPos Preset, int Frames )
	{
		CkBaseMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW_PressStart::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	void StartMenu_MW_PressStart::Init()
	{
		 CkBaseMenu::Init();

		//DelayToAllowInput = 80;
		//DelayToAllowInput = 50;
		DelayToAllowInput = 15;

		CallDelay = ReturnToCallerDelay = 0;

		MyPile = boost::make_shared<DrawPile>();

		EnsureFancy();

		//Text = new EzText("Press any key to start", Resources.Font_Grobold42, true);
		Text = boost::make_shared<EzText>( Localization::Words_PRESS_START, Resources::Font_Grobold42, true );
		//Text = new EzText(Localization.Words.PressStart, ItemFont);

		Text->MyFloatColor = ( bColor( 226, 10, 83 ) ).ToVector4();
		Text->OutlineColor = Color::Black.ToVector4();
		MyPile->Add( Text );

		SetPos();
	}

	void StartMenu_MW_PressStart::SetPos()
	{
		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -11.11157f, -461.111f ) );
			_t->setScale( 0.66054f );
		}
		MyPile->setPos( Vector2( -91.66675f, -250 ) );
	}

	void StartMenu_MW_PressStart::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();
		if ( !Active )
			return;

		if ( DelayToAllowInput > 0 )
		{
			DelayToAllowInput--;
			return;
		}

		if ( ButtonCheck::AnyKey() )
		{
			DelayToAllowInput = 10;

			//Tools.Nothing();
			GUI_Panel::Call( MakeMagic( StartMenu_MW, ( Title ) ) );
			Hide();
		}
	}

	void StartMenu_MW_PressStart::MyDraw()
	{
		if ( !Active )
			return;

		float s = CoreMath::Periodic( .85f, 1, 3, Tools::t );
		Text->MyFloatColor = ( bColor( static_cast<int>( 226 * s ), 10, 83 ) ).ToVector4();

		Text->setScale( CoreMath::Periodic( .818668f,.838668f, 3, Tools::t ) *.8f );

		t += .01f;
		Text->Alpha = t;

		CkBaseMenu::MyDraw();
	}

	void StartMenu_MW_PressStart::OnReturnTo()
	{
		CkBaseMenu::OnReturnTo();
	}

	void StartMenu_MW_PressStart::InitializeInstanceFields()
	{
		t = 0;
	}
}
