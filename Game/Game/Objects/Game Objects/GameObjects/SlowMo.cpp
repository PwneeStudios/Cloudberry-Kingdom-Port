#include <global_header.h>

namespace CloudberryKingdom
{

	SlowMo::SlowMo()
	{
		InitializeInstanceFields();
		Active = true;
		PauseOnPause = true;

		Tags += GameObject::Tag_REMOVE_ON_LEVEL_FINISH;
	}

	void SlowMo::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();

		Tools::setPhsxSpeed( 1 );
	}

	void SlowMo::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( !Active )
			return;

		std::shared_ptr<Level> level = MyGame->MyLevel;

		// Don't affect speed if a replay is being watched
		if ( level->Replay || level->Watching )
			return;

		Tools::setPhsxSpeed( Speed );

		// On (B)
		if ( ButtonCheck::State( ControllerButtons_X, getControl() ).Pressed )
		{
			// Change the speed
			if ( Speed == 1 )
				Speed = 0;
			else
				Speed = 1;
		}
	}

	void SlowMo::InitializeInstanceFields()
	{
		Speed = 0;
	}
}
