#include <global_header.h>

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

	GUI_Timer_Simple::GUI_Timer_Simple( int Time ) { }
	std::shared_ptr<GUI_Timer_Simple> GUI_Timer_Simple::GUI_Timer_Simple_Construct( int Time )
	{
		GUI_Timer_Base::GUI_Timer_Base_Construct();

		PreventRelease = false;
		getCore()->RemoveOnReset = true;

		this->setTime( Time );

		OnTimeExpired->Add( std::make_shared<SimpleOnExpireLambda>( std::static_pointer_cast<GUI_Timer_Simple>( shared_from_this() ) ) );
	}
}
