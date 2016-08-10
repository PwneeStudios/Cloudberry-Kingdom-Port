#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/Guide.h"

#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Games/GameType.h"


#include <Core\Tools\Set.h>

namespace CloudberryKingdom
{

	ShowGuide::ShowGuide() {}
	boost::shared_ptr<ShowGuide> ShowGuide::ShowGuide_Construct()
	{
		GUI_Panel::GUI_Panel_Construct();

		Bob::GuideActivated = true;

		Active = true;
		PauseOnPause = true;

		Tags->Add( GameObject::Tag_REMOVE_ON_LEVEL_FINISH );

		return boost::static_pointer_cast<ShowGuide>( shared_from_this() );
	}

	void ShowGuide::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();

		Bob::GuideActivated = false;
	}

	void ShowGuide::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( !Active )
			return;

		boost::shared_ptr<Level> level = MyGame->MyLevel;

		// Don't affect speed if a replay is being watched
		if ( level->Replay || level->Watching )
			return;

		// Otherwise show the ShowGuide
		Bob::GuideActivated = true;
	}
}
