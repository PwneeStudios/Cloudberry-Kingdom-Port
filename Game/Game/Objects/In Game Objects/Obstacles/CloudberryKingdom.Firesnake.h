#ifndef CLOUDBERRYKINGDOM
#define CLOUDBERRYKINGDOM

#define _USE_MATH_DEFINES
#include "../Game/Objects/In Game Objects/BaseClasses/_CircleDeath.h"
#include "../Game/Tilesets/TileSet.h"
#include <cmath>

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


#endif	//#ifndef CLOUDBERRYKINGDOM
