#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Simple.h"

#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Base.h"


namespace CloudberryKingdom
{

	GUI_Timer_Simple::SimpleOnExpireLambda::SimpleOnExpireLambda( const boost::shared_ptr<GUI_Timer_Simple> &timer )
	{
		this->timer = timer;
	}

	void GUI_Timer_Simple::SimpleOnExpireLambda::Apply( const boost::shared_ptr<GUI_Timer_Base> &timer )
	{
		timer->Hide();
		timer->ReleaseWhenDone = true;
	}

	GUI_Timer_Simple::GUI_Timer_Simple( int Time ) { }
	boost::shared_ptr<GUI_Timer_Simple> GUI_Timer_Simple::GUI_Timer_Simple_Construct( int Time )
	{
		GUI_Timer_Base::GUI_Timer_Base_Construct();

		PreventRelease = false;
		getCore()->RemoveOnReset = true;

		this->setTime( Time );

		OnTimeExpired->Add( boost::make_shared<SimpleOnExpireLambda>( boost::static_pointer_cast<GUI_Timer_Simple>( shared_from_this() ) ) );

		return boost::static_pointer_cast<GUI_Timer_Simple>( shared_from_this() );
	}
}
