#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/ExplodeBobs.h"

#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreScreen.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"

#include "Game/Player/PlayerData.h"
#include "Core/Sound/EzSound.h"

#include "Hacks/List.h"
#include "Hacks/Compare.h"

namespace CloudberryKingdom
{

	ExplodeBobs::ExplodeBobs( int speed ) :
		MySpeed( 0 ),
		Count( 0 ),
		InitialDelay_MultipleBobs( 0 ), Delay( 0 ), InitialDelay_OneBob( 0 )
	{
	}
	boost::shared_ptr<ExplodeBobs> ExplodeBobs::ExplodeBobs_Construct( int speed )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Active = true;
		PauseOnPause = true;

		SetSpeed( speed );

		return boost::static_pointer_cast<ExplodeBobs>( shared_from_this() );
	}

	void ExplodeBobs::SetSpeed( int speed )
	{
		MySpeed = speed;
		switch ( MySpeed )
		{
			case Speed_REGULAR:
				ScoreScreen::UseZoomIn = true;
				InitialDelay_MultipleBobs = 48;
				InitialDelay_OneBob = 27;

				//ScoreScreen.UseZoomIn = false;
				//InitialDelay_MultipleBobs = 56;
				//InitialDelay_OneBob = 35;

				break;

			case Speed_FAST:
				InitialDelay_MultipleBobs = InitialDelay_MultipleBobs = 20;
				Delay = 20;
				break;
		}
	}

	void ExplodeBobs::Finish()
	{
		if ( OnDone != 0 )
			OnDone->Apply();

		Release();
	}

	int ExplodeBobs::CompareBobs( const boost::shared_ptr<Bob> &A, const boost::shared_ptr<Bob> &B )
	{
		return Compare(A->getCore()->Data.Position.X, B->getCore()->Data.Position.X);
	}

	void ExplodeBobs::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( !Active )
			return;

		boost::shared_ptr<Level> level = getCore()->MyLevel;

		Count++;

		// Decide how long to wait before starting the action
		int InitialDelay;
		if ( PlayerManager::GetNumPlayers() == 1 )
			InitialDelay = InitialDelay_OneBob;
		else
			InitialDelay = InitialDelay_MultipleBobs;

		// Do nothing until that wait period is over
		if ( Count < InitialDelay )
			return;

		// Afterward blow up a bob periodicially
		if ( ( Count - InitialDelay ) % Delay == 0 )
		{
			BobVec bobs = BobVec();
			for ( BobVec::const_iterator bob = getCore()->MyLevel->Bobs.begin(); bob != getCore()->MyLevel->Bobs.end(); ++bob )
				if ( ( *bob )->getCore()->Show && ( *bob )->GetPlayerData()->IsAlive )
					bobs.push_back( *bob );
			//bobs.Sort( CompareBobs );
			Sort( bobs, CompareBobs );

			if ( bobs.empty() )
				Finish();
			else
			{
				// Kill the first bob in the list
				boost::shared_ptr<Bob> targetbob = bobs[ 0 ];

				Fireball::Explosion( targetbob->getCore()->Data.Position, targetbob->getCore()->MyLevel );
				Fireball::ExplodeSound->Play();

				targetbob->getCore()->Show = false;
				targetbob->Dead = true;
				if (!targetbob->Dead && !targetbob->Dying) targetbob->DeadCount = 0;
			}
		}
	}

	void ExplodeBobs::InitializeInstanceFields()
	{
		Count = 0;
		InitialDelay_MultipleBobs = 56;
		Delay = 40;
		InitialDelay_OneBob = 28;
	}
}
