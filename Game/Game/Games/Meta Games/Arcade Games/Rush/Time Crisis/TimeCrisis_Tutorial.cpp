#include "TimeCrisis_Tutorial.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Time Crisis/TimeCrisis.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

	TimeCrisis_Tutorial::TimeCrisis_Tutorial( const std::shared_ptr<Challenge_TimeCrisis> &TimeCrisis ) : HeroRush_Tutorial( TimeCrisis )
	{
		this->TimeCrisis = TimeCrisis;
	}

	void TimeCrisis_Tutorial::Title()
	{
		ShowTitle = false;

		std::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Challenge_TimeCrisis::getInstance()->Name );
		//GUI_Text text2 = GUI_Text.SimpleTitle("Revenge of the Double Jump");
		text->MyText->setPos( text->MyText->getPos() + Vector2(0, -110) );
		//text2.MyText.Pos += new Vector2(0, 300);
		//CampaignHelper.AbusiveColor(text2.MyText);

		MyGame->AddGameObject( text );
		MyGame->WaitThenDo( 0, std::make_shared<AddGameObjectHelper>( this, text ) );
	}
}
