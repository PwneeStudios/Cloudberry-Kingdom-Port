#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	Rush::RushOnTimeExpiredLambda::RushOnTimeExpiredLambda( const std::shared_ptr<Rush> &rush )
	{
		this->rush = rush;
	}

	void Rush::RushOnTimeExpiredLambda::Apply( const std::shared_ptr<GUI_Timer_Base> &Timer )
	{
		std::shared_ptr<GameData> game = Timer->MyGame;
		std::shared_ptr<Level> level = game->MyLevel;

		// Remove the timer
		Timer->SlideOut( GUI_Panel::PresetPos_TOP );
		Timer->Active = false;

		// End the level
		level->EndLevel();

		// Void the final door
		if ( level->getFinalDoor() != 0 )
			level->getFinalDoor()->getOnOpen().reset();

		game->AddToDo( std::make_shared<KillAllPlayersHelper>( rush, game ) );
	}

	Rush::OnLevelBeginLambda::OnLevelBeginLambda()
	{
	}

	bool Rush::OnLevelBeginLambda::Apply( const std::shared_ptr<Level> &level )
	{
		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
		return false;
	}

	Rush::KillAllPlayersHelper::KillAllPlayersHelper( const std::shared_ptr<Rush> &rush, const std::shared_ptr<GameData> &game )
	{
		this->rush = rush;
		this->game = game;
	}

	bool Rush::KillAllPlayersHelper::Apply()
	{
		std::shared_ptr<Level> level = game->MyLevel;

		// Kill all the players
		for ( BobVec::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
		{
			if ( ( *bob )->IsVisible() )
			{
				ParticleEffects::PiecePopFart( level, ( *bob )->getCore()->Data.Position );
				( *bob )->getCore()->Show = false;
			}

			if ( !( *bob )->Dead && !( *bob )->Dying )
				( *bob )->Die( BobDeathType_NONE, true, false );
		}

		// Add the Game Over panel, check for Awardments
		game->WaitThenDo( 105, std::make_shared<ShowEndScreenProxy>( rush ) );

		return true;
	}

	void Rush::OnTimeExpired( const std::shared_ptr<GUI_Timer_Base> &Timer )
	{
	}

	void Rush::Start( int StartLevel )
	{
		Challenge::Start( StartLevel );
		StartIndex = StartLevel;

		// Create the timer
		Timer = MakeMagic( GUI_Timer, () );

		// Set the time expired function
		Timer->OnTimeExpired->Add( std::make_shared<RushOnTimeExpiredLambda>( std::static_pointer_cast<Rush>( shared_from_this() ) ) );

		// Create the string world, and add the relevant game objects
		MyStringWorld = std::make_shared<StringWorldTimed>( std::make_shared<PassGetSeedAsLambda>( std::static_pointer_cast<Challenge>( shared_from_this() ) ), Timer );
		StringWorldTimed_Construct( MyStringWorld, std::make_shared<PassGetSeedAsLambda>( std::static_pointer_cast<Challenge>( shared_from_this() ) ), Timer );
		MyStringWorld->StartLevelMusic.reset();

		// Start menu
		MyStringWorld->OnLevelBegin = std::make_shared<OnLevelBeginLambda>();


		// Invert level

		// Additional preprocessing
		SetGameParent( MyStringWorld );
		AdditionalPreStart();

		// Start
		MyStringWorld->Init( StartLevel );
	}

	void Rush::AdditionalPreStart()
	{
	}

	void Rush::InitializeInstanceFields()
	{
		StartIndex = 0;
	}
}
