#ifndef SLOWMO
#define SLOWMO

#include <global_header.h>

namespace CloudberryKingdom
{

	struct SlowMo : public GUI_Panel
	{

	
		SlowMo();

	
		virtual void ReleaseBody();

	
		int Speed;

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();

	};

}

#endif	//#ifndef SLOWMO
