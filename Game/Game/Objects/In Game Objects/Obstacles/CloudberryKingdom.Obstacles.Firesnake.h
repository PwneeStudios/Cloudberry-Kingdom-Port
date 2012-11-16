#ifndef CLOUDBERRYKINGDOM
#define CLOUDBERRYKINGDOM

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	namespace Levels
	{
		class Level;
	}
}

namespace CloudberryKingdom
{
	class ObjectBase;
}













namespace CloudberryKingdom
{
	namespace Obstacles
	{
		class Firesnake : public _CircleDeath
		{
		public:
			class FiresnakeTileInfo : public TileInfoBase
			{
			public:
				std::shared_ptr<SpriteInfo> Sprite;

			private:
				void InitializeInstanceFields();

public:
				FiresnakeTileInfo()
				{
					InitializeInstanceFields();
				}
			};

		public:
			std::shared_ptr<QuadClass> MyQuad;

		private:
			Vector2 Size;

		public:
			Vector2 Orbit;
			Vector2 Radii;
			int Period, Offset;

			virtual void MakeNew();

			virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

			Firesnake( bool BoxesOnly );

			virtual void PhsxStep();

		protected:
			virtual void DrawGraphics();

		public:
			virtual void Move( Vector2 shift );

			virtual void Reset( bool BoxesOnly );

			virtual void Clone( const std::shared_ptr<ObjectBase> &A );
		};
	}
}


#endif	//#ifndef CLOUDBERRYKINGDOM
