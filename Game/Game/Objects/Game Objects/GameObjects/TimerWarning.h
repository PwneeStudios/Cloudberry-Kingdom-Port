#ifndef TIMERWARNING
#define TIMERWARNING

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	struct TimerWarning : public GameObject
	{
	
		boost::shared_ptr<GUI_Timer> MyTimer;
	
		boost::shared_ptr<QuadClass> Fullscreen;

	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		TimerWarning();

	
		float t;
	
		virtual void MyDraw();

		//int Threshhold = 62 * 3;
	
		int Threshhold;
		int SubThreshholdCount;
	
		virtual void MyPhsxStep();

	
		void SetAlpha( float alpha );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TIMERWARNING
