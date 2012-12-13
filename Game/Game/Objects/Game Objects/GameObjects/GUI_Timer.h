#ifndef GUI_TIMER
#define GUI_TIMER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GUI_Timer : public GUI_Timer_Base
	{
	
		struct OnCoinGrabProxy : public Lambda_1<std::shared_ptr<ObjectBase> >
		{
		
			std::shared_ptr<GUI_Timer> timer;

		
			OnCoinGrabProxy( const std::shared_ptr<GUI_Timer> &timer );

			void Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	
		struct OnCompleteLevelProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			std::shared_ptr<GUI_Timer> timer;

		
			OnCompleteLevelProxy( const std::shared_ptr<GUI_Timer> &timer );

			void Apply( const std::shared_ptr<Level> &level );
		};


	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		int CoinTimeValue, MinLevelStartTimeValue;
		int MaxTime;
		void OnCoinGrab( const std::shared_ptr<ObjectBase> &obj );

		void OnCompleteLevel( const std::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		GUI_Timer();
		std::shared_ptr<GUI_Timer> GUI_Timer_Construct();
	};
}


#endif	//#ifndef GUI_TIMER
