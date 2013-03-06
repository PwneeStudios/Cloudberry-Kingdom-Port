#ifndef GUIDE
#define GUIDE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ShowGuide : public GUI_Panel
	{
	
		virtual ~ShowGuide()
		{
#ifdef BOOST_BIN
			OnDestructor( "ShowGuide" );
#endif
		}


		ShowGuide();
		boost::shared_ptr<ShowGuide> ShowGuide_Construct();

		virtual void ReleaseBody();

		virtual void MyPhsxStep();

	};

}


#endif	//#ifndef GUIDE
