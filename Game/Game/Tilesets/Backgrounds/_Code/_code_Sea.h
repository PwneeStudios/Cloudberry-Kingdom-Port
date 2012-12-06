#ifndef _CODE_SEA
#define _CODE_SEA

#include <global_header.h>

namespace CloudberryKingdom
{
	class Background_Sea : public BackgroundTemplate
	{
	public:
		Background_Sea( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

	class Background_SeaRain : public BackgroundTemplate
	{
	public:
		Background_SeaRain( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

}


#endif	//#ifndef _CODE_SEA
