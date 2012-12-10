#ifndef MAKEFINALDOOR_VERTICAL
#define MAKEFINALDOOR_VERTICAL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MakeFinalDoorVertical : public MakeThing
	{
	
		struct ElementPositionProjectY : public LambdaFunc_1<std::shared_ptr<BlockBase> , float>
		{
		
			float Apply( const std::shared_ptr<BlockBase> &element );
		};

	
		struct MatchUsedLambda : public LambdaFunc_1<std::shared_ptr<BlockBase> , bool>
		{
		
			MatchUsedLambda();

			bool Apply( const std::shared_ptr<BlockBase> &match );
		};

	
		std::shared_ptr<Level> MyLevel;

		/// <summary>
		/// The block on which the final door rests on.
		/// </summary>
	
		std::shared_ptr<BlockBase> FinalBlock;

		/// <summary>
		/// The position of the final door.
		/// </summary>
		Vector2 FinalPos;

	
		MakeFinalDoorVertical( const std::shared_ptr<Level> &level );

		virtual void Phase1();

		virtual void Phase2();

	
		std::shared_ptr<Door> MadeDoor;
	
		virtual void Phase3();

		virtual void Cleanup();
	};
}


#endif	//#ifndef MAKEFINALDOOR_VERTICAL
