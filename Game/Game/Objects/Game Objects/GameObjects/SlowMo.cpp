#include <global_header.h>

namespace CloudberryKingdom
{

	SlowMo::SlowMo() :
		Speed( 0 ) { }
	boost::shared_ptr<SlowMo> SlowMo::SlowMo_Construct()
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();
		
		Active = true;
		PauseOnPause = true;

		Tags->Add( GameObject::Tag_REMOVE_ON_LEVEL_FINISH );

		return boost::static_pointer_cast<SlowMo>( shared_from_this() );
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

		boost::shared_ptr<Level> level = MyGame->MyLevel;

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
