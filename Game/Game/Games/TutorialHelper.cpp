#include <global_header.h>







namespace CloudberryKingdom
{

	TutorialHelper::TextKillerHelper::TextKillerHelper( const std::shared_ptr<GUI_Text> &text )
	{
		this->text = text;
	}

	void TutorialHelper::TextKillerHelper::Apply()
	{
		text->Kill( false );
	}

	TutorialHelper::ReadyGo_GoProxy::ReadyGo_GoProxy( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &End )
	{
		this->game = game;
		this->End = End;
	}

	void TutorialHelper::ReadyGo_GoProxy::Apply()
	{
		TutorialHelper::ReadyGo_Go( game, End );
	}

Vector2 TutorialHelper::ReadyGoPos = Vector2( 0, 80 );

	void TutorialHelper::ReadyGo( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &End )
	{
		std::shared_ptr<GUI_Text> text = std::make_shared<GUI_Text>( Localization::Words_READY, ReadyGoPos );
		text->FixedToCamera = true;
		game->AddGameObject( text );

		game->WaitThenDo( 36, std::make_shared<TextKillerHelper>( text ) );
		game->WaitThenDo( 40, std::make_shared<ReadyGo_GoProxy>( game, End ) );
	}

	void TutorialHelper::ReadyGo_Go( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &End )
	{
		std::shared_ptr<GUI_Text> text = std::make_shared<GUI_Text>( Localization::Words_GO, ReadyGoPos );
		text->MyPile->MyPopPitch = 3;
		text->FixedToCamera = true;
		game->AddGameObject( text );

		game->WaitThenDo( 20, End );
		game->WaitThenDo( 30, std::make_shared<TextKillerHelper>( text ) );
	}
}
