#include "GUI_Timer_Simple.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	GUI_Timer_Simple::SimpleOnExpireLambda::SimpleOnExpireLambda( const std::shared_ptr<GUI_Timer_Simple> &timer )
	{
		this->timer = timer;
	}

	void GUI_Timer_Simple::SimpleOnExpireLambda::Apply( const std::shared_ptr<GUI_Timer_Base> &timer )
	{
		timer->Hide();
		timer->ReleaseWhenDone = true;
	}

	GUI_Timer_Simple::GUI_Timer_Simple( int Time )
	{
		PreventRelease = false;
		getCore()->RemoveOnReset = true;

		this->setTime( Time );

		OnTimeExpired->Add( std::make_shared<SimpleOnExpireLambda>( this ) );
	}
}
