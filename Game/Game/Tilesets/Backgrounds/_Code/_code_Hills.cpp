#include <small_header.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Hills.h"

namespace CloudberryKingdom
{

	Background_Hills::Background_Hills( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Hills::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Hills( b );
	}

	Background_HillsRain::Background_HillsRain( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_HillsRain::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Hills( b );
		Background::AddRainLayer( b );
	}
}
