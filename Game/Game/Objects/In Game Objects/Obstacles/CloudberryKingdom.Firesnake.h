#ifndef CLOUDBERRYKINGDOM_FIRESNAKE
#define CLOUDBERRYKINGDOM_FIRESNAKE

#define _USE_MATH_DEFINES
#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_CircleDeath.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/Firesnake__Auto.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct Firesnake : public _CircleDeath
	{

		virtual ~Firesnake()
		{
#ifdef BOOST_BIN
			OnDestructor( "Firesnake" );
#endif
		}

	
		struct FiresnakeTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Sprite;

		
			void InitializeInstanceFields();


			FiresnakeTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		boost::shared_ptr<QuadClass> MyQuad;

	
		Vector2 Size;

	
		Vector2 Orbit;
		Vector2 Radii;
		int Period, Offset;

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		Firesnake( bool BoxesOnly );

		virtual void PhsxStep();

	
		virtual void DrawGraphics();

	
		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};

}


#endif	//#ifndef CLOUDBERRYKINGDOM_FIRESNAKE
