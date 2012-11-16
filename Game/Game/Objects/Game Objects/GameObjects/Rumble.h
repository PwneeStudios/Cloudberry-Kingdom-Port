#ifndef RUMBLE
#define RUMBLE

#include "GUI_Panel.h"

namespace CloudberryKingdom
{
	class Rumble : public GUI_Panel
	{
	public:
		Rumble();

	protected:
		virtual void ReleaseBody();

		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef RUMBLE
