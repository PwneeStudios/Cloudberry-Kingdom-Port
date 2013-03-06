#ifndef BASE
#define BASE
#include <global_header.h>
namespace CloudberryKingdom
{
	struct HeroSpec
	{
	
		int basetype;
		int shape;
		int move;
		int special;
		HeroSpec();
		HeroSpec( int basetype, int shape, int move, int special );
		HeroSpec( int basetype, int shape, int move );
		HeroSpec operator + ( HeroSpec B );
		bool operator == ( const HeroSpec &B ) const
		{
			return basetype == B.basetype &&
				   shape == B.shape &&
				   move == B.move &&
				   special == B.special;
		}

		std::wstring ToString();

	};

	struct BobPhsx : public Object, public boost::enable_shared_from_this<BobPhsx>
	{

		virtual ~BobPhsx()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsx" );
#endif
		}


		struct DefaultInfo
		{
		
			static void InitializeStatics();
		
			static boost::shared_ptr<EzSound> DoubleJump_Sound;
			static boost::shared_ptr<EzSound> BobBoxJump_Sound;
			static boost::shared_ptr<EzSound> BobJetpack_Sound;
			static int BobJetpack_SoundDelay;
		};
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
		struct CustomPhsxData
		{
			
		
			struct DataBounds
			{
			
				float DefaultValue, MinValue, MaxValue;
				DataBounds() : DefaultValue( 0 ), MinValue( 0 ), MaxValue( 0 ) { }
				DataBounds( float DefaultValue, float MinValue, float MaxValue );
			};
		
			static void InitStatic();
		
			static std::vector<DataBounds> _Bounds;
		
			static DataBounds Bounds( CustomData type );
			static DataBounds Bounds( int i );
		
			static bool BoundsSet;
		
			static void InitBounds();
		
			std::vector<float> data;
		
			static int Length;
			void Init();
			void Init( std::vector<float> vals );
			std::wstring ToString();
			void Init( const std::wstring &str );
			float &operator []( CustomData type );
		};
		CustomPhsxData MyCustomPhsxData;
		enum RocketThrustType
		{
			RocketThrustType_NONE,
			RocketThrustType_SINGLE,
			RocketThrustType_DOUBLE
		};


		// Members
		int DisableJumpCount;
		bool CustomPhsx;
		HeroSpec Specification;
		Localization::Words Name;
		int Id;
		std::wstring Adjective;
		std::wstring NameTemplate;
		boost::shared_ptr<ObjectIcon> Icon;
	
		float DefaultIconWidth;
	
		boost::shared_ptr<Bob> Prototype;
		CapeType CapePrototype;
		Vector2 CapeOffset;
		Vector2 CapeOffset_Ducking;
		Vector2 CapeGravity;
		Vector2 ModCapeSize;
		float DollCamZoomMod;
		Vector2 HeroDollShift;
		boost::shared_ptr<Bob> MyBob;
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
		bool OverrideSticky;
		float MaxJumpAccelMultiple, JumpAccelModifier;
		float JumpLengthModifier;
		float ReverseDirectionBoost;
		// Ice parameters
		bool DoFastTakeOff;
		float ReverseDirectionBoostMod;
		float FricMod;
		float AccelMod;
		bool IceRun;

		/// <summary>
		/// Extra padding for when drawing the stickman to texture
		/// </summary>
		Vector2 SpritePadding;
		Vector2 ModInitSize;
		bool DoubleJumpModel;
		bool JetpackModel;
		RocketThrustType ThrustType;
		float GroundSpeed;
	

		bool Oscillate_Renamed;
	
		float ExplosionScale;
		float RunAnimSpeed;
	
		float ScaledFactor;
		float OscillateSize1, OscillateSize2, OscillatePeriod;
		float OscillateGravity1, OscillateGravity2;

		Vector2 PrevVel, PrevPos;
		int SameInputDirectionCount;
		/// <summary>
		/// True when the first phsx step hasn't finished yet.
		/// </summary>
		bool FirstPhsxStep;
		boost::shared_ptr<ObjectBase> ObjectLandedOn;
		int LastUsedStamp;
		bool PlacedJump, NextJumpIsPlacedJump;

	
		bool SingletonInitialized;

#if defined(DEBUG)
	
		void ResetInfo();
#endif
	
		const LevelGeometry &getGeometry() const;
	
		static boost::shared_ptr<BobPhsx> GetPhsx_Base( int BaseType );
		static boost::shared_ptr<BobPhsx> GetPhsx_Shape( int Shape );
		static boost::shared_ptr<BobPhsx> GetPhsx_Move( int MoveMod );
		static boost::shared_ptr<BobPhsx> GetPhsx_Special( int Special );
		virtual void Set( const boost::shared_ptr<BobPhsx> &phsx );
		static boost::shared_ptr<BobPhsx> MakeCustom( HeroSpec spec );
		static boost::shared_ptr<BobPhsx> MakeCustom( boost::shared_ptr<BobPhsx> BaseType, const boost::shared_ptr<BobPhsx> &Shape, boost::shared_ptr<BobPhsx> MoveMod, boost::shared_ptr<BobPhsx> Special );
		static boost::shared_ptr<BobPhsx> MakeCustom( const std::wstring &BaseType, const std::wstring &Shape, const std::wstring &MoveMod, const std::wstring &Special );
		static boost::shared_ptr<BobPhsx> MakeCustom( int BaseType, int Shape, int MoveMod );
		static boost::shared_ptr<BobPhsx> MakeCustom( int BaseType, int Shape, int MoveMod, int Special );
		static boost::shared_ptr<BobPhsx> MakeCustom( Hero_BaseType BaseType, Hero_Shape Shape, Hero_MoveMod MoveMod );
		static boost::shared_ptr<BobPhsx> MakeCustom( Hero_BaseType BaseType, Hero_Shape Shape, Hero_MoveMod MoveMod, Hero_Special Special );
		/// <summary>
		/// If true this BobPhsx has custom physic's parameters, such as gravity, friction, etc.
		/// </summary>
		void SetCustomPhsx( CustomPhsxData data );
		virtual void InitSingleton();
		const boost::shared_ptr<ObjectClass> &getObj() const;
		const boost::shared_ptr<Camera> &getCam() const;
		const boost::shared_ptr<Level> &getMyLevel() const;
		const boost::shared_ptr<ObjectData> &getCore() const;
		const boost::shared_ptr<RichLevelGenData> &getGenData() const;
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
		bool DynamicLessThan( float val1, float val2 );
		bool DynamicGreaterThan( float val1, float val2 );
		virtual bool getSticky() const;

		void ResetJumpModifiers();
		virtual void ToSprites( const std::map<int, boost::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding );
		virtual void Release();
		BobPhsx();
		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsx> &bob );
		virtual void KillJump();
		/// <summary>
		/// Called when an external force (such as a bouncy block) forces Bob toward a specific direction.
		/// </summary>
		virtual void Forced( Vector2 Dir );
		virtual void DampForcedJump();
		virtual void DisableJump( int Length );
		virtual void Init( const boost::shared_ptr<Bob> &bob );

		virtual void Integrate();

		void OscillatePhsx();
	
	
		void SetIceParams();

	
		
		virtual void PhsxStep();
		virtual void PhsxStep2();
		void CopyPrev();

		/// <summary>
		/// Additional checks that should be performed at the end of the GenerateInput function.
		/// Typically these are things that are uniform across all BobPhsx types.
		/// </summary>
	
		void AdditionalGenerateInputChecks( int CurPhsxStep );
	
		virtual bool CheckFor_xFlip();
		virtual void LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn );
		virtual void HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit );
		virtual void GenerateInput( int CurPhsxStep );
		virtual void AnimStep();
	
		void CheckForAnimDone();
	
		virtual void IncrementJumpCounter();
		virtual void SideHit( ColType side, const boost::shared_ptr<BlockBase> &block );
		virtual void Die( BobDeathType DeathType );
		bool SkipInteraction( const boost::shared_ptr<BlockBase> &block );
		virtual void BlockInteractions();
		virtual void BlockInteractions_Stage1();
		virtual bool IsTopCollision( ColType Col, const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block );
		virtual bool IsBottomCollision( ColType Col, const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block );
		virtual void ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style );
		virtual void ModLadderPiece( const boost::shared_ptr<PieceSeedData> &piece );
		virtual void OnInitBoxes();
		/// <summary>
		/// Do any initial actions needed for using this hero as a Doll.
		/// </summary>
		virtual void DollInitialize();
	
		void InitializeInstanceFields();
	};

}

#endif	//#ifndef BASE
