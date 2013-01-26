#ifndef SLOWMO
#define SLOWMO

#include <global_header.h>

namespace CloudberryKingdom
{

	struct SlowMo : public GUI_Panel
	{

	
		virtual ~SlowMo() { }
		
		SlowMo();
		boost::shared_ptr<SlowMo> SlowMo_Construct();
	
		virtual void ReleaseBody();

	
		int Speed;

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();

	};

}

#endif	//#ifndef SLOWMO
