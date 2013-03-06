#ifndef CONTROLSCREEN
#define CONTROLSCREEN

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ControlScreen : public CkBaseMenu
	{
	
		virtual ~ControlScreen()
		{
#ifdef BOOST_BIN
			OnDestructor( "ControlScreen" );
#endif
		}


		boost::shared_ptr<QuadClass> BackgroundQuad;

	
		ControlScreen( int Control );
		boost::shared_ptr<ControlScreen> ControlScreen_Construct( int Control );

#if defined(PC_VERSION)
		boost::shared_ptr<QuadClass> MakeQuad( Keys key );
#endif
	
		virtual void Init();

		void SetPos();
	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef CONTROLSCREEN
