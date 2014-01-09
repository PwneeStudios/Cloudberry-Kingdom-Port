#ifndef FLYINGBLOB
#define FLYINGBLOB

#define _USE_MATH_DEFINES
#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/Effects/EzEffectWad.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Graphics/Draw/Simple/SimpleObject.h"
//#include "Core/Particle Effects/Particle.h"
//#include "Core/Sound/EzSound.h"
//#include "Core/Texture/EzTextureWad.h"
//#include "Core/Texture/EzTexture.h"
//#include "Core/Texture/TextureOrAnim.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/IBounded.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_Obstacle.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Prototypes.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct FlyingBlob : public _Obstacle, public IBound
	{

		virtual ~FlyingBlob()
		{
#ifdef BOOST_BIN
			OnDestructor( "FlyingBlob" );
#endif
		}


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
