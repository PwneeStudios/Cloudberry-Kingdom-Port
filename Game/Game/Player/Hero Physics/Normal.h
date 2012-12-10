#ifndef NORMAL
#define NORMAL

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsxNormal : public BobPhsx
	{

	public:
		static void InitializeStatics();

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static std::shared_ptr<BobPhsxNormal> instance;
	public:
		const static std::shared_ptr<BobPhsxNormal> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxNormal> &bob );

		// Instancable class
	private:
		bool InitializedAnim;


	protected:
		std::shared_ptr<EzSound> LandSound;
	private:
		std::shared_ptr<EzSound> DoubleJump;
		std::shared_ptr<EzSound> ThrustSound;
		int ThrustSoundDelay;
		int ThrustSoundCount;

		int RndMoveType, Offset;
		int RndThrustType;

	public:
		virtual bool getSticky();

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
		const int &getJumpCount() const;
		void setJumpCount( const int &value );

		virtual void KillJump();

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

	private:
		int AutoMoveLength, AutoMoveType, AutoStrafeLength, AutoSetToJumpLength, AutoSetToJumpType;
		int AutoDirLength, AutoDir, AutoDirLength_SetTo;
		int AutoFallOrJumpLength, AutoFallOrJump;

	public:
		int NumJumps;
	protected:
		int CurJump;
	private:
		int JumpDelay;
		int JumpDelayCount;
		//static int ComputerJumpDelay = 55;

	public:
		bool JetPack;
		int JetPackLength;
		int JetPackCushion;

		/// <summary> The number of frames the jetpack has been activated, since last touchdown </summary>
	private:
		int JetPackCount;

		/// <summary> Y velocity must be less than this to jump </summary>
		float MaxVerticalSpeed_Jump;

		/// <summary> Y velocity must be less than this thrust with the jetpack </summary>
		float MaxVerticalSpeed_Thrust;

	protected:
		bool StartJumpAnim;



	public:
		BobPhsxNormal();

		BobPhsxNormal( int NumJumps, bool JetPack );

		void SetAccels();
		void SetAccels( float JumpLength );

		virtual void DefaultValues();

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual bool CheckFor_xFlip();

		virtual void DuckingPhsx();

		virtual void PhsxStep();

		Vector2 ThrustPos1;
		Vector2 ThrustDir1;
		Vector2 ThrustPos_Duck;
		Vector2 ThrustDir_Duck;
		Vector2 ThrustPos2;
		Vector2 ThrustDir2;

		virtual void PhsxStep2();


	protected:
		bool AutoAllowComputerToJumpOnLand;
	public:
		virtual void UpdateReadyToJump();

		bool getCanJump() const;

		bool getExternalPreventJump() const;

		virtual void Jump();

		/// <summary>
		/// For this many frames Bob will not stick to blocks
		/// (so that he can successfully jump off of fast upward moving blocks)
		/// </summary>
	private:
		int NoStickPeriod;
	protected:
		virtual void DoJump();

	public:
		virtual float GetXAccel();

		virtual void DoXAccel();

		virtual void DoYAccel();

		virtual void PlayLandSound();

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

		virtual void HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit );

		virtual float RetardxVec();


		// Survival variables
	private:
		std::shared_ptr<BlockBase> SafetyBlock;
		int JumpCountdown, TurnCountdown, Dir;

	public:
		void GenerateInput_Survival( int CurPhsxStep );

		float MinHeightAttained, MinGroundHeightAttained;
		void GenerateInput_Vertical( int CurPhsxStep );


		/// <summary> When true Bob aims to go as high as possible </summary>
	private:
		bool Up;

		void GenerateInput_Right( int CurPhsxStep );



void HighThrusts( int CurPhsxStep );
protected:
virtual void SetTarget( const std::shared_ptr<RichLevelGenData> &GenData );

		virtual void PreventEarlyLandings( const std::shared_ptr<RichLevelGenData> &GenData );


	public:
		virtual void GenerateInput( int CurPhsxStep );

		float ForcedJumpDamping;
		virtual void DampForcedJump();



		virtual void AnimStep();

	protected:
		void BezierAnimStep();

		virtual void SpriteAnimStep();

		/// <summary>
		/// Whether we should start playing the jump animation.
		/// </summary>
	public:
		virtual bool ShouldStartJumpAnim();

		virtual void SetDeathVel( BobDeathType DeathType );


	protected:
		void Explode();

	public:
		virtual void Die( BobDeathType DeathType );

		virtual void ToSprites( std::map<int, std::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding );

		virtual void DollInitialize();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef NORMAL
