#include <global_header.h>

namespace CloudberryKingdom
{

	TimeCrisis_Tutorial::TimeCrisis_Tutorial( const boost::shared_ptr<Challenge_TimeCrisis> &TimeCrisis ) : HeroRush_Tutorial( TimeCrisis )
	{
		this->TimeCrisis = TimeCrisis;
	}

	void TimeCrisis_Tutorial::Title()
	{
		ShowTitle = false;

		boost::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Challenge_TimeCrisis::getInstance()->Name );
		//GUI_Text text2 = GUI_Text.SimpleTitle("Revenge of the Double Jump");
		text->MyText->setPos( text->MyText->getPos() + Vector2(0, -110) );
		//text2.MyText.Pos += new Vector2(0, 300);
		//CampaignHelper.AbusiveColor(text2.MyText);

		MyGame->AddGameObject( text );
		MyGame->WaitThenDo( 0, boost::make_shared<AddGameObjectHelper>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ), text ) );
	}
}
