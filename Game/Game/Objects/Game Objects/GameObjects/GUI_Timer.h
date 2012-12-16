#ifndef GUI_TIMER
#define GUI_TIMER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GUI_Timer : public GUI_Timer_Base
	{
	
		struct OnCoinGrabProxy : public Lambda_1<boost::shared_ptr<ObjectBase> >
		{
		
			boost::shared_ptr<GUI_Timer> timer;

		
			OnCoinGrabProxy( const boost::shared_ptr<GUI_Timer> &timer );

			void Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		struct OnCompleteLevelProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<GUI_Timer> timer;

		
			OnCompleteLevelProxy( const boost::shared_ptr<GUI_Timer> &timer );

			void Apply( const boost::shared_ptr<Level> &level );
		};


	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		int CoinTimeValue, MinLevelStartTimeValue;
		int MaxTime;
		void OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj );

		void OnCompleteLevel( const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		GUI_Timer();
		boost::shared_ptr<GUI_Timer> GUI_Timer_Construct();
	};
}


#endif	//#ifndef GUI_TIMER
