#ifndef CLOUD
#define CLOUD

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
	class AABox;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Cloud : public _Obstacle
	{
	public:
		class CloudTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<SpriteInfo> Sprite;
			Vector2 BoxSize;

		private:
			void InitializeInstanceFields();

public:
			CloudTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		Vector2 Displacement;
		float Shiftiness;
		Vector2 Size;

		std::shared_ptr<QuadClass> MyQuad;

		std::shared_ptr<AABox> Box;

		Cloud();
		Cloud( bool BoxesOnly );

	private:
		int PeriodOffset;

	public:
		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

		virtual void Construct( bool BoxesOnly );

	protected:
		virtual void ActivePhsxStep();

	public:
		virtual void PhsxStep2();

	protected:
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	public:
		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

		virtual void Write( const std::shared_ptr<BinaryWriter> &writer );
		virtual void Read( const std::shared_ptr<BinaryReader> &reader );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOUD
