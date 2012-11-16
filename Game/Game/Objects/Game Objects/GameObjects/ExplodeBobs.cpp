#include "ExplodeBobs.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreScreen.h"
#include "Core/Lambdas/Lambda.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

	ExplodeBobs::ExplodeBobs( Speed speed )
	{
		InitializeInstanceFields();
		Active = true;
		PauseOnPause = true;

		SetSpeed( speed );
	}

	void ExplodeBobs::SetSpeed( Speed speed )
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

	int ExplodeBobs::CompareBobs( const std::shared_ptr<Bob> &A, const std::shared_ptr<Bob> &B )
	{
		return A->getCore()->Data.Position->X.compare(B->getCore()->Data.Position->X);
	}

	void ExplodeBobs::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( !Active )
			return;

		std::shared_ptr<Level> level = getCore()->MyLevel;

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
			std::vector<Bob*> bobs = std::vector<Bob*>();
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( std::vector<Bob*>::const_iterator bob = getCore()->MyLevel->Bobs.begin(); bob != getCore()->MyLevel->Bobs.end(); ++bob )
				if ( ( *bob )->Core->Show && ( *bob )->GetPlayerData()->IsAlive )
					bobs.push_back( *bob );
			bobs.Sort( CompareBobs );

			if ( bobs.empty() )
				Finish();
			else
			{
				// Kill the first bob in the list
				std::shared_ptr<Bob> targetbob = bobs[ 0 ];

				Fireball::Explosion( targetbob->getCore()->Data.Position, targetbob->getCore()->MyLevel );
				Fireball::ExplodeSound->Play();

				targetbob->getCore()->Show = false;
				targetbob->Dead = true;
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
