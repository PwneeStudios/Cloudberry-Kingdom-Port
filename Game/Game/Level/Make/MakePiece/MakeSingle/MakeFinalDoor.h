#ifndef MAKEFINALDOOR
#define MAKEFINALDOOR

#include <global_header.h>

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class ILevelConnector;
}

namespace CloudberryKingdom
{
	class Door;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class MakeFinalDoor : public MakeThing
	{
	private:
		class VanillaFillEndPieceLambda : public Lambda_1<BlockBase*>
		{
		public:
			VanillaFillEndPieceLambda();

			void Apply( const std::shared_ptr<BlockBase> &block );
		};

	private:
		class ModBlockLambda : public Lambda_1<BlockBase*>
		{
		private:
			std::shared_ptr<MakeFinalDoor> mfd;
		public:
			ModBlockLambda( const std::shared_ptr<MakeFinalDoor> &mfd );

			void Apply( const std::shared_ptr<BlockBase> &block );
		};

	private:
		class FindFinalBlockLambda : public LambdaFunc_1<BlockBase*, bool>
		{
		public:
			FindFinalBlockLambda();

			bool Apply( const std::shared_ptr<BlockBase> &block );
		};

	private:
		class BoxTRyLambda : public LambdaFunc_1<BlockBase*, float>
		{
		public:
			BoxTRyLambda();

			float Apply( const std::shared_ptr<BlockBase> &block );
		};

	private:
		std::shared_ptr<Level> MyLevel;

		/// <summary>
		/// The block on which the final door rests on.
		/// </summary>
	public:
		std::shared_ptr<BlockBase> FinalBlock;

		/// <summary>
		/// The position of the final door.
		/// </summary>
		Vector2 FinalPos;

	private:
		std::vector<BlockBase*> FinalBlocks;

	public:
		MakeFinalDoor( const std::shared_ptr<Level> &level );

		virtual void Phase1();

		void ModBlock( const std::shared_ptr<BlockBase> &block );

		virtual void Phase2();

		virtual void Phase3();

		static void AttachDoorAction( const std::shared_ptr<ILevelConnector> &door );

		static void SetFinalDoor( const std::shared_ptr<Door> &door, const std::shared_ptr<Level> &level, Vector2 FinalPos );

	private:
		void InitializeInstanceFields();
	};

	class FindCamZoneLambda : public LambdaFunc_1<ObjectBase*, bool>
	{
	public:
		static std::shared_ptr<FindCamZoneLambda> FindCamZoneLambda_Static;

		FindCamZoneLambda();

		bool Apply( const std::shared_ptr<ObjectBase> &obj );
	};
}


#endif	//#ifndef MAKEFINALDOOR
