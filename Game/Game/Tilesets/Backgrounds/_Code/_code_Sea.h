#ifndef _CODE_SEA
#define _CODE_SEA

#include "../Game/Tilesets/Backgrounds/Background.h"
#include <string>

namespace CloudberryKingdom
{
	class Background;
}


using namespace Microsoft::Xna::Framework;

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
