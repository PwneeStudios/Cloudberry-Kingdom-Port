#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	MakeDarkBottom::MakeDarkBottom( const std::shared_ptr<Level> &level ) : MakeFinalDoorVertical( level )
	{
	}

	void MakeDarkBottom::Phase3()
	{
		MakeFinalDoorVertical::Phase3();

		float MoveAll = 1450;

		// Add dark bottom region
		std::shared_ptr<Region> region = std::make_shared<Region>( MadeDoor->getPos() + Vector2(0, 100 - MoveAll), Vector2(5000, 2000) );
		region->AttachedDoor = MadeDoor;
		MyLevel->AddObject( region );

		float Amount = 560 + MoveAll; // 900;
		MyLevel->FinalCamZone->End.Y -= Amount;
		MyLevel->getFinalDoor()->Move(Vector2(0, -Amount - 900));
	}
}
