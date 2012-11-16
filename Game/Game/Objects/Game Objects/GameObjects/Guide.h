#ifndef GUIDE
#define GUIDE

#include <global_header.h>

namespace CloudberryKingdom
{
	class ShowGuide : public GUI_Panel
	{
	public:
		ShowGuide();

	protected:
		virtual void ReleaseBody();

		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef GUIDE
