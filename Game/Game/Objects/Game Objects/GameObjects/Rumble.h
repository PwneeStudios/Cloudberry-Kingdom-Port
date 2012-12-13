#ifndef RUMBLE
#define RUMBLE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Rumble : public GUI_Panel
	{
	
		Rumble();
		void Rumble_Construct();

	
		virtual void ReleaseBody();

		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef RUMBLE
