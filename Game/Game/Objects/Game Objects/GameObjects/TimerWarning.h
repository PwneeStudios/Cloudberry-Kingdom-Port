#ifndef TIMERWARNING
#define TIMERWARNING

#define _USE_MATH_DEFINES
#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Tools/CoreMath.h"
#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct TimerWarning : public GameObject
	{

		virtual ~TimerWarning()
		{
#ifdef BOOST_BIN
			OnDestructor( "TimerWarning" );
#endif
		}


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
