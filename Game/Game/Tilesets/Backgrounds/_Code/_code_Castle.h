#ifndef _CODE_CASTLE
#define _CODE_CASTLE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background_Castle : public BackgroundTemplate
	{
	
		Background_Castle( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

}


#endif	//#ifndef _CODE_CASTLE
