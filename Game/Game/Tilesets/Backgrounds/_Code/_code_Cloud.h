#ifndef _CODE_CLOUD
#define _CODE_CLOUD

#include "../Game/Tilesets/Backgrounds/Background.h"
#include <string>

namespace CloudberryKingdom
{
	class Background;
}


using namespace Microsoft::Xna::Framework;

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
