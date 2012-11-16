#ifndef WALL
#define WALL

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
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}




namespace CloudberryKingdom
{
	class Wall : public BlockBase
	{
	public:
		enum BufferType
		{
			BufferType_PUSH,
			BufferType_SPACE
		};
	public:
		class WallTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<SpriteInfo> Sprite;

		private:
			void InitializeInstanceFields();

public:
			WallTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	private:
		bool Horizontal;
	public:
		static std::shared_ptr<Wall> MakeWall( LevelGeometry geometry );

	private:
		bool Spiked;
	public:
		void Spikify();

	private:
		void MakeSpike( int count, float pos );

	public:
		float Speed;
		float Accel;
		int InitialDelay;

		virtual void MakeNew();

	private:
		std::shared_ptr<QuadClass> MyQuad;
	public:
		Wall( bool BoxesOnly );

		virtual void ResetPieces();

		float StartOffset;
		void Init();

		void MoveBack( Vector2 shift );

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

	private:
		float ShakeIntensity, CurShakeIntensity;
		float MinShakeIntensity;
		float ShakeLength;
		Vector2 Offset;
		void Shake();

		Vector2 CalcPosition( float t );

	public:
		BufferType MyBufferType;
		float Space;

		void DoInteraction( const std::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Draw();

		virtual void Extend( Side side, float pos );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef WALL
