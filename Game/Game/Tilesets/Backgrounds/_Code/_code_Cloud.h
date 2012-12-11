#ifndef _CODE_CLOUD
#define _CODE_CLOUD

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background_Cloud : public BackgroundTemplate
	{
	
		Background_Cloud( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

	struct Background_CloudRain : public BackgroundTemplate
	{
	
		Background_CloudRain( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

}



#endif	//#ifndef _CODE_CLOUD
