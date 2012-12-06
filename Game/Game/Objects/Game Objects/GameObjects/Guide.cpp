#include <global_header.h>

namespace CloudberryKingdom
{

	ShowGuide::ShowGuide()
	{
		Bob::GuideActivated = true;

		Active = true;
		PauseOnPause = true;

		Tags->Add( GameObject::Tag_REMOVE_ON_LEVEL_FINISH );
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

		std::shared_ptr<Level> level = MyGame->MyLevel;

		// Don't affect speed if a replay is being watched
		if ( level->Replay || level->Watching )
			return;

		// Otherwise show the ShowGuide
		Bob::GuideActivated = true;
	}
}
