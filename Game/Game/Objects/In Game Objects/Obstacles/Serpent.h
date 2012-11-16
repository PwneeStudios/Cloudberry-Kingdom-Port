#ifndef SERPENT
#define SERPENT

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
	class Level;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Serpent : public _BoxDeath
	{
	public:
		class SerpentTileInfo : public TileInfoBase
		{
		public:
//C# TO C++ CONVERTER NOTE: The variable Serpent was renamed since it is named the same as a user-defined type:
			std::shared_ptr<SpriteInfo> Serpent_Renamed;
			std::shared_ptr<SpriteInfo> Fish;
			Vector2 BoxSize;

		private:
			void InitializeInstanceFields();

public:
			SerpentTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		std::shared_ptr<QuadClass> MyQuad, MyFish;

		int Offset, UpT, DownT, WaitT1, WaitT2;

		Vector2 Start, End;

		bool Exposed;

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

		Serpent( bool BoxesOnly );

		void SetPeriod( int Period );

	protected:
		virtual void ActivePhsxStep();

	public:
		void AnimStep();
		void AnimStep( bool Skip );

	protected:
		virtual void DrawGraphics();

	public:
		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef SERPENT
