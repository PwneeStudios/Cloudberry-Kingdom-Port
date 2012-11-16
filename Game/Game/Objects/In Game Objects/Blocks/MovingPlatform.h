#ifndef MOVINGPLATFORM
#define MOVINGPLATFORM

#define _USE_MATH_DEFINES
#include "Block.h"
#include "../Game/Tilesets/TileSet.h"
#include "../Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include <cmath>

namespace CloudberryKingdom
{
	class BlockGroup;
}

namespace CloudberryKingdom
{
	class BlockEmitter;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class MovingPlatform : public BlockBase
	{
	public:
		class ElevatorTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<BlockGroup> Group;

		private:
			void InitializeInstanceFields();

public:
			ElevatorTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		enum MoveType
		{
			MoveType_NORMAL,
			MoveType_SINE
		};
	public:
		MoveType MyMoveType;
		float Amp;
		int Offset;

		Vector2 Range;

		std::shared_ptr<BlockEmitter> Parent;

	private:
		const std::shared_ptr<BlockEmitter_Parameters> &getMyParams() const;

	public:
		virtual bool PermissionToUse();

		virtual void LandedOn( const std::shared_ptr<Bob> &bob );
		virtual void OnUsed();

		virtual void OnMarkedForDeletion();

		virtual void MakeNew();

		virtual void Release();

		MovingPlatform( bool BoxesOnly );

	private:
		BlockEmitter_Parameters::BoxStyle MyBoxStyle;
	public:
		void Init( Vector2 center, Vector2 size, const std::shared_ptr<Level> &level, BlockEmitter_Parameters::BoxStyle boxstyle );


		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef MOVINGPLATFORM
