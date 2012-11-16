#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


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
				AnimSpeed = __max( .35f,.1f * abs( MyBob->getCore()->Data.Velocity.X ) );
			MyBob->PlayerObject->PlayUpdate( AnimSpeed * 1000 / 60 / 150 );
			//MyBob.PlayerObject.PlayUpdate(1000f * AnimSpeed * Tools.dt / 150f);
			//Console.WriteLine("{0},  {1}", 1000f / 60f, Tools.dt);
		}
	}

	void BobPhsxCharSelect::InitializeInstanceFields()
	{
		OverrideAnimBehavior = false;
	}
}
