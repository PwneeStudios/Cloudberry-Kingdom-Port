#ifndef _CODE_HILLS
#define _CODE_HILLS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background_Hills : public BackgroundTemplate
	{
	
		Background_Hills( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

	struct Background_HillsRain : public BackgroundTemplate
	{
	
		Background_HillsRain( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

}


#endif	//#ifndef _CODE_HILLS
