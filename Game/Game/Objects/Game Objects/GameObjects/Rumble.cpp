#include <global_header.h>

namespace CloudberryKingdom
{

	Rumble::Rumble()
	{
		Active = true;
		PauseOnPause = true;
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
