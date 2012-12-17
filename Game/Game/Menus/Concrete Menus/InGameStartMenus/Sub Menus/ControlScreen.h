#ifndef CONTROLSCREEN
#define CONTROLSCREEN

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ControlScreen : public CkBaseMenu
	{
	
		boost::shared_ptr<QuadClass> BackgroundQuad;

	
		ControlScreen( int Control );
		boost::shared_ptr<ControlScreen> ControlScreen_Construct( int Control );

#if defined(PC_VERSION)
	
		boost::shared_ptr<QuadClass> MakeQuad( Keys key );
#endif
	
		virtual void Init();

#if defined(PC_VERSION)
	
		void SetPos();
#endif

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef CONTROLSCREEN
