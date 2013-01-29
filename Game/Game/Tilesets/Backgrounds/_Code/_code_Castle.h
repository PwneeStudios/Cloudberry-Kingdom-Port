#ifndef _CODE_CASTLE
#define _CODE_CASTLE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background_Castle : public BackgroundTemplate
	{
	
		virtual ~Background_Castle() { }

		Background_Castle( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

}


#endif	//#ifndef _CODE_CASTLE
