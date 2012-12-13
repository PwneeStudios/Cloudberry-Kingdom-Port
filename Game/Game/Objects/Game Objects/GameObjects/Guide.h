#ifndef GUIDE
#define GUIDE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ShowGuide : public GUI_Panel
	{
	
		ShowGuide();
		void ShowGuide_Costruct();

		virtual void ReleaseBody();

		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef GUIDE
