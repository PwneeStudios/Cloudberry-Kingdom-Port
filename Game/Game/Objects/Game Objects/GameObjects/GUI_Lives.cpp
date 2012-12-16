#include <global_header.h>

namespace CloudberryKingdom
{

	const int &GUI_Lives::getLives() const
	{
		return MyGUI_Lives->getNumLives();
	}

	boost::shared_ptr<StringBuilder> GUI_Lives::BuildString()
	{
		MyString->setLength( 0 );

		MyString->Append( L'x' );
		MyString->Append( L' ' );
		MyString->Add( getLives(), 1 );

		return MyString;
	}

	void GUI_Lives::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			Hide();

			Show();
		}

		AddedOnce = true;
	}

	void GUI_Lives::Hide()
	{
		GUI_Panel::Hide();
		SlideOut( PresetPos_TOP, 0 );
	}

	void GUI_Lives::Show()
	{
		GUI_Panel::Show();
		SlideIn();
		MyPile->BubbleUp( false );
	}

	const Vector2 GUI_Lives::getApparentPos() const
	{
		return Text->FancyPos->AbsVal + Text->GetWorldSize() / 2;
	}

	void GUI_Lives::UpdateLivesText()
	{
		Text->SubstituteText( BuildString() );
	}

	GUI_Lives::GUI_Lives( const boost::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed ) :
		GUI_Panel( false ),
		AddedOnce( false )
	{
	}
	boost::shared_ptr<GUI_Lives> GUI_Lives::GUI_Lives_Construct( const boost::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct( false );

		MyGUI_Lives = GUI_Lives_Renamed;
		Constructor();

		return boost::static_pointer_cast<GUI_Lives>( shared_from_this() );
	}

	void GUI_Lives::Init()
	{
		GUI_Panel::Init();

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		Vector2 shift = Vector2( -320, 0 );
		MyPile->setPos( Vector2( 1356.112f, -848.889f ) );
		SlideInLength = 0;

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		Text = boost::make_shared<EzText>( BuildString()->ToString(), Resources::Font_Grobold42, 450.f, false, false );
		Text->setScale( .625f );
		Text->setPos( Vector2( -67.22302f, 83.26669f ) );
		Text->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		Text->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();
		MyPile->Add( Text );

		Bob_Renamed = boost::make_shared<QuadClass>( _T( "Score/Stickman" ), 64.f, true );
		Bob_Renamed->setPos( Vector2( 200.5664f, -42.03058f ) + shift );
		MyPile->Add( Bob_Renamed );
	}

	void GUI_Lives::MyDraw()
	{
		return;

		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Lives::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( MyGame->SoftPause )
			return;
		if ( Hid || !Active )
			return;

		if ( getCore()->MyLevel->Watching || getCore()->MyLevel->Finished )
			return;

		UpdateLivesText();
	}

	void GUI_Lives::InitializeInstanceFields()
	{
		MyString = boost::make_shared<StringBuilder>( 50, 50 );
		AddedOnce = false;
	}
}
