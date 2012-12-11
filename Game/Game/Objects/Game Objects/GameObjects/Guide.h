#ifndef GUIDE
#define GUIDE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ShowGuide : public GUI_Panel
	{
	
		ShowGuide();

	
		virtual void ReleaseBody();

		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef GUIDE
