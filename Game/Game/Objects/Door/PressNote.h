#ifndef PRESSNOTE
#define PRESSNOTE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct PressNote : public GUI_Text
	{
	
		static const int ButtonScale = 87;
		static const float TextScale;

	
		boost::shared_ptr<Door> Parent;

#if defined(PC_VERSION)
	
		PressNote( const boost::shared_ptr<Door> &Parent );
	#else
		PressNote( const boost::shared_ptr<Door> &Parent );
#endif

	
		int Life;

	
		int LifeSpeed; //9;
		void FadeIn();

		int DelayToFadeOut; //80;
	
		int Count;
	
		void FadeOut();

	
		virtual void MyPhsxStep();

	
		virtual void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PRESSNOTE
