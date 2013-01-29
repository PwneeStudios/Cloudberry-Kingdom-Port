#ifndef _CODE_HILLS
#define _CODE_HILLS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background_Hills : public BackgroundTemplate
	{
	
		virtual ~Background_Hills() { }

		Background_Hills( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

	struct Background_HillsRain : public BackgroundTemplate
	{
	
		virtual ~Background_HillsRain() { }

		Background_HillsRain( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

}


#endif	//#ifndef _CODE_HILLS
