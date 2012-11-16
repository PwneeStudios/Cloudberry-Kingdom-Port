#ifndef TIMERWARNING
#define TIMERWARNING

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class GUI_Timer;
}

namespace CloudberryKingdom
{
	class QuadClass;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class TimerWarning : public GameObject
	{
	public:
		std::shared_ptr<GUI_Timer> MyTimer;
	private:
		std::shared_ptr<QuadClass> Fullscreen;

	public:
		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

	public:
		TimerWarning();

	private:
		float t;
	protected:
		virtual void MyDraw();

		//int Threshhold = 62 * 3;
	private:
		int Threshhold;
		int SubThreshholdCount;
	protected:
		virtual void MyPhsxStep();

	private:
		void SetAlpha( float alpha );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TIMERWARNING
