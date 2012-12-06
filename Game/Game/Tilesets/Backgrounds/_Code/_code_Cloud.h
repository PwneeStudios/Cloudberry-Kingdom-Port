#ifndef _CODE_CLOUD
#define _CODE_CLOUD

#include <global_header.h>

namespace CloudberryKingdom
{
	class Background_Cloud : public BackgroundTemplate
	{
	public:
		Background_Cloud( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

	class Background_CloudRain : public BackgroundTemplate
	{
	public:
		Background_CloudRain( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

}



#endif	//#ifndef _CODE_CLOUD
