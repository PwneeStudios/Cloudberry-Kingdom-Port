#ifndef FLYINGBLOB
#define FLYINGBLOB

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{

	struct FlyingBlob : public _Obstacle, public IBound
	{

		virtual ~FlyingBlob() { }

		static void InitializeStatics();

		struct FlyingBlobTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Body;

			Vector2 ObjectSize;

			boost::shared_ptr<TextureOrAnim> GooSprite;

		
			void InitializeInstanceFields();

		
			FlyingBlobTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		enum BlobColor
		{
			BlobColor_GREEN,
			BlobColor_PINK,
			BlobColor_BLUE,
			BlobColor_GREY,
			BlobColor_GOLD
		};
	
		enum PhsxType
		{
			PhsxType_PRESCRIBED,
			PhsxType_TO_TARGET
		};
	
		enum PrescribedMoveType
		{
			PrescribedMoveType_LINE,
			PrescribedMoveType_CIRCLE,
			PrescribedMoveType_STAR
		};

	
		static boost::shared_ptr<Particle> BlobGooTemplate;
		static boost::shared_ptr<EzSound> SquishSound;

	
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

	
		static std::vector<float> BobMaxSpeed;
		static float BobXAccel;
		static float BobXFriction;

	
		boost::shared_ptr<SimpleObject> MyObject;
		boost::shared_ptr<QuadClass> MyQuad;
		float MyAnimSpeed;

		/// <summary>
		/// Source from which to copy object vertex info
		/// </summary>
		boost::shared_ptr<FlyingBlob> CopySource;

		/// <summary>
		/// Whether to delete the blob permanently when it dies
		/// </summary>
		bool DeleteOnDeath;

		boost::shared_ptr<AABox> Box, Box2;

		float Life, StartLife;

		int Direction;

		bool NeverSkip;

	
        Vector2 KilledLocation;
        boost::shared_ptr<Bob> KillingBob, KillingBob2, KillingBob3;
        int KillBobTimeStamp;

	
		void SetColor( BlobColor color );

	
		static boost::shared_ptr<EzTexture> GetGooTexture( BlobColor color );

	
		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		FlyingBlob( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		void SetAnimation();

		FlyingBlob( const std::wstring &file, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad );

		void Death();

		void Squish( Vector2 vel );

		void XAccel( bool Left, bool Right, bool Run );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		Vector2 CalcPosition( float t );


	
		void UpdatePos();

	
		virtual void PhsxStep();

	
		virtual void ActivePhsxStep();

	
		virtual void PhsxStep2();

		void AnimStep();

		void UpdateObject();

	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	
		void MoveToBounded( Vector2 shift );

		virtual void Move( Vector2 shift );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

		void SetStandardTargetParams();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef FLYINGBLOB
