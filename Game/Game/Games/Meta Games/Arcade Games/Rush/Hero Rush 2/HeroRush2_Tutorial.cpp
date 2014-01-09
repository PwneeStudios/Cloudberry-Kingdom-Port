#include <small_header.h>
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2_Tutorial.h"

#include "Game/Localization.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "Game/Objects/Game Objects/GameObjects/Listener.h"

#include "Core/Text/EzText.h"
#include "Game/Games/GameType.h"

namespace CloudberryKingdom
{

	HeroRush2_Tutorial::HeroRush2_Tutorial( const boost::shared_ptr<Challenge_HeroRush2> &HeroRush2 ) : HeroRush_Tutorial( HeroRush2 )
	{
		this->HeroRush2 = HeroRush2;
	}

	void HeroRush2_Tutorial::Title()
	{
		ShowTitle = false;

		boost::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Localization::Words_HybridRush );
		text->MyText->setPos( text->MyText->getPos() + Vector2(0, -110) );

		MyGame->AddGameObject( text );
		MyGame->WaitThenDo( 0, boost::make_shared<AddGameObjectHelper>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ), text ) );
	}
}
