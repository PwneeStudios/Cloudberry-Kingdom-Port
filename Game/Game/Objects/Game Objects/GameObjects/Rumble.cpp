#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/Rumble.h"

#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Tools/Tools.h"

#include "Game/Tools/Camera.h"

namespace CloudberryKingdom
{

	Rumble::Rumble() { }
	boost::shared_ptr<Rumble> Rumble::Rumble_Construct()
	{
		GUI_Panel::GUI_Panel_Construct();

		Active = true;
		PauseOnPause = true;

		return boost::static_pointer_cast<Rumble>( shared_from_this() );
	}

	void Rumble::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();
	}

	void Rumble::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( !Active )
			return;

		int Period = 105; // 96;
		if ( getCore()->GetPhsxStep() % Period == 0 && getCore()->GetPhsxStep() > 60 )
			Tools::getCurCamera()->StartShake(.5f, 36);
	}
}
