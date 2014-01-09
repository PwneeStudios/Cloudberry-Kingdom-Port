#include <small_header.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Castle.h"

namespace CloudberryKingdom
{

	Background_Castle::Background_Castle( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Castle::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Castle( b );
	}
}
