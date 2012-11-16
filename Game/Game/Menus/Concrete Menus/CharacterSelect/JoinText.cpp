#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))
using namespace Microsoft::Xna::Framework::GamerServices;
#endif

namespace CloudberryKingdom
{

	JoinText::JoinText( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	{
		this->Tags += Tag_CHAR_SELECT;
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();
	}

	void JoinText::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	void JoinText::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		// Press A to join
		Tools::Warning();
	#if defined(PC_VERSION)
		Text = std::make_shared<EzText>( _T( "Press\n" ) + ButtonString::Go_Controller( 89 ) + _T( "\nto join!" ), Resources::Font_Grobold42, 1000, true, true,.65f );
	#else
		Text = std::make_shared<EzText>( _T( "Press\n{pXbox_A,72,?}\nto join!" ), Resources::Font_Grobold42, true, true );
	#endif
		Text->setScale( .7765f );

		Text->ShadowOffset = Vector2( 7.5f, 7.5f );
		Text->ShadowColor = Color( 30, 30, 30 );
		Text->ColorizePics = true;

		MyPile->Add( Text );

		CharacterSelect::Shift( this );
	}

	void JoinText::ScaleGamerTag( const std::shared_ptr<EzText> &GamerTag_Renamed )
	{
		GamerTag_Renamed->setScale( GamerTag_Renamed->getScale() * 850 / GamerTag_Renamed->GetWorldWidth() );

		float Height = GamerTag_Renamed->GetWorldHeight();
		float MaxHeight = 380;
		if ( Height > MaxHeight )
			GamerTag_Renamed->setScale( GamerTag_Renamed->getScale() * MaxHeight / Height );
	}

	void JoinText::SetGamerTag()
	{
		Tools::StartGUIDraw();
		if ( MyCharacterSelect->getPlayer()->Exists )
		{
			std::wstring name = MyCharacterSelect->getPlayer()->GetName();
			Text = std::make_shared<EzText>( name, Resources::Font_Grobold42, true, true );
			ScaleGamerTag( Text );
		}
		else
		{
			Text = std::make_shared<EzText>( _T( "ERROR" ), Resources::LilFont, true, true );
		}

		Text->Shadow = false;
		Text->PicShadow = false;

		Tools::EndGUIDraw();
	}

	void JoinText::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;
		MyCharacterSelect->MyState = CharacterSelect::SelectState_BEGINNING;
		MyCharacterSelect->MyDoll->ShowBob = false;
		MyCharacterSelect->MyGamerTag->ShowGamerTag = false;
		MyCharacterSelect->getPlayer()->Exists = false;

		// Use this if statement if you want keyboard to control all characters (For debugging)
		//if (ButtonCheck.State(ControllerButtons.A, -2).Pressed)

		if ( ButtonCheck::State( ControllerButtons_A, getControl() ).Pressed )
		{
	#if defined(XBOX) || defined(XBOX_SIGNIN)
			if ( MyCharacterSelect->getPlayer()->getMyGamer() != 0 )
				Call( std::make_shared<SimpleMenu>( getControl(), MyCharacterSelect ) );
			else
				Call( std::make_shared<SignInMenu>( getControl(), MyCharacterSelect ) );
	#else
			Call( std::make_shared<SimpleMenu>( getControl(), MyCharacterSelect ) );
	#endif
			Hide();
		}
	}
}
