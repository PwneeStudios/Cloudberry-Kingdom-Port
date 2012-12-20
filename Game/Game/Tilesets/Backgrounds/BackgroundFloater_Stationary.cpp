#include <global_header.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"

namespace CloudberryKingdom
{

	BackgroundFloater_Stationary::BackgroundFloater_Stationary( const boost::shared_ptr<Level> &level ) : BackgroundFloater( level )
	{
	}

	void BackgroundFloater_Stationary::PhsxStep( const boost::shared_ptr<BackgroundFloaterList> &list )
	{
	}

	void BackgroundFloater_Stationary::Draw()
	{
		Tools::QDrawer->DrawQuad( MyQuad->Quad_Renamed );
	}
}
