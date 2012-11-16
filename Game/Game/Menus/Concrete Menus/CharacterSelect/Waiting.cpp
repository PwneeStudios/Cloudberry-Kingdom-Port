#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	Waiting::Waiting( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	{
		this->Tags += Tag_CHAR_SELECT;
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();
	}

	void Waiting::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	void Waiting::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		if ( MyCharacterSelect->QuickJoin )
			MyCharacterSelect->Join = true;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		CharacterSelect::Shift( this );
	}

	void Waiting::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;
		MyCharacterSelect->MyState = CharacterSelect::SelectState_WAITING;
		MyCharacterSelect->MyDoll->ShowBob = true;
		MyCharacterSelect->MyGamerTag->ShowGamerTag = true;
		MyCharacterSelect->MyHeroLevel->ShowHeroLevel = true;

		// Check for back.
		if ( ButtonCheck::State( ControllerButtons_B, MyCharacterSelect->PlayerIndex ).Pressed )
		{
			ReturnToCaller();
		}
	}
}
