#ifndef WALL
#define WALL

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Obstacles/Spike.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct SpriteInfo;
}

namespace CloudberryKingdom
{
	struct QuadClass;
}

namespace CloudberryKingdom
{
	struct Bob;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}




namespace CloudberryKingdom
{
	struct Wall : public BlockBase
	{

		virtual ~Wall()
		{
#ifdef BOOST_BIN
			OnDestructor( "Wall" );
#endif
		}

	
		enum BufferType
		{
			BufferType_PUSH,
			BufferType_SPACE
		};
	
		struct WallTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Sprite;

		
			void InitializeInstanceFields();


			WallTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		bool Horizontal;
	
		static boost::shared_ptr<Wall> MakeWall( LevelGeometry geometry );

	
		bool Spiked;
	
		void Spikify();

	
		void MakeSpike( int count, float pos );

	
		float Speed;
		float Accel;
		int InitialDelay;

		virtual void MakeNew();

	
		boost::shared_ptr<QuadClass> MyQuad;
	
		Wall( bool BoxesOnly );

		virtual void ResetPieces();

		float StartOffset;
		void Init();

		void MoveBack( Vector2 shift );

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

	
		float ShakeIntensity, CurShakeIntensity;
		float MinShakeIntensity;
		float ShakeLength;
		Vector2 Offset;
		void Shake();

		Vector2 CalcPosition( float t );

	
		BufferType MyBufferType;
		float Space;

		void DoInteraction( const boost::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Draw();

		virtual void Extend( Side side, float pos );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef WALL
