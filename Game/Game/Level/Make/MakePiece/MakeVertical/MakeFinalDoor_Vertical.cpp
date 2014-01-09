#include <small_header.h>
#include "Game/Level/Make/MakePiece/MakeVertical/MakeFinalDoor_Vertical.h"

#include "Game/Objects/In Game Objects/Blocks/Block.h"
#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/MakePiece/MakeThing.h"
#include "Game/Level/Make/MakePiece/MakeSingle/MakeFinalDoor.h"
#include "Game/Objects/Door/Door.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Tools/Tools.h"

#include "Game/Level/LevelPiece.h"
#include "Game/Level/Make/ComputerRecording.h"

namespace CloudberryKingdom
{

	float MakeFinalDoorVertical::ElementPositionProjectY::Apply( const boost::shared_ptr<BlockBase> &element )
	{
		return element->getCore()->Data.Position.Y;
	}

	MakeFinalDoorVertical::MatchUsedLambda::MatchUsedLambda()
	{
	}

	bool MakeFinalDoorVertical::MatchUsedLambda::Apply( const boost::shared_ptr<BlockBase> &match )
	{
		return match->getCore()->GenData.Used;
	}

	MakeFinalDoorVertical::MakeFinalDoorVertical( const boost::shared_ptr<Level> &level )
	{
		MyLevel = level;
	}

	void MakeFinalDoorVertical::Phase1()
	{
		MakeThing::Phase1();
	}

	void MakeFinalDoorVertical::Phase2()
	{
		MakeThing::Phase2();

		// Find a final block that was used by the computer.
		if ( MyLevel->CurMakeData->PieceSeed->GeometryType == LevelGeometry_DOWN )
			FinalBlock = Tools::ArgMin<boost::shared_ptr<BlockBase> >( Tools::FindAll<boost::shared_ptr<BlockBase> >( MyLevel->Blocks, boost::make_shared<MatchUsedLambda>() ), boost::make_shared<ElementPositionProjectY>() );
		else
			FinalBlock = Tools::ArgMax<boost::shared_ptr<BlockBase> >( Tools::FindAll<boost::shared_ptr<BlockBase> >( MyLevel->Blocks, boost::make_shared<MatchUsedLambda>() ), boost::make_shared<ElementPositionProjectY>() );

		FinalPos = FinalBlock->getCore()->Data.Position;

		// Cut computer run short once the computer reaches the door.
		int Earliest = 100000;
		Vector2 pos = FinalPos;
		float Closest = -1;
		int NewLastStep = MyLevel->LastStep;
		for ( int i = 0; i < MyLevel->CurPiece->NumBobs; i++ )
			for ( int j = MyLevel->LastStep - 1; j > 0; j-- )
			{
				Vector2 BobPos = MyLevel->CurPiece->Recording_Renamed[ i ]->AutoLocs[ j ];
				float Dist = ( BobPos - FinalPos ).Length();

				if ( Closest == -1 || Dist < Closest )
				{
					Earliest = __min( Earliest, j );
					Closest = Dist;
					pos = BobPos;
					NewLastStep = j;
				}
			}

		MyLevel->LastStep = __min( Earliest, MyLevel->LastStep );
	}

	void MakeFinalDoorVertical::Phase3()
	{
		MakeThing::Phase3();

		// Add door
		MadeDoor = MyLevel->PlaceDoorOnBlock( FinalPos, FinalBlock, false );
		MadeDoor->getCore()->EditorCode1 = LevelConnector::EndOfLevelCode;

		// Attach an action to the door
		MakeFinalDoor::AttachDoorAction( MadeDoor );
		//door.OnOpen = ((StringWorldGameData)Tools::WorldMap).EOL_StringWorldDoorAction;
	}

	void MakeFinalDoorVertical::Cleanup()
	{
		MadeDoor.reset();
		FinalBlock.reset();
	}
}
