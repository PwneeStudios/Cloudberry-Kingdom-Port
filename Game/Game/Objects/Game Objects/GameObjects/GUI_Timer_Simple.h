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
	
		struct SimpleOnExpireLambda : public Lambda_1<std::shared_ptr<GUI_Timer_Base> >
		{
		
			std::shared_ptr<GUI_Timer_Simple> timer;
		
			SimpleOnExpireLambda( const std::shared_ptr<GUI_Timer_Simple> &timer );

			void Apply( const std::shared_ptr<GUI_Timer_Base> &timer );
		};

	
		GUI_Timer_Simple( int Time );
		void GUI_Timer_Simple_Construct( int Time );

		//void OnExpire(GUI_Timer_Base timer)
		//{
		//    Hide();
		//    ReleaseWhenDone = true;
		//}
	};
}


#endif	//#ifndef GUI_TIMER_SIMPLE
