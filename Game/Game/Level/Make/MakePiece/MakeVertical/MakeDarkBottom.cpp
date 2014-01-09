#include <small_header.h>
#include "Game/Level/Make/MakePiece/MakeVertical/MakeDarkBottom.h"

#include "Game/Level/Make/MakePiece/MakeVertical/MakeFinalDoor_Vertical.h"
#include "Game/Objects/Game Objects/GameObjects/Region.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"

#include "Game/Objects/Door/Door.h"
#include "Game/Objects/Special/CameraZone.h"

namespace CloudberryKingdom
{

	MakeDarkBottom::MakeDarkBottom( const boost::shared_ptr<Level> &level ) : MakeFinalDoorVertical( level )
	{
	}

	void MakeDarkBottom::Phase3()
	{
		MakeFinalDoorVertical::Phase3();

		float MoveAll = 1450;

		// Add dark bottom region
		boost::shared_ptr<Region> region = MakeMagic( Region, ( MadeDoor->getPos() + Vector2(0, 100 - MoveAll), Vector2(5000, 2000) ) );
		region->AttachedDoor = MadeDoor;
		MyLevel->AddObject( region );

		float Amount = 560 + MoveAll; // 900;
		MyLevel->FinalCamZone->End.Y -= Amount;
		MyLevel->getFinalDoor()->Move(Vector2(0, -Amount - 900));
	}
}
