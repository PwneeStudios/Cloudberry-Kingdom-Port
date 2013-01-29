#ifndef _CODE_SEA
#define _CODE_SEA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background_Sea : public BackgroundTemplate
	{
	
		virtual ~Background_Sea() { }

		Background_Sea( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

	struct Background_SeaRain : public BackgroundTemplate
	{
	
		virtual ~Background_SeaRain() { }

		Background_SeaRain( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

}


#endif	//#ifndef _CODE_SEA
