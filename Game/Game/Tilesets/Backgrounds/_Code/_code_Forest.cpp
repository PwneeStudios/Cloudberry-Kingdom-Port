#include <small_header.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Forest.h"


namespace CloudberryKingdom
{

	Background_Forest::Background_Forest( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_Forest::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Forest( b );
		Background::TurnOffSnow( b );
	}

	Background_ForestSnow::Background_ForestSnow( const std::wstring &Name ) : BackgroundTemplate( Name )
	{
	}

	void Background_ForestSnow::Code( const boost::shared_ptr<Background> &b )
	{
		BackgroundTemplate::Code( b );

		Background::_code_Forest( b );
		Background::TurnOnSnow( b );
	}
}
