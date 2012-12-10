#ifndef CLOUDBERRYKINGDOM_FIRESNAKE
#define CLOUDBERRYKINGDOM_FIRESNAKE

#define _USE_MATH_DEFINES
#include <global_header.h>

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
	struct Level;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}



namespace CloudberryKingdom
{
	struct Firesnake : public _CircleDeath
	{
	
		struct FiresnakeTileInfo : public TileInfoBase
		{
		
			std::shared_ptr<SpriteInfo> Sprite;

		
			void InitializeInstanceFields();


			FiresnakeTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		std::shared_ptr<QuadClass> MyQuad;

	
		Vector2 Size;

	
		Vector2 Orbit;
		Vector2 Radii;
		int Period, Offset;

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

		Firesnake( bool BoxesOnly );

		virtual void PhsxStep();

	
		virtual void DrawGraphics();

	
		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_FIRESNAKE
