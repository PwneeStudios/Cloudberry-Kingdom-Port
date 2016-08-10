#include <small_header.h>
#include "Game/Games/TutorialHelper.h"

#include "Game/Localization.h"
#include "Game/Games/GameType.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"



namespace CloudberryKingdom
{

	TutorialHelper::TextKillerHelper::TextKillerHelper( const boost::shared_ptr<GUI_Text> &text )
	{
		this->text = text;
	}

	void TutorialHelper::TextKillerHelper::Apply()
	{
		text->Kill( false );
	}

	TutorialHelper::ReadyGo_GoProxy::ReadyGo_GoProxy( const boost::shared_ptr<GameData> &game, const boost::shared_ptr<Lambda> &End )
	{
		this->game = game;
		this->End = End;
	}

	void TutorialHelper::ReadyGo_GoProxy::Apply()
	{
		TutorialHelper::ReadyGo_Go( game, End );
	}

Vector2 TutorialHelper::ReadyGoPos = Vector2( 0, 80 );

	void TutorialHelper::ReadyGo( const boost::shared_ptr<GameData> &game, const boost::shared_ptr<Lambda> &End )
	{
		boost::shared_ptr<GUI_Text> text = MakeMagic( GUI_Text, ( Localization::Words_Ready, ReadyGoPos ));
		text->FixedToCamera = true;
		game->AddGameObject( text );

		game->WaitThenDo( 36, boost::make_shared<TextKillerHelper>( text ) );
		game->WaitThenDo( 40, boost::make_shared<ReadyGo_GoProxy>( game, End ) );
	}

	void TutorialHelper::ReadyGo_Go( const boost::shared_ptr<GameData> &game, const boost::shared_ptr<Lambda> &End )
	{
		boost::shared_ptr<GUI_Text> text = MakeMagic( GUI_Text, ( Localization::Words_Go, ReadyGoPos ) );
		text->MyPile->MyPopPitch = 3;
		text->FixedToCamera = true;
		game->AddGameObject( text );

		game->WaitThenDo( 20, End );
		game->WaitThenDo( 30, boost::make_shared<TextKillerHelper>( text ) );
	}
}
