#ifndef MAKEFINALDOOR
#define MAKEFINALDOOR

#include <global_header.h>


namespace CloudberryKingdom
{
	struct MakeFinalDoor : public MakeThing, public std::enable_shared_from_this<MakeFinalDoor>
	{
	
		struct VanillaFillEndPieceLambda : public Lambda_1<std::shared_ptr<BlockBase> >
		{
		
			VanillaFillEndPieceLambda();

			void Apply( const std::shared_ptr<BlockBase> &block );
		};

	
		struct ModBlockLambda : public Lambda_1<std::shared_ptr<BlockBase> >
		{
		
			std::shared_ptr<MakeFinalDoor> mfd;
		
			ModBlockLambda( const std::shared_ptr<MakeFinalDoor> &mfd );

			void Apply( const std::shared_ptr<BlockBase> &block );
		};

	
		struct FindFinalBlockLambda : public LambdaFunc_1<std::shared_ptr<BlockBase> , bool>
		{
		
			FindFinalBlockLambda();

			bool Apply( const std::shared_ptr<BlockBase> &block );
		};

	
		struct BoxTRyLambda : public LambdaFunc_1<std::shared_ptr<BlockBase> , float>
		{
		
			BoxTRyLambda();

			float Apply( const std::shared_ptr<BlockBase> &block );
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

	
		BlockVec FinalBlocks;

	
		MakeFinalDoor( const std::shared_ptr<Level> &level );

		virtual void Phase1();

		void ModBlock( const std::shared_ptr<BlockBase> &block );

		virtual void Phase2();

		virtual void Phase3();

		static void AttachDoorAction( const std::shared_ptr<ILevelConnector> &door );

		static void SetFinalDoor( const std::shared_ptr<Door> &door, const std::shared_ptr<Level> &level, Vector2 FinalPos );

	
		void InitializeInstanceFields();
	};

	struct FindCamZoneLambda : public LambdaFunc_1<std::shared_ptr<ObjectBase> , bool>
	{

	
		static void InitializeStatics();

	
		static std::shared_ptr<FindCamZoneLambda> FindCamZoneLambda_Static;

		FindCamZoneLambda();

		bool Apply( const std::shared_ptr<ObjectBase> &obj );
	};
}


#endif	//#ifndef MAKEFINALDOOR
