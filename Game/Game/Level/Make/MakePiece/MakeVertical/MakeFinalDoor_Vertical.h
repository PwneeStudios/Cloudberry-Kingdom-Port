#ifndef MAKEFINALDOOR_VERTICAL
#define MAKEFINALDOOR_VERTICAL

#include <global_header.h>

namespace CloudberryKingdom
{

	struct MakeFinalDoorVertical : public MakeThing
	{

		virtual ~MakeFinalDoorVertical()
		{
#ifdef BOOST_BIN
			OnDestructor( "MakeFinalDoorVertical" );
#endif
		}

	
		struct ElementPositionProjectY : public LambdaFunc_1<boost::shared_ptr<BlockBase> , float>
		{
		
			float Apply( const boost::shared_ptr<BlockBase> &element );
		};

	
		struct MatchUsedLambda : public LambdaFunc_1<boost::shared_ptr<BlockBase> , bool>
		{
		
			MatchUsedLambda();

			bool Apply( const boost::shared_ptr<BlockBase> &match );
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

	
		MakeFinalDoorVertical( const boost::shared_ptr<Level> &level );

		virtual void Phase1();

		virtual void Phase2();

	
		boost::shared_ptr<Door> MadeDoor;
	
		virtual void Phase3();

		virtual void Cleanup();
	};
}


#endif	//#ifndef MAKEFINALDOOR_VERTICAL
