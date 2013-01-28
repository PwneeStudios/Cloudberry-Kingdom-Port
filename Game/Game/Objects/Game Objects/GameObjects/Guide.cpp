#include <global_header.h>

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
