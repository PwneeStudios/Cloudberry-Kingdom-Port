#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	Rush::RushOnTimeExpiredLambda::RushOnTimeExpiredLambda( const boost::shared_ptr<Rush> &rush )
	{
		this->rush = rush;
	}

	void Rush::RushOnTimeExpiredLambda::Apply( const boost::shared_ptr<GUI_Timer_Base> &Timer )
	{
		boost::shared_ptr<GameData> game = Timer->MyGame;
		boost::shared_ptr<Level> level = game->MyLevel;

		// Remove the timer
		Timer->SlideOut( GUI_Panel::PresetPos_TOP );
		Timer->Active = false;

		// End the level
		level->EndLevel();

		// Void the final door
		if ( level->getFinalDoor() != 0 )
			level->getFinalDoor()->getOnOpen().reset();

		game->AddToDo( boost::make_shared<KillAllPlayersHelper>( rush, game ) );
	}

	Rush::OnLevelBeginLambda::OnLevelBeginLambda()
	{
	}

	bool Rush::OnLevelBeginLambda::Apply( const boost::shared_ptr<Level> &level )
	{
		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
		return false;
	}

	Rush::KillAllPlayersHelper::KillAllPlayersHelper( const boost::shared_ptr<Rush> &rush, const boost::shared_ptr<GameData> &game )
	{
		this->rush = rush;
		this->game = game;
	}

	bool Rush::KillAllPlayersHelper::Apply()
	{
		boost::shared_ptr<Level> level = game->MyLevel;

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
		game->WaitThenDo( 105, boost::make_shared<ShowEndScreenProxy>( rush ) );

		return true;
	}

	void Rush::OnTimeExpired( const boost::shared_ptr<GUI_Timer_Base> &Timer )
	{
	}

	void Rush::Start( int StartLevel )
	{
		Challenge::Start( StartLevel );
		StartIndex = StartLevel;

		// Create the timer
		Timer = MakeMagic( GUI_Timer, () );

		// Set the time expired function
		Timer->OnTimeExpired->Add( boost::make_shared<RushOnTimeExpiredLambda>( boost::static_pointer_cast<Rush>( shared_from_this() ) ) );

		// Create the string world, and add the relevant game objects
		MyStringWorld = boost::make_shared<StringWorldTimed>( boost::make_shared<PassGetSeedAsLambda>( boost::static_pointer_cast<Challenge>( shared_from_this() ) ), Timer );
		StringWorldTimed_Construct( MyStringWorld, boost::make_shared<PassGetSeedAsLambda>( boost::static_pointer_cast<Challenge>( shared_from_this() ) ), Timer );
		MyStringWorld->StartLevelMusic.reset();

		// Start menu
		MyStringWorld->OnLevelBegin = boost::make_shared<OnLevelBeginLambda>();


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
