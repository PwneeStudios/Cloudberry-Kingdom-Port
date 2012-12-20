#include <global_header.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Sea.h"

namespace CloudberryKingdom
{

	Background_Sea::Background_Sea( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Sea::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Sea( b );
	}

	Background_SeaRain::Background_SeaRain( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_SeaRain::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Sea( b );
		Background::AddRainLayer( b );
	}
}
