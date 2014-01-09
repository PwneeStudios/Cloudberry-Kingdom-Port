#include <small_header.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Cloud.h"

namespace CloudberryKingdom
{

	Background_Cloud::Background_Cloud( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Cloud::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Cloud( b );
	}

	Background_CloudRain::Background_CloudRain( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_CloudRain::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Cloud( b );
		Background::AddRainLayer( b );
	}
}
