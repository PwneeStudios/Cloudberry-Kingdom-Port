#ifndef FLYINGBLOB
#define FLYINGBLOB

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	class TextureOrAnim;
}

namespace CloudberryKingdom
{
	class Particle;
}

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class SimpleObject;
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
	class Bob;
}

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class EzEffectWad;
}

namespace CloudberryKingdom
{
	class EzTextureWad;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}











namespace CloudberryKingdom
{
	class FlyingBlob : public _Obstacle, public IBound
	{
	public:
		class FlyingBlobTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<SpriteInfo> Body;

			Vector2 ObjectSize;

			std::shared_ptr<TextureOrAnim> GooSprite;

		private:
			void InitializeInstanceFields();

public:
			FlyingBlobTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		enum BlobColor
		{
			BlobColor_GREEN,
			BlobColor_PINK,
			BlobColor_BLUE,
			BlobColor_GREY,
			BlobColor_GOLD
		};
	public:
		enum PhsxType
		{
			PhsxType_PRESCRIBED,
			PhsxType_TO_TARGET
		};
	public:
		enum PrescribedMoveType
		{
			PrescribedMoveType_LINE,
			PrescribedMoveType_CIRCLE,
			PrescribedMoveType_STAR
		};

	private:
		static std::shared_ptr<Particle> BlobGooTemplate;
		static std::shared_ptr<EzSound> SquishSound;

	public:
		int Period, Offset;
		Vector2 Displacement;

		Vector2 Target, TargetVel;
		bool HasArrived, RemoveOnArrival;
		float ArrivedRadius;
		float MaxVel, MaxAcc, DistAccMod;
		bool FinalizedParams;
		float Damp;
		float DampRange;

		bool GiveVelocity;

		PrescribedMoveType MyMoveType;
		PhsxType MyPhsxType;

		BlobColor MyColor;

	private:
		static std::vector<float> BobMaxSpeed;
		static float BobXAccel;
		static float BobXFriction;

	public:
		std::shared_ptr<SimpleObject> MyObject;
		std::shared_ptr<QuadClass> MyQuad;
		float MyAnimSpeed;

		/// <summary>
		/// Source from which to copy object vertex info
		/// </summary>
		std::shared_ptr<FlyingBlob> CopySource;

		/// <summary>
		/// Whether to delete the blob permanently when it dies
		/// </summary>
		bool DeleteOnDeath;

		std::shared_ptr<AABox> Box, Box2;

		int Life, StartLife;

		int Direction;

		bool NeverSkip;

	private:
		std::shared_ptr<Bob> KillingBob;

	public:
		void SetColor( BlobColor color );

	private:
		static std::shared_ptr<EzTexture> GetGooTexture( BlobColor color );

	public:
		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

		FlyingBlob( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		void SetAnimation();

		FlyingBlob( const std::wstring &file, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad );

		void Death();

		void Squish( Vector2 vel );

		void XAccel( bool Left, bool Right, bool Run );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		Vector2 CalcPosition( float t );


	private:
		void UpdatePos();

	public:
		virtual void PhsxStep();

	protected:
		virtual void ActivePhsxStep();

	public:
		virtual void PhsxStep2();

		void AnimStep();

		void UpdateObject();

	protected:
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	public:
		void MoveToBounded( Vector2 shift );

		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

		void SetStandardTargetParams();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef FLYINGBLOB
