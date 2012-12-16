#ifndef _CODE_CAVE
#define _CODE_CAVE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background_Cave : public BackgroundTemplate
	{
	
		Background_Cave( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );
	};

}


#endif	//#ifndef _CODE_CAVE
