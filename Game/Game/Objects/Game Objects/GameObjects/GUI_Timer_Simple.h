#ifndef GUI_TIMER_SIMPLE
#define GUI_TIMER_SIMPLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class GUI_Timer_Base;
}









namespace CloudberryKingdom
{
	/// <summary>
	/// A simple timer. The timer is removed on level resets, and removes itself when the timer expires.
	/// </summary>
	class GUI_Timer_Simple : public GUI_Timer_Base
	{
	private:
		class SimpleOnExpireLambda : public Lambda_1<GUI_Timer_Base*>
		{
		private:
			std::shared_ptr<GUI_Timer_Simple> timer;
		public:
			SimpleOnExpireLambda( const std::shared_ptr<GUI_Timer_Simple> &timer );

			void Apply( const std::shared_ptr<GUI_Timer_Base> &timer );
		};

	public:
		GUI_Timer_Simple( int Time );

		//void OnExpire(GUI_Timer_Base timer)
		//{
		//    Hide();
		//    ReleaseWhenDone = true;
		//}
	};
}


#endif	//#ifndef GUI_TIMER_SIMPLE
