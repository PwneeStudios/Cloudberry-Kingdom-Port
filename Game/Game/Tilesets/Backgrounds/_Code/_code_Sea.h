#ifndef _CODE_SEA
#define _CODE_SEA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background_Sea : public BackgroundTemplate
	{
	
		Background_Sea( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

	struct Background_SeaRain : public BackgroundTemplate
	{
	
		Background_SeaRain( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

}


#endif	//#ifndef _CODE_SEA
