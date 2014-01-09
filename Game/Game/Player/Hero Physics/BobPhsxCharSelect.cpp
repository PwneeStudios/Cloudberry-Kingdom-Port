#include <small_header.h>
#include "Game/Player/Hero Physics/BobPhsxCharSelect.h"

#include "Game/Player/Hero Physics/Normal.h"

#include "Game/Objects/Bob/Bob.h"

namespace CloudberryKingdom
{

	void BobPhsxCharSelect::PhsxStep2()
	{
		BobPhsxNormal::PhsxStep2();

		OnGround = true;

		//Offset.Y += MyBob.Core.Data.Velocity.Y;
	}

	void BobPhsxCharSelect::AnimStep()
	{
		if ( !OverrideAnimBehavior )
			BobPhsxNormal::AnimStep();
		else
		{
			float AnimSpeed = 1;
			if ( MyBob->PlayerObject->DestinationAnim() == 1 && MyBob->PlayerObject->Loop )
				AnimSpeed = __max( .35f,.1f * fabs( MyBob->getCore()->Data.Velocity.X ) );
			MyBob->PlayerObject->PlayUpdate( AnimSpeed * 1000.f / 60.f / 150.f );
			//MyBob.PlayerObject.PlayUpdate(1000f * AnimSpeed * Tools::dt / 150f);
			//Console.WriteLine("{0},  {1}", 1000f / 60f, Tools::dt);
		}
	}

	void BobPhsxCharSelect::InitializeInstanceFields()
	{
		OverrideAnimBehavior = false;
	}
}
