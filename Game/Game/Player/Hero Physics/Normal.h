#ifndef NORMAL
#define NORMAL

#include <small_header.h>

//#include "Core/Animation/SpriteAnim.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Game/Localization.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Core/Sound/EzSound.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob.h"
//#include "Game/Player/Cape.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct BobPhsxNormal : public BobPhsx
	{

		virtual ~BobPhsxNormal()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxNormal" );
#endif
		}


		// Members
		bool InitializedAnim;
		boost::shared_ptr<EzSound> LandSound;
	
		boost::shared_ptr<EzSound> DoubleJump;
		boost::shared_ptr<EzSound> ThrustSound;
		int ThrustSoundDelay;
		int ThrustSoundCount;

		int RndMoveType, Offset;
		int RndThrustType;

		int BobFallDelay;
		float XFriction, BobXDunkFriction;

		int BobJumpLength, BobJumpLengthDucking;
		float BobInitialJumpSpeed, BobInitialJumpSpeedDucking, BobJumpAccel2;

		int BobJumpLength2, BobJumpLengthDucking2;
		float BobInitialJumpSpeed2, BobInitialJumpSpeedDucking2, BobJumpAccel;

		int BobEdgeJump; // 1 if computer waits until edge before jumping, and never walks off, 0 otherwise
		int BobEdgeJumpLength; // Duration of BobEdgeJump

		float JetPackAccel;
		bool Thrusting, ReadyToThrust;

		bool StartedJump;
		int _JumpCount;

		int FallingCount;
		bool ReadyToJump;

		/// <summary>
		/// The Y coordinate of the last jump apex
		/// </summary>
		float ApexY;

		/// <summary>
		/// The number of frames since the last jump apex
		/// </summary>
		int CountSinceApex;

	
		int AutoMoveLength, AutoMoveType, AutoStrafeLength, AutoSetToJumpLength, AutoSetToJumpType;
		int AutoDirLength, AutoDir, AutoDirLength_SetTo;
		int AutoFallOrJumpLength, AutoFallOrJump;

	
		int NumJumps;
	
		int CurJump;
	
		int JumpDelay;
		int JumpDelayCount;
		//static int ComputerJumpDelay = 55;

	
		bool JetPack;
		int JetPackLength;
		int JetPackCushion;

		/// <summary> The number of frames the jetpack has been activated, since last touchdown </summary>
	
		int JetPackCount;

		/// <summary> Y velocity must be less than this to jump </summary>
		float MaxVerticalSpeed_Jump;

		/// <summary> Y velocity must be less than this thrust with the jetpack </summary>
		float MaxVerticalSpeed_Thrust;


		bool StartJumpAnim;

		Vector2 ThrustPos1;
		Vector2 ThrustDir1;
		Vector2 ThrustPos_Duck;
		Vector2 ThrustDir_Duck;
		Vector2 ThrustPos2;
		Vector2 ThrustDir2;

		bool AutoAllowComputerToJumpOnLand;

		int NoStickPeriod;

		boost::shared_ptr<BlockBase> SafetyBlock;
		int JumpCountdown, TurnCountdown, Dir;
	
		bool Up;

		float ForcedJumpDamping;

		float MinHeightAttained, MinGroundHeightAttained;
		



		// Static members
		static boost::shared_ptr<BobPhsxNormal> instance;		
		

		// Methods
	
		static void InitializeStatics();

		// Singleton
		virtual void InitSingleton();
	
		const static boost::shared_ptr<BobPhsxNormal> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxNormal> &bob );

		// Instancable struct

		virtual bool getSticky();

		const int &getJumpCount() const;
		void setJumpCount( const int &value );

		virtual void KillJump();
	
		BobPhsxNormal();

		BobPhsxNormal( int NumJumps, bool JetPack );

		void SetAccels();
		void SetAccels( float JumpLength );

		virtual void DefaultValues();

		virtual void Init( const boost::shared_ptr<Bob> &bob );

		virtual bool CheckFor_xFlip();

		virtual void DuckingPhsx();

		virtual void PhsxStep();

		virtual void PhsxStep2();
	

		virtual void UpdateReadyToJump();

		bool getCanJump() const;

		bool getExternalPreventJump() const;

		virtual void Jump();

		/// <summary>
		/// For this many frames Bob will not stick to blocks
		/// (so that he can successfully jump off of fast upward moving blocks)
		/// </summary>
	
		virtual void DoJump();

		virtual void PlayJumpSound();

		virtual float GetXAccel();

		virtual void DoXAccel();

		virtual void DoYAccel();

		virtual void PlayLandSound();

		virtual void LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit );

		virtual float RetardxVec();


		// Survival variables
		
		void GenerateInput_Survival( int CurPhsxStep );

		void GenerateInput_Vertical( int CurPhsxStep );


		/// <summary> When true Bob aims to go as high as possible </summary>

		void GenerateInput_Right( int CurPhsxStep );



void HighThrusts( int CurPhsxStep );

virtual void SetTarget( const boost::shared_ptr<RichLevelGenData> &GenData );

		virtual void PreventEarlyLandings( const boost::shared_ptr<RichLevelGenData> &GenData );


	
		virtual void GenerateInput( int CurPhsxStep );

		virtual void DampForcedJump();



		virtual void AnimStep();

	
		void BezierAnimStep();

		virtual void SpriteAnimStep();

		/// <summary>
		/// Whether we should start playing the jump animation.
		/// </summary>
	
		virtual bool ShouldStartJumpAnim();

		virtual void SetDeathVel( BobDeathType DeathType );


	
		void Explode();

	
		virtual void Die( BobDeathType DeathType );

		virtual void ToSprites( std::map<int, boost::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding );

		virtual void DollInitialize();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef NORMAL
