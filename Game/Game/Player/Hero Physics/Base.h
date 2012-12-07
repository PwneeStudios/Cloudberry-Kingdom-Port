#ifndef BASE
#define BASE

#include <global_header.h>

namespace CloudberryKingdom
{
	class HeroSpec
	{
	public:
		int basetype;
		int shape;
		int move;
		int special;

		HeroSpec();

		HeroSpec( int basetype, int shape, int move, int special );

		HeroSpec( int basetype, int shape, int move );

		HeroSpec operator + ( HeroSpec B );

		virtual std::wstring ToString();
	};

	class BobPhsx : public Object, public std::enable_shared_from_this<BobPhsx>
	{
	public:
		class DefaultInfo
		{
		public:
			static std::shared_ptr<EzSound> DoubleJump_Sound;
			static std::shared_ptr<EzSound> BobBoxJump_Sound;
			static std::shared_ptr<EzSound> BobJetpack_Sound;
			static int BobJetpack_SoundDelay;
		};

	public:
		enum CustomData
		{
			CustomData_GRAVITY,
			CustomData_ACCEL,
			CustomData_MAXSPEED,
			CustomData_MAXFALL,
			CustomData_JUMPLENGTH,
			CustomData_JUMPLENGTH2,
			CustomData_JUMPACCEL,
			CustomData_JUMPACCEL2,
			CustomData_JETPACKACCEL,
			CustomData_JETPACKFUEL,
			CustomData_NUMJUMPS,
			CustomData_SIZE,
			CustomData_SIZE2,
			CustomData_GRAVITY2,
			CustomData_PHASEPERIOD,
			CustomData_FRICTION
		};

	public:
		class CustomPhsxData
		{
		public:
			class DataBounds
			{
			public:
				float DefaultValue, MinValue, MaxValue;
				DataBounds() : DefaultValue( 0 ), MinValue( 0 ), MaxValue( 0 ) { }
				DataBounds( float DefaultValue, float MinValue, float MaxValue );
			};

		public:
			static void InitStatic();

		private:
			static std::vector<DataBounds> _Bounds;
		public:
			static DataBounds Bounds( CustomData type );
			static DataBounds Bounds( int i );

		private:
			static bool BoundsSet;
		public:
			static void InitBounds();

		private:
			std::vector<float> data;

		public:
			static int Length;

			void Init();

			void Init( std::vector<float> vals );

			virtual std::wstring ToString();

			void Init( const std::wstring &str );

			float &operator []( CustomData type );
		};

	public:
		enum RocketThrustType
		{
			RocketThrustType_NONE,
			RocketThrustType_SINGLE,
			RocketThrustType_DOUBLE
		};
#if defined(DEBUG)
	public:
		void ResetInfo();
#endif

	protected:
		const LevelGeometry &getGeometry() const;

	public:
		static std::shared_ptr<BobPhsx> GetPhsx_Base( int BaseType );

		static std::shared_ptr<BobPhsx> GetPhsx_Shape( int Shape );

		static std::shared_ptr<BobPhsx> GetPhsx_Move( int MoveMod );

		static std::shared_ptr<BobPhsx> GetPhsx_Special( int Special );

		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		static std::shared_ptr<BobPhsx> MakeCustom( HeroSpec spec );

		static std::shared_ptr<BobPhsx> MakeCustom( std::shared_ptr<BobPhsx> BaseType, const std::shared_ptr<BobPhsx> &Shape, std::shared_ptr<BobPhsx> MoveMod, std::shared_ptr<BobPhsx> Special );

		static std::shared_ptr<BobPhsx> MakeCustom( const std::wstring &BaseType, const std::wstring &Shape, const std::wstring &MoveMod, const std::wstring &Special );

		static std::shared_ptr<BobPhsx> MakeCustom( int BaseType, int Shape, int MoveMod );

		static std::shared_ptr<BobPhsx> MakeCustom( int BaseType, int Shape, int MoveMod, int Special );

		static std::shared_ptr<BobPhsx> MakeCustom( Hero_BaseType BaseType, Hero_Shape Shape, Hero_MoveMod MoveMod );

		static std::shared_ptr<BobPhsx> MakeCustom( Hero_BaseType BaseType, Hero_Shape Shape, Hero_MoveMod MoveMod, Hero_Special Special );

		/// <summary>
		/// If true this BobPhsx has custom physic's parameters, such as gravity, friction, etc.
		/// </summary>
		bool CustomPhsx;
		CustomPhsxData MyCustomPhsxData;

		void SetCustomPhsx( CustomPhsxData data );

		HeroSpec Specification;
		Localization::Words Name;
		int Id;

		std::wstring Adjective;
		std::wstring NameTemplate;
		std::shared_ptr<ObjectIcon> Icon;
	protected:
		float DefaultIconWidth;

	public:
		std::shared_ptr<Bob> Prototype;
		CapeType CapePrototype;
		Vector2 CapeOffset;
		Vector2 CapeOffset_Ducking;
		Vector2 CapeGravity;
		Vector2 ModCapeSize;
		float DollCamZoomMod;

		Vector2 HeroDollShift;

	private:
		bool SingletonInitialized;
	protected:
		virtual void InitSingleton();

	public:
		std::shared_ptr<Bob> MyBob;
		const std::shared_ptr<ObjectClass> &getObj() const;

		const std::shared_ptr<Camera> &getCam() const;

		const std::shared_ptr<Level> &getMyLevel() const;
		const std::shared_ptr<ObjectData> &getCore() const;

		const std::shared_ptr<RichLevelGenData> &getGenData() const;

		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );
		Vector2 getApparentVelocity() const;
		const Vector2 &getVel() const;
		void setVel( const Vector2 &value );
		const float &getxVel() const;
		void setxVel( const float &value );
		const float &getyVel() const;
		void setyVel( const float &value );
		const Vector2 &getAcc() const;
		void setAcc( const Vector2 &value );

		virtual void DefaultValues();

		float BlobMod;

		bool Ducking;
		int DuckingCount;

		/// <summary>
		/// If true, then the player must first land, then release the A button, and then press A again to jump.
		/// </summary>
		bool MustHitGroundToReadyJump;

		float MaxSpeed, XAccel;

		float Gravity;
		float ForceDown;

		float BobMaxFallSpeed;
		bool OnGround, PrevOnGround, Jumped;
		int AirTime;

		bool UseGroundSpeed;

		Vector2 JumpStartPos;
		bool ApexReached;

		bool DynamicLessThan( float val1, float val2 );

		bool DynamicGreaterThan( float val1, float val2 );

		virtual bool getSticky() const;

		bool OverrideSticky;
		float MaxJumpAccelMultiple, JumpAccelModifier;
		float JumpLengthModifier;
		void ResetJumpModifiers();

		/// <summary>
		/// Extra padding for when drawing the stickman to texture
		/// </summary>
		Vector2 SpritePadding;

		virtual void ToSprites( const std::map<int, std::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding );

		virtual void Release();

		BobPhsx();

		virtual std::shared_ptr<BobPhsx> Clone();

		virtual void KillJump();

		/// <summary>
		/// Called when an external force (such as a bouncy block) forces Bob toward a specific direction.
		/// </summary>
		virtual void Forced( Vector2 Dir );

		virtual void DampForcedJump();

	protected:
		int DisableJumpCount;
	public:
		virtual void DisableJump( int Length );

		Vector2 ModInitSize;
		bool DoubleJumpModel;
		bool JetpackModel;
		RocketThrustType ThrustType;
		virtual void Init( const std::shared_ptr<Bob> &bob );

	private:
		float GroundSpeed;
	public:
		virtual void Integrate();

//C# TO C++ CONVERTER NOTE: The variable Oscillate was renamed since it is named the same as a user-defined type:
		bool Oscillate_Renamed;
	protected:
		float ExplosionScale;
		float RunAnimSpeed;
	public:
		float ScaledFactor;

		float OscillateSize1, OscillateSize2, OscillatePeriod;
		float OscillateGravity1, OscillateGravity2;
	private:
		void OscillatePhsx();

	public:
		float ReverseDirectionBoost;

		// Ice parameters
		bool DoFastTakeOff;
		float ReverseDirectionBoostMod;
		float FricMod;
		float AccelMod;
		bool IceRun;

	private:
		void SetIceParams();


	public:
		Vector2 PrevVel, PrevPos;
		virtual void PhsxStep();

		int SameInputDirectionCount;
		virtual void PhsxStep2();

		void CopyPrev();

		/// <summary>
		/// True when the first phsx step hasn't finished yet.
		/// </summary>
		bool FirstPhsxStep;


		/// <summary>
		/// Additional checks that should be performed at the end of the GenerateInput function.
		/// Typically these are things that are uniform across all BobPhsx types.
		/// </summary>
	protected:
		void AdditionalGenerateInputChecks( int CurPhsxStep );

	public:
		virtual bool CheckFor_xFlip();

		std::shared_ptr<ObjectBase> ObjectLandedOn;
		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );
		virtual void HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit );

		virtual void GenerateInput( int CurPhsxStep );

		virtual void AnimStep();

	protected:
		void CheckForAnimDone();

	public:
		virtual void IncrementJumpCounter();

		int LastUsedStamp;
		virtual void SideHit( ColType side, const std::shared_ptr<BlockBase> &block );

		virtual void Die( BobDeathType DeathType );

		bool SkipInteraction( const std::shared_ptr<BlockBase> &block );

		virtual void BlockInteractions();

		virtual void BlockInteractions_Stage1();

		bool PlacedJump, NextJumpIsPlacedJump;

		virtual bool IsTopCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual bool IsBottomCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual void ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

		virtual void ModLadderPiece( const std::shared_ptr<PieceSeedData> &piece );

		virtual void OnInitBoxes();

		/// <summary>
		/// Do any initial actions needed for using this hero as a Doll.
		/// </summary>
		virtual void DollInitialize();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BASE
