#include <global_header.h>


namespace CloudberryKingdom
{

	HeroRush2_Tutorial::HeroRush2_Tutorial( const std::shared_ptr<Challenge_HeroRush2> &HeroRush2 ) : HeroRush_Tutorial( HeroRush2 )
	{
		this->HeroRush2 = HeroRush2;
	}

	void HeroRush2_Tutorial::Title()
	{
		ShowTitle = false;

		std::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Localization::Words_HYBRID_RUSH );
		text->MyText->setPos( text->MyText->getPos() + Vector2(0, -110) );

		MyGame->AddGameObject( text );
		MyGame->WaitThenDo( 0, std::make_shared<AddGameObjectHelper>( std::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ), text ) );
	}
}
