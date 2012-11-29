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

	GUI_Timer_Simple::GUI_Timer_Simple( int Time )
	{
		PreventRelease = false;
		getCore()->RemoveOnReset = true;

		this->setTime( Time );

		OnTimeExpired->Add( std::make_shared<SimpleOnExpireLambda>( shared_from_this() ) );
	}
}
