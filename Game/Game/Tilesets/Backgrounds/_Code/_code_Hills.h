#ifndef _CODE_HILLS
#define _CODE_HILLS

#include <global_header.h>

namespace CloudberryKingdom
{
	class Background;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Background_Hills : public BackgroundTemplate
	{
	public:
		Background_Hills( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

	class Background_HillsRain : public BackgroundTemplate
	{
	public:
		Background_HillsRain( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

}


#endif	//#ifndef _CODE_HILLS
