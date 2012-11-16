#ifndef CHECKPOINT
#define CHECKPOINT

#include <global_header.h>

namespace CloudberryKingdom
{
	class TextureOrAnim;
}

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class Particle;
}

namespace CloudberryKingdom
{
	class AABox;
}

namespace CloudberryKingdom
{
	class SimpleObject;
}

namespace CloudberryKingdom
{
	class LevelPiece;
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


namespace CloudberryKingdom
{
	class Checkpoint : public ObjectBase
	{
	public:
		class CheckpointTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<TextureOrAnim> Sprite;
			Vector2 Size;
			Vector2 TextureSize;

			std::shared_ptr<EzSound> MySound;

			std::shared_ptr<Particle> DieTemplate;
			CheckpointTileInfo();

		private:
			void InitializeInstanceFields();
		};

	public:
		virtual void Release();

		bool Taken, TakenAnimFinished;
	private:
		bool GhostFaded;

		float Taken_Scale, Taken_Alpha;

		static std::shared_ptr<EzSound> MySound;

	public:
		bool SkipPhsx;

		bool Touched;

		std::shared_ptr<AABox> Box;
		SimpleQuad MyQuad;
		BasePoint Base;

		std::shared_ptr<SimpleObject> MyObject;

		std::shared_ptr<LevelPiece> MyPiece;
		int MyPieceIndex;

		virtual void MakeNew();

		Checkpoint();

	private:
		void SetAnimation();

	public:
		void Revert();

	private:
		void ResetTakenAnim();

	public:
		void Die();

		void Init( const std::shared_ptr<Level> &level );

		void AnimStep();

		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Reset( bool BoxesOnly );

		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		void SetAlpha();

		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef CHECKPOINT
