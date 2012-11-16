#include "GUI_Lives.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_LivesLeft.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Text/EzText.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Tools/Resources.h"
#include "Properties/Resources.Designer.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	const int &GUI_Lives::getLives() const
	{
		return MyGUI_Lives->getNumLives();
	}

	std::shared_ptr<StringBuilder> GUI_Lives::BuildString()
	{
		MyString->Length = 0;

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

	const Microsoft::Xna::Framework::Vector2 &GUI_Lives::getApparentPos() const
	{
		return Text->FancyPos->AbsVal + Text->GetWorldSize() / 2;
	}

	void GUI_Lives::UpdateLivesText()
	{
		Text->SubstituteText( BuildString() );
	}

	GUI_Lives::GUI_Lives( const std::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed ) : GUI_Panel( false )
	{
		InitializeInstanceFields();
		MyGUI_Lives = GUI_Lives_Renamed;
		Constructor();
	}

	void GUI_Lives::Init()
	{
		GUI_Panel::Init();

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		Vector2 shift = Vector2( -320, 0 );
		MyPile->setPos( Vector2( 1356.112f, -848.889f ) );
		SlideInLength = 0;

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		Text = std::make_shared<EzText>( BuildString()->ToString(), Resources::Font_Grobold42, 450, false, false );
		Text->setScale( .625f );
		Text->setPos( Vector2( -67.22302f, 83.26669f ) );
		Text->MyFloatColor = ( Color( 255, 255, 255 ) ).ToVector4();
		Text->OutlineColor = ( Color( 0, 0, 0 ) ).ToVector4();
		MyPile->Add( Text );

		Bob_Renamed = std::make_shared<QuadClass>( _T( "Score\\Stickman" ), 64, true );
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
		MyString = std::make_shared<StringBuilder>( 50, 50 );
		AddedOnce = false;
	}
}
