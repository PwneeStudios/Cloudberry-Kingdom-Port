#ifndef GUI_TIMER_SIMPLE
#define GUI_TIMER_SIMPLE

#include <global_header.h>

namespace CloudberryKingdom
{

	/// <summary>
	/// A simple timer. The timer is removed on level resets, and removes itself when the timer expires.
	/// </summary>
	struct GUI_Timer_Simple : public GUI_Timer_Base
	{
	
		struct SimpleOnExpireLambda : public Lambda_1<boost::shared_ptr<GUI_Timer_Base> >
		{
		
			boost::shared_ptr<GUI_Timer_Simple> timer;
		
			SimpleOnExpireLambda( const boost::shared_ptr<GUI_Timer_Simple> &timer );

			void Apply( const boost::shared_ptr<GUI_Timer_Base> &timer );
		};

	
		GUI_Timer_Simple( int Time );
		boost::shared_ptr<GUI_Timer_Simple> GUI_Timer_Simple_Construct( int Time );

		//void OnExpire(GUI_Timer_Base timer)
		//{
		//    Hide();
		//    ReleaseWhenDone = true;
		//}
	};
}


#endif	//#ifndef GUI_TIMER_SIMPLE
