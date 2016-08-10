#ifndef MAKEFINALDOOR
#define MAKEFINALDOOR

#include <small_header.h>

//#include "Game/Collision Detection/AABox.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
//#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/MakePiece/MakeThing.h"
//#include "Game/Objects/Door/Door.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/Special/CameraZone.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"



namespace CloudberryKingdom
{
	struct MakeFinalDoor : public MakeThing, public boost::enable_shared_from_this<MakeFinalDoor>
	{

		virtual ~MakeFinalDoor()
		{
#ifdef BOOST_BIN
			OnDestructor( "MakeFinalDoor" );
#endif
		}

	
		struct VanillaFillEndPieceLambda : public Lambda_1<boost::shared_ptr<BlockBase> >
		{
		
			VanillaFillEndPieceLambda();

			void Apply( const boost::shared_ptr<BlockBase> &block );
		};

	
		struct ModBlockLambda : public Lambda_1<boost::shared_ptr<BlockBase> >
		{
		
			boost::shared_ptr<MakeFinalDoor> mfd;
		
			ModBlockLambda( const boost::shared_ptr<MakeFinalDoor> &mfd );

			void Apply( const boost::shared_ptr<BlockBase> &block );
		};

	
		struct FindFinalBlockLambda : public LambdaFunc_1<boost::shared_ptr<BlockBase> , bool>
		{
		
			FindFinalBlockLambda();

			bool Apply( const boost::shared_ptr<BlockBase> &block );
		};

	
		struct BoxTRyLambda : public LambdaFunc_1<boost::shared_ptr<BlockBase> , float>
		{
		
			BoxTRyLambda();

			float Apply( const boost::shared_ptr<BlockBase> &block );
		};

	
		boost::shared_ptr<Level> MyLevel;

		/// <summary>
		/// The block on which the final door rests on.
		/// </summary>
	
		boost::shared_ptr<BlockBase> FinalBlock;

		/// <summary>
		/// The position of the final door.
		/// </summary>
		Vector2 FinalPos;

	
		BlockVec FinalBlocks;

	
		MakeFinalDoor( const boost::shared_ptr<Level> &level );

		virtual void Phase1();

		void ModBlock( const boost::shared_ptr<BlockBase> &block );

		virtual void Phase2();

		virtual void Phase3();

		static void AttachDoorAction( const boost::shared_ptr<ILevelConnector> &door );

		static void SetFinalDoor( const boost::shared_ptr<Door> &door, const boost::shared_ptr<Level> &level, Vector2 FinalPos );

	
		void InitializeInstanceFields();
	};

	struct FindCamZoneLambda : public LambdaFunc_1<boost::shared_ptr<ObjectBase> , bool>
	{

	
		static void InitializeStatics();

	
		static boost::shared_ptr<FindCamZoneLambda> FindCamZoneLambda_Static;

		FindCamZoneLambda();

		bool Apply( const boost::shared_ptr<ObjectBase> &obj );
	};
}


#endif	//#ifndef MAKEFINALDOOR
