#include <global_header.h>

#include "Hacks/String.h"
#include "Hacks/Parse.h"

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void BobPhsx::DefaultInfo::InitializeStatics()
	{
		BobPhsx::DefaultInfo::DoubleJump_Sound = Tools::NewSound( std::wstring( L"Jump5" ),.1f );
		BobPhsx::DefaultInfo::BobBoxJump_Sound = Tools::NewSound( std::wstring( L"BoxHero_Land" ), 1 );
		BobPhsx::DefaultInfo::BobJetpack_Sound = Tools::NewSound( std::wstring( L"Jetpack" ),.15f );
		BobPhsx::DefaultInfo::BobJetpack_SoundDelay = 5;
	}

	// Statics
	boost::shared_ptr<EzSound> BobPhsx::DefaultInfo::DoubleJump_Sound;
	boost::shared_ptr<EzSound> BobPhsx::DefaultInfo::BobBoxJump_Sound;
	boost::shared_ptr<EzSound> BobPhsx::DefaultInfo::BobJetpack_Sound;
	int BobPhsx::DefaultInfo::BobJetpack_SoundDelay;


	HeroSpec::HeroSpec()
	{
		basetype = 0;
		shape = 0;
		move = 0;
		special = 0;
	}

	HeroSpec::HeroSpec( int basetype, int shape, int move )
	{
		this->basetype = basetype;
		this->shape = shape;
		this->move = move;
		this->special = Hero_Special_CLASSIC;
	}

	HeroSpec::HeroSpec( int basetype, int shape, int move, int special )
	{
		this->basetype = basetype;
		this->shape = shape;
		this->move = move;
		this->special = special;
	}

	HeroSpec HeroSpec::operator + ( HeroSpec B )
	{
		return HeroSpec( B.basetype == Hero_BaseType_CLASSIC ? this->basetype : B.basetype, B.shape == Hero_Shape_CLASSIC ? this->shape : B.shape, B.move == Hero_MoveMod_CLASSIC ? this->move : B.move, B.special == Hero_Special_CLASSIC ? this->special : B.special );
	}

	std::wstring HeroSpec::ToString()
	{
		return Format( _T( "%d,%d,%d,%d" ), static_cast<int>( basetype ), static_cast<int>( shape ), static_cast<int>( move ), static_cast<int>( special ) );
	}

	BobPhsx::CustomPhsxData::DataBounds::DataBounds( float DefaultValue, float MinValue, float MaxValue )
	{
		this->DefaultValue = DefaultValue;
		this->MinValue = MinValue;
		this->MaxValue = MaxValue;
	}

	void BobPhsx::CustomPhsxData::InitStatic()
	{
		_Bounds = std::vector<DataBounds>( Length );
	}

	std::vector<BobPhsx::CustomPhsxData::DataBounds> BobPhsx::CustomPhsxData::_Bounds;

	CloudberryKingdom::BobPhsx::CustomPhsxData::DataBounds BobPhsx::CustomPhsxData::Bounds( CustomData type )
	{
		InitBounds();
		return _Bounds[ static_cast<int>( type ) ];
	}

	CloudberryKingdom::BobPhsx::CustomPhsxData::DataBounds BobPhsx::CustomPhsxData::Bounds( int i )
	{
		InitBounds();
		return _Bounds[ i ];
	}

	bool BobPhsx::CustomPhsxData::BoundsSet = false;

	void BobPhsx::CustomPhsxData::InitBounds()
	{
		if ( BoundsSet )
			return;
		BoundsSet = true;

		_Bounds[ static_cast<int>( CustomData_GRAVITY ) ] = DataBounds( 1,.5f, 2 );
		_Bounds[ static_cast<int>( CustomData_ACCEL ) ] = DataBounds( 1,.5f, 2 );
		_Bounds[ static_cast<int>( CustomData_MAXSPEED ) ] = DataBounds( 1,.5f, 2 );
		_Bounds[ static_cast<int>( CustomData_MAXFALL ) ] = DataBounds( 1,.33f, 3 );
		_Bounds[ static_cast<int>( CustomData_JUMPLENGTH ) ] = DataBounds( 1,.65f, 1.65f );
		_Bounds[ static_cast<int>( CustomData_JUMPLENGTH2 ) ] = DataBounds( 1,.5f, 1.65f );
		_Bounds[ static_cast<int>( CustomData_JUMPACCEL ) ] = DataBounds( 1,.5f, 1.65f );
		_Bounds[ static_cast<int>( CustomData_JUMPACCEL2 ) ] = DataBounds( 1,.5f, 1.65f );
		_Bounds[ static_cast<int>( CustomData_JETPACKACCEL ) ] = DataBounds( 1,.75f, 2 );
		_Bounds[ static_cast<int>( CustomData_JETPACKFUEL ) ] = DataBounds( 1,.5f, 4 );
		_Bounds[ static_cast<int>( CustomData_NUMJUMPS ) ] = DataBounds( 2, 1, 8 );
		_Bounds[ static_cast<int>( CustomData_SIZE ) ] = DataBounds( 1,.2f, 2.1f );
		_Bounds[ static_cast<int>( CustomData_SIZE2 ) ] = DataBounds( 2.08f,.2f, 2.1f );
		_Bounds[ static_cast<int>( CustomData_GRAVITY2 ) ] = DataBounds( 1,.5f, 2 );
		_Bounds[ static_cast<int>( CustomData_PHASEPERIOD ) ] = DataBounds( 1,.35f, 2 );
		_Bounds[ static_cast<int>( CustomData_FRICTION ) ] = DataBounds( 1, 0, 3 );
	}

	int BobPhsx::CustomPhsxData::Length = 16;

	void BobPhsx::CustomPhsxData::Init()
	{
		data = std::vector<float>( Length );

		for ( int i = 0; i < Length; i++ )
			data[ i ] = _Bounds[ i ].DefaultValue;
	}

	void BobPhsx::CustomPhsxData::Init( std::vector<float> vals )
	{
		data = std::vector<float>( Length );

		Tools::Assert( vals.size() == data.size() );

		this->operator[]( CustomData_GRAVITY ) = vals[0];
		this->operator[]( CustomData_ACCEL ) = vals[1];
		this->operator[]( CustomData_MAXSPEED ) = vals[2];
		this->operator[]( CustomData_MAXFALL ) = vals[3];
		this->operator[]( CustomData_JUMPLENGTH ) = vals[4];
		this->operator[]( CustomData_JUMPLENGTH2 ) = vals[5];
		this->operator[]( CustomData_JUMPACCEL ) = vals[6];
		this->operator[]( CustomData_JUMPACCEL ) = vals[7];
		this->operator[]( CustomData_JETPACKACCEL ) = vals[8];
		this->operator[]( CustomData_JETPACKFUEL ) = vals[9];
		this->operator[]( CustomData_NUMJUMPS ) = vals[10];
		this->operator[]( CustomData_SIZE ) = vals[11];
		this->operator[]( CustomData_SIZE2 ) = vals[12];
		this->operator[]( CustomData_GRAVITY2 ) = vals[13];
		this->operator[]( CustomData_PHASEPERIOD ) = vals[14];
		this->operator[]( CustomData_FRICTION ) = vals[15];
	}

	std::wstring BobPhsx::CustomPhsxData::ToString()
	{
		std::wstring str = std::wstring( L"ph:" );

		for ( size_t i = 0; i < data.size(); i++ )
		{
			str += ::ToString( data[ i ] );
			if ( i + 1 < data.size() )
				str += std::wstring( L"," );
		}
		str += std::wstring( L";" );

		return str;
	}

	void BobPhsx::CustomPhsxData::Init( const std::wstring &str )
	{
		// Break the data up by commas
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		std::vector<std::wstring> terms = Split( str, L',' );

		Init();

		// Try and load the data into the array.
		// FIXME: Make sure parse works.
		/*try
		{*/
			for ( int i = 0; i < static_cast<int>( terms.size() ); i++ )
			{
				float v = ParseFloat( terms[ i ] );
				data[ i ] = CoreMath::RestrictVal( Bounds( i ).MinValue, Bounds( i ).MaxValue, v );
			}
		/*}
		catch ( ... )
		{
			for ( int i = 0; i < static_cast<int>( data.size() ); i++ )
				data[ i ] = Bounds( i ).DefaultValue;
		}*/
	}

	float &BobPhsx::CustomPhsxData::operator []( CustomData type )
	{
		return data[ static_cast<int>( type ) ];
	}

//C# TO C++ CONVERTER TODO TASK: You cannot specify separate 'set' logic for indexers in native C++:
//	void BobPhsx::CustomPhsxData::setdefault(const CustomData &type, float value)
//	{
//		data[safe_cast<int>(type)] = value;
//	}

#if defined(DEBUG)
	void BobPhsx::ResetInfo()
	{
		InitSingleton();
	}
#endif

	const LevelGeometry &BobPhsx::getGeometry() const
	{
		return MyBob->getCore()->MyLevel->CurMakeData->PieceSeed->GeometryType;
	}

	boost::shared_ptr<BobPhsx> BobPhsx::GetPhsx_Base( int BaseType )
	{
		switch ( BaseType )
		{
			case Hero_BaseType_CLASSIC:
				return BobPhsxNormal::getInstance();
			case Hero_BaseType_BOX:
				return BobPhsxBox::getInstance();
			case Hero_BaseType_BOUNCY:
				return BobPhsxBouncy::getInstance();
			case Hero_BaseType_WHEEL:
				return BobPhsxWheel::getInstance();
			case Hero_BaseType_SPACESHIP:
				return BobPhsxSpaceship::getInstance();
			case Hero_BaseType_MEAT:
				return BobPhsxMeat::getInstance();
			case Hero_BaseType_ROCKET_BOX:
				return BobPhsxRocketbox::getInstance();
		}

		return 0;
	}

	boost::shared_ptr<BobPhsx> BobPhsx::GetPhsx_Shape( int Shape )
	{
		switch ( Shape )
		{
			case Hero_Shape_SMALL:
				return BobPhsxSmall::getInstance();
			case Hero_Shape_OSCILLATE:
				return BobPhsxScale::getInstance();
			case Hero_Shape_BIG:
				return BobPhsxBig::getInstance();
			case Hero_Shape_CLASSIC:
				return BobPhsxNormal::getInstance();
		}

		return 0;
	}

	boost::shared_ptr<BobPhsx> BobPhsx::GetPhsx_Move( int MoveMod )
	{
		switch ( MoveMod )
		{
			case Hero_MoveMod_DOUBLE:
				return BobPhsxDouble::getInstance();
			case Hero_MoveMod_JETPACK:
				return BobPhsxJetman::getInstance();
			case Hero_MoveMod_INVERT:
				return BobPhsxInvert::getInstance();
			case Hero_MoveMod_CLASSIC:
				return BobPhsxNormal::getInstance();
		}

		return 0;
	}

	boost::shared_ptr<BobPhsx> BobPhsx::GetPhsx_Special( int Special )
	{
		switch ( Special )
		{
			case Hero_Special_CLASSIC:
				return BobPhsxNormal::getInstance();
			case Hero_Special_TIME:
				return BobPhsxTime::getInstance();
		}

		return 0;
	}

	void BobPhsx::Set( const boost::shared_ptr<BobPhsx> &phsx )
	{
	}

	boost::shared_ptr<BobPhsx> BobPhsx::MakeCustom( HeroSpec spec )
	{
		return MakeCustom( spec.basetype, spec.shape, spec.move );
	}

	boost::shared_ptr<BobPhsx> BobPhsx::MakeCustom( boost::shared_ptr<BobPhsx> BaseType, const boost::shared_ptr<BobPhsx> &Shape, boost::shared_ptr<BobPhsx> MoveMod, boost::shared_ptr<BobPhsx> Special )
	{
		// Error catch. Spaceship can't be rocketman or double jump
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( BaseType ) != 0 )
			MoveMod = BobPhsxNormal::getInstance();

		// Error catch. Invert must be classic, and must be the base struct.
		if ( boost::dynamic_pointer_cast<BobPhsxInvert>( MoveMod ) != 0 )
		{
			BaseType = BobPhsxInvert::getInstance();
			MoveMod = BobPhsxNormal::getInstance();
		}

		// Error catch. Time Master must be classic, and must be the base struct.
		if ( boost::dynamic_pointer_cast<BobPhsxTime>( Special ) != 0 )
		{
			BaseType = BobPhsxTime::getInstance();
			Special = BobPhsxNormal::getInstance();
		}

		// Make the phsx
		boost::shared_ptr<BobPhsx> custom = BaseType->Clone();
		Shape->Set( custom );
		MoveMod->Set( custom );
		Special->Set( custom );

		// Set the name
		if ( BaseType == BobPhsxNormal::getInstance() && Shape == BobPhsxNormal::getInstance() && MoveMod == BobPhsxNormal::getInstance() )
			custom->Name = Localization::Words_CLASSIC_HERO;
		else
		{
			custom->Name = Localization::Words_CUSTOM;
			//string template = BaseType.Name;
			//string adjective = Shape.Adjective;
			//string adjective2 = MoveMod.Adjective;

			//if (adjective.Length > 0) adjective += " ";
			//if (adjective2.Length > 0) adjective2 += " ";

			//custom.Name = adjective + adjective2 + template;
			//custom.Name = custom.Name.Capitalize();
		}

		// Set the specificaiton for this hero.
		custom->Specification = BaseType->Specification + Shape->Specification + MoveMod->Specification;

		return custom;
	}

	boost::shared_ptr<BobPhsx> BobPhsx::MakeCustom( const std::wstring &BaseType, const std::wstring &Shape, const std::wstring &MoveMod, const std::wstring &Special )
	{
		int _BaseType, _Shape, _MoveMod, _Special;

		// FIXME: Make sure try/catch works as before.
		/*try
		{*/
			_BaseType = ParseInt( BaseType );
			_Shape = ParseInt( Shape );
			_MoveMod = ParseInt( MoveMod );
			_Special = ParseInt( Special );
		/*}
		catch ( ... )
		{
			_BaseType = _Shape = _MoveMod = _Special = 0;
		}*/

		_BaseType = CoreMath::RestrictVal( 0, Hero_BaseType_LENGTH - 1, _BaseType );
		_Shape = CoreMath::RestrictVal( 0, Hero_Shape_LENGTH - 1, _Shape );
		_MoveMod = CoreMath::RestrictVal( 0, Hero_MoveMod_LENGTH - 1, _MoveMod );
		_Special = CoreMath::RestrictVal( 0, Hero_Special_LENGTH - 1, _Special );

		//return MakeCustom(_BaseType, _Shape, _MoveMod);
		return MakeCustom( _BaseType, _Shape, _MoveMod, _Special );
	}

	boost::shared_ptr<BobPhsx> BobPhsx::MakeCustom( int BaseType, int Shape, int MoveMod )
	{
		return MakeCustom( static_cast<Hero_BaseType>( BaseType ), static_cast<Hero_Shape>( Shape ), static_cast<Hero_MoveMod>( MoveMod ) );
	}

	boost::shared_ptr<BobPhsx> BobPhsx::MakeCustom( int BaseType, int Shape, int MoveMod, int Special )
	{
		return MakeCustom( static_cast<Hero_BaseType>( BaseType ), static_cast<Hero_Shape>( Shape ), static_cast<Hero_MoveMod>( MoveMod ), static_cast<Hero_Special>( Special ) );
	}

	boost::shared_ptr<BobPhsx> BobPhsx::MakeCustom( Hero_BaseType BaseType, Hero_Shape Shape, Hero_MoveMod MoveMod )
	{
		return MakeCustom( GetPhsx_Base( BaseType ), GetPhsx_Shape( Shape ), GetPhsx_Move( MoveMod ), BobPhsxNormal::getInstance() );
	}

	boost::shared_ptr<BobPhsx> BobPhsx::MakeCustom( Hero_BaseType BaseType, Hero_Shape Shape, Hero_MoveMod MoveMod, Hero_Special Special )
	{
		return MakeCustom( GetPhsx_Base( BaseType ), GetPhsx_Shape( Shape ), GetPhsx_Move( MoveMod ), GetPhsx_Special( Special ) );
	}

	void BobPhsx::SetCustomPhsx( CustomPhsxData data )
	{
		CustomPhsx = true;
		MyCustomPhsxData = data;

		// Generic phsx
		Gravity *= data[ CustomData_GRAVITY ];
		XAccel *= data[ CustomData_ACCEL ];
		MaxSpeed *= data[ CustomData_MAXSPEED ];
		ModInitSize *= data[ CustomData_SIZE ];
		ModCapeSize *= data[ CustomData_SIZE ];

		// Wheelie phsx
		boost::shared_ptr<BobPhsxWheel> wheel = boost::dynamic_pointer_cast<BobPhsxWheel>( shared_from_this() );
		if ( 0 != wheel )
		{
			wheel->AngleAcc *= static_cast<float>( pow( data[ CustomData_ACCEL ], 1.5f ) );
			wheel->MaxAngleSpeed *= data[ CustomData_MAXSPEED ];
		}

		boost::shared_ptr<BobPhsxNormal> normal = boost::dynamic_pointer_cast<BobPhsxNormal>( shared_from_this() );
		if ( boost::dynamic_pointer_cast<BobPhsxNormal>( normal ) != 0 )
		{
			// Normal phsx
			BobMaxFallSpeed *= data[ CustomData_MAXFALL ];

			normal->BobJumpLength = static_cast<int>( normal->BobJumpLength * data[ CustomData_JUMPLENGTH ] );
			normal->BobJumpLength2 = static_cast<int>( normal->BobJumpLength2 * data[ CustomData_JUMPLENGTH2 ] );
			normal->SetAccels( static_cast<float>( normal->BobJumpLength ) );
			normal->BobJumpAccel *= data[ CustomData_JUMPACCEL ];
			normal->BobJumpAccel2 *= data[ CustomData_JUMPACCEL2 ];

			normal->XFriction *= data[ CustomData_FRICTION ];

			// Jetpack phsx
			if ( normal->JetPack )
			{
				normal->JetPackAccel *= data[ CustomData_JETPACKACCEL ];
				normal->JetPackLength = static_cast<int>( normal->JetPackLength * data[ CustomData_JETPACKFUEL ] );
			}

			// Double jump phsx
			if ( normal->NumJumps > 1 )
			{
				normal->NumJumps = static_cast<int>( data[ CustomData_NUMJUMPS ] );
			}
		}

		// Phase phsx
		if ( Oscillate_Renamed )
		{
			OscillateSize1 = data[ CustomData_SIZE ];
			OscillateSize2 = data[ CustomData_SIZE2 ];
			OscillateGravity1 *= data[ CustomData_GRAVITY ];
			OscillateGravity2 *= data[ CustomData_GRAVITY2 ];
			OscillatePeriod *= data[ CustomData_PHASEPERIOD ];
		}
	}

	void BobPhsx::InitSingleton()
	{
		SingletonInitialized = true;
	}

	const boost::shared_ptr<ObjectClass> &BobPhsx::getObj() const
	{
		return MyBob->PlayerObject;
	}

	const boost::shared_ptr<Camera> &BobPhsx::getCam() const
	{
		return MyBob->getCore()->MyLevel->getMainCamera();
	}

	const boost::shared_ptr<Level> &BobPhsx::getMyLevel() const
	{
		return MyBob->getCore()->MyLevel;
	}

	const boost::shared_ptr<ObjectData> &BobPhsx::getCore() const
	{
		return MyBob->getCore();
	}

	const boost::shared_ptr<RichLevelGenData> &BobPhsx::getGenData() const
	{
		return MyBob->getCore()->MyLevel->CurMakeData->GenData;
	}

	const Vector2 &BobPhsx::getPos() const
	{
		return MyBob->getCore()->Data.Position;
	}

	void BobPhsx::setPos( const Vector2 &value )
	{
		MyBob->getCore()->Data.Position = value;
	}

	Vector2 BobPhsx::getApparentVelocity() const
	{
		return getVel() + Vector2(GroundSpeed, 0);
	}

	const Vector2 &BobPhsx::getVel() const
	{
		return MyBob->getCore()->Data.Velocity;
	}

	void BobPhsx::setVel( const Vector2 &value )
	{
		MyBob->getCore()->Data.Velocity = value;
	}

	const float &BobPhsx::getxVel() const
	{
		return MyBob->getCore()->Data.Velocity.X;
	}

	void BobPhsx::setxVel( const float &value )
	{
		MyBob->getCore()->Data.Velocity.X = value;
	}

	const float &BobPhsx::getyVel() const
	{
		return MyBob->getCore()->Data.Velocity.Y;
	}

	void BobPhsx::setyVel( const float &value )
	{
		MyBob->getCore()->Data.Velocity.Y = value;
	}

	const Vector2 &BobPhsx::getAcc() const
	{
		return MyBob->getCore()->Data.Acceleration;
	}

	void BobPhsx::setAcc( const Vector2 &value )
	{
		MyBob->getCore()->Data.Acceleration = value;
	}

	void BobPhsx::DefaultValues()
	{
	}

	bool BobPhsx::DynamicLessThan( float val1, float val2 )
	{
		return Gravity > 0 ? ( val1 < val2 ) : ( val1 > -val2 );
	}

	bool BobPhsx::DynamicGreaterThan( float val1, float val2 )
	{
		return Gravity > 0 ? val1 > val2 : val1 < -val2;
	}

	bool BobPhsx::getSticky() const
	{
		return !OverrideSticky;
	}

	void BobPhsx::ResetJumpModifiers()
	{
		OverrideSticky = false;
		MaxJumpAccelMultiple = JumpAccelModifier = JumpLengthModifier = 1;
	}

	void BobPhsx::ToSprites( const std::map<int, boost::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding )
	{
	}

	void BobPhsx::Release()
	{
		MyBob.reset();
	}

	BobPhsx::BobPhsx()
	{
		InitializeInstanceFields();
		//if ( !SingletonInitialized )
		//	InitSingleton();
	}

	boost::shared_ptr<BobPhsx> BobPhsx::Clone()
	{
		// FIXME: Verify MemberwiseClone() behavior.
		boost::shared_ptr<BobPhsx> newBob = boost::make_shared<BobPhsx>();
			InitBobPhsxSingleton( newBob );
		CopyTo( newBob );
		return newBob;
	}

	void BobPhsx::CopyTo( const boost::shared_ptr<BobPhsx> &bob )
	{
		bob->CustomPhsx = CustomPhsx;
		bob->MyCustomPhsxData = MyCustomPhsxData;
		bob->Specification = Specification;
		bob->Name = Name;
		bob->Id = Id;
		bob->Adjective = Adjective;
		bob->NameTemplate = NameTemplate;
		bob->Icon = Icon;
		bob->DefaultIconWidth = DefaultIconWidth;
		bob->Prototype = Prototype;
		bob->CapePrototype = CapePrototype;
		bob->CapeOffset = CapeOffset;
		bob->CapeOffset_Ducking = CapeOffset_Ducking;
		bob->CapeGravity = CapeGravity;
		bob->ModCapeSize = ModCapeSize;
		bob->DollCamZoomMod = DollCamZoomMod;
		bob->HeroDollShift = HeroDollShift;
		bob->SingletonInitialized = SingletonInitialized;
		bob->MyBob = MyBob;
		bob->BlobMod = BlobMod;
		bob->Ducking = Ducking;
		bob->DuckingCount = DuckingCount;
		bob->MustHitGroundToReadyJump = MustHitGroundToReadyJump;
		bob->MaxSpeed = MaxSpeed;
		bob->XAccel = XAccel;
		bob->Gravity = Gravity;
		bob->ForceDown = ForceDown;
		bob->BobMaxFallSpeed = BobMaxFallSpeed;
		bob->OnGround = OnGround;
		bob->PrevOnGround = PrevOnGround;
		bob->Jumped = Jumped;
		bob->AirTime = AirTime;
		bob->UseGroundSpeed = UseGroundSpeed;
		bob->JumpStartPos = JumpStartPos;
		bob->ApexReached = ApexReached;
		bob->OverrideSticky = OverrideSticky;
		bob->MaxJumpAccelMultiple = MaxJumpAccelMultiple;
		bob->JumpAccelModifier = JumpAccelModifier;
		bob->JumpLengthModifier = JumpLengthModifier;
		bob->SpritePadding = SpritePadding;
		bob->DisableJumpCount = DisableJumpCount;
		bob->ModInitSize = ModInitSize;
		bob->DoubleJumpModel = DoubleJumpModel;
		bob->JetpackModel = JetpackModel;
		bob->ThrustType = ThrustType;
		bob->GroundSpeed = GroundSpeed;
		bob->Oscillate_Renamed = Oscillate_Renamed;
		bob->ExplosionScale = ExplosionScale;
		bob->RunAnimSpeed = RunAnimSpeed;
		bob->ScaledFactor = ScaledFactor;
		bob->OscillateSize1 = OscillateSize1;
		bob->OscillateSize2 = OscillateSize2;
		bob->OscillatePeriod = OscillatePeriod;
		bob->OscillateGravity1 = OscillateGravity1;
		bob->OscillateGravity2 = OscillateGravity2;
		bob->ReverseDirectionBoost = ReverseDirectionBoost;
		bob->DoFastTakeOff = DoFastTakeOff;
		bob->ReverseDirectionBoostMod = ReverseDirectionBoostMod;
		bob->FricMod = FricMod;
		bob->AccelMod = AccelMod;
		bob->IceRun = IceRun;
		bob->PrevVel = PrevVel;
		bob->PrevPos = PrevPos;
		bob->SameInputDirectionCount = SameInputDirectionCount;
		bob->FirstPhsxStep = FirstPhsxStep;
		bob->ObjectLandedOn = ObjectLandedOn;
		bob->LastUsedStamp = LastUsedStamp;
		bob->PlacedJump = PlacedJump;
		bob->NextJumpIsPlacedJump = NextJumpIsPlacedJump;
	}

	void BobPhsx::KillJump()
	{
	}

	void BobPhsx::Forced( Vector2 Dir )
	{
	}

	void BobPhsx::DampForcedJump()
	{
	}

	void BobPhsx::DisableJump( int Length )
	{
		DisableJumpCount = Length;
	}

	void BobPhsx::Init( const boost::shared_ptr<Bob> &bob )
	{
		MyBob = bob;

		if ( Prototype != 0 && MyBob->PlayerObject != 0 )
		{
			Vector2 size = Prototype->PlayerObject->ParentQuad->getSize();
			//Vector2 size = Prototypes.bob[BobPhsxNormal.Instance].PlayerObject.ParentQuad.Size;
			size *= ModInitSize;
			MyBob->PlayerObject->ParentQuad->setSize( size );

			if ( DoubleJumpModel )
				BobPhsxDouble::SetDoubleObject( MyBob->PlayerObject, shared_from_this() );
			if ( JetpackModel )
				BobPhsxJetman::SetJetmanObject( MyBob->PlayerObject );
		}
	}

	void BobPhsx::Integrate()
	{
		GroundSpeed *= .925f;

		if ( UseGroundSpeed && ( OnGround || PrevOnGround ) )
			GroundSpeed = MyBob->GroundSpeed;

		setPos( getPos() + getVel() + Vector2(GroundSpeed, 0) );
	}

	void BobPhsx::OscillatePhsx()
	{
		float t = static_cast<float>( MyBob->getCore()->GetPhsxStep() );
		float scale = CoreMath::Periodic( OscillateSize1, OscillateSize2, 30 * OscillatePeriod, t, 90 );
		ScaledFactor = scale;

		Vector2 size = Prototype->PlayerObject->ParentQuad->getSize() * Vector2(1.7f, 1.4f);
		size *= scale;
		MyBob->PlayerObject->ParentQuad->setSize( size );

		Gravity = CoreMath::Periodic( OscillateGravity1, OscillateGravity2, 30 * OscillatePeriod, t, 90 );
		RunAnimSpeed = 1 / ( ( scale - 1 ) *.16f + 1 );
		ExplosionScale = 1.4f * ( ( scale - 1 ) *.5f + 1 );

		boost::shared_ptr<Cape> cape = MyBob->MyCape;
		if ( cape != 0 )
		{
			cape->DoScaling = true;
			cape->ScaleCenter = cape->AnchorPoint[ 0 ];
			cape->Scale = Vector2( .975f * scale );
		}
	}

	void BobPhsx::SetIceParams()
	{
		if ( IceRun )
		{
			if ( OnGround )
			{
				AccelMod = .6f;
				FricMod = .085f;
				ReverseDirectionBoostMod = 0.3f;
				DoFastTakeOff = false;
			}
			else
			{
				AccelMod = .8325f;
				FricMod = .435f;
				ReverseDirectionBoostMod = 0.75f;
				DoFastTakeOff = true;
			}
		}
		else
		{
			AccelMod = 1;
			FricMod = 1;
			ReverseDirectionBoostMod = 1;
			DoFastTakeOff = true;
		}
	}

	void BobPhsx::PhsxStep()
	{
		SetIceParams();

		if ( OnGround )
			AirTime = 0;
		else
			AirTime++;

		if ( MyBob->CurInput.A_Button )
			MyBob->Count_ButtonA++;
		else
			MyBob->Count_ButtonA = 0;

		if ( Oscillate_Renamed )
			OscillatePhsx();
	}

	void BobPhsx::PhsxStep2()
	{
		if ( Sign( MyBob->PrevInput.xVec.X ) == Sign( MyBob->CurInput.xVec.X ) && Sign( MyBob->CurInput.xVec.X ) != 0 )
			SameInputDirectionCount++;
		else
			SameInputDirectionCount = 0;

		CheckFor_xFlip();

		PrevOnGround = OnGround;
	}

	void BobPhsx::CopyPrev()
	{
		PrevVel = getVel();
		PrevPos = getPos() + getVel();
	}

	void BobPhsx::AdditionalGenerateInputChecks( int CurPhsxStep )
	{
		// Pause at the beginning
		if ( CurPhsxStep < MyBob->ComputerWaitAtStartLength && MyBob->ComputerWaitAtStart )
		{
			MyBob->CurInput.xVec.X = 0;
			MyBob->CurInput.A_Button = false;
		}

		// Jump if the current block we're on says to jump
		if ( ObjectLandedOn != 0 && OnGround && ObjectLandedOn->getCore()->GenData.JumpNow )
			MyBob->CurInput.A_Button = true;

		// Copy another bob's input
		//if (MyBob.MyPieceIndex > 0 && MyBob.MoveData.Copy >= 0)
		if ( MyBob->MoveData.Copy >= 0 )
		{
			MyBob->CurInput = MyBob->getCore()->MyLevel->Bobs[ MyBob->MoveData.Copy ]->CurInput;
		}

		// Stay left of lowest bob
		//if (MyBob != MyLevel.LowestBob && MyLevel.LowestBob != null)
		//    if (MyBob.Pos.X > MyLevel.LowestBob.Pos.X - 30)
		//        CoreMath.Restrict(-1, 0, ref MyBob.CurInput.xVec.X);

		//if (MyBob != MyLevel.LowestBob && MyLevel.LowestBob != null)
		//    if (MyBob.Pos.X > MyLevel.LowestBob.Pos.X - 240)
		//        CoreMath.Restrict(-1, 0, ref MyBob.CurInput.xVec.X);

		FirstPhsxStep = false;
	}

	bool BobPhsx::CheckFor_xFlip()
	{
		bool HoldFlip = MyBob->PlayerObject->xFlip;
		if ( MyBob->CurInput.xVec.X > 0 )
			MyBob->PlayerObject->xFlip = false;
		if ( MyBob->CurInput.xVec.X < 0 )
			MyBob->PlayerObject->xFlip = true;

		if ( MyBob->MoveData.InvertDirX && MyBob->CurInput.xVec.X != 0 )
			MyBob->PlayerObject->xFlip = !MyBob->PlayerObject->xFlip;

		return HoldFlip != MyBob->PlayerObject->xFlip;
	}

	void BobPhsx::LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn )
	{
		ObjectLandedOn = ThingLandedOn;
	}

	void BobPhsx::HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit )
	{
	}

	void BobPhsx::GenerateInput( int CurPhsxStep )
	{
		MyBob->WantsToLand_Reluctant = getPos().Y < MyBob->TargetPosition.Y + 1200;

		if ( getPos().Y > getMyLevel()->getMainCamera()->TR.Y - 500 )
			MyBob->WantsToLand_Reluctant = false;

		if ( MyBob->WantsToLand )
			MyBob->WantsToLand_Reluctant = true;
	}

	void BobPhsx::AnimStep()
	{
		CheckForAnimDone();
	}

	void BobPhsx::CheckForAnimDone()
	{
		if ( getObj()->getDonePlaying() && MyBob->OnAnimFinish != 0 )
		{
			MyBob->OnAnimFinish->Apply();
			MyBob->OnAnimFinish.reset();
		}
	}

	void BobPhsx::IncrementJumpCounter()
	{
		if ( !MyBob->CompControl && !MyBob->getCore()->MyLevel->Watching && MyBob->getCore()->MyLevel->PlayMode == 0 )
		{
			MyBob->getMyStats()->Jumps++;

			// Check for Lots of Jumps awardment
			Awardments::CheckForAward_JumpAlot( MyBob );
		}
	}

	void BobPhsx::SideHit( ColType side, const boost::shared_ptr<BlockBase> &block )
	{
	}

	void BobPhsx::Die( BobDeathType DeathType )
	{
	}

	bool BobPhsx::SkipInteraction( const boost::shared_ptr<BlockBase> &block )
	{
		if ( block->getCore()->MarkedForDeletion || !block->getCore()->Active || !block->getIsActive() || !block->getCore()->Real )
			return true;
		if ( block->getBlockCore()->OnlyCollidesWithLowerLayers && block->getCore()->DrawLayer <= getCore()->DrawLayer )
			return true;
		return false;
	}

	void BobPhsx::BlockInteractions()
	{
		for ( BlockVec::const_iterator block = getMyLevel()->Blocks.begin(); block != getMyLevel()->Blocks.end(); ++block )
		{
			if ( SkipInteraction( *block ) )
				continue;

			ColType Col = Phsx::CollisionTest( MyBob->Box, ( *block )->getBox() );

			if ( Col != ColType_NO_COL )
				MyBob->InteractWithBlock( ( *block )->getBox(), *block, Col );
		}
	}

	void BobPhsx::BlockInteractions_Stage1()
	{
	}

	bool BobPhsx::IsTopCollision( ColType Col, const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block )
	{
		return Col != ColType_NO_COL && ( Col == ColType_TOP || Col != ColType_BOTTOM && __max( MyBob->Box->Current->BL.Y, MyBob->Box->Target->BL.Y ) > box->Target->TR.Y - __max( -1.35 * getCore()->Data.Velocity.Y, 7 ) );
	}

	bool BobPhsx::IsBottomCollision( ColType Col, const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block )
	{
		return Col == ColType_BOTTOM || Col != ColType_BOTTOM && getCore()->Data.Velocity.X != 0 && !OnGround && __min(MyBob->Box->Current->TR.Y, MyBob->Box->Target->TR.Y) < box->Target->BL.Y + __max(1.35 * getCore()->Data.Velocity.Y, 7);
	}

	void BobPhsx::ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style )
	{
	}

	void BobPhsx::ModLadderPiece( const boost::shared_ptr<PieceSeedData> &piece )
	{
	}

	void BobPhsx::OnInitBoxes()
	{
	}

	void BobPhsx::DollInitialize()
	{
	}

	void BobPhsx::InitializeInstanceFields()
	{
		DisableJumpCount = 0;
		CustomPhsx = false;
		Name = static_cast<Localization::Words>( 0 );
		Id = 0;
		DefaultIconWidth = 0;
		CapePrototype = static_cast<CapeType>( 0 );
		DollCamZoomMod = 0;
		BlobMod = 0;
		Ducking = false;
		DuckingCount = 0;
		MustHitGroundToReadyJump = false;
		MaxSpeed = XAccel = 0;
		Gravity = 0;
		ForceDown = 0;
		BobMaxFallSpeed = 0;
		OnGround = PrevOnGround = Jumped = false;
		AirTime = 0;
		UseGroundSpeed = false;
		Vector2 JumpStartPos;
		ApexReached = false;
		OverrideSticky = false;
		MaxJumpAccelMultiple = JumpAccelModifier = 0;
		JumpLengthModifier = 0;
		ReverseDirectionBoost = 0;
		DoFastTakeOff = false;
		ReverseDirectionBoostMod = 0;
		FricMod = 0;
		AccelMod = 0;
		IceRun = false;
		DoubleJumpModel = false;
		JetpackModel = false;
		ThrustType = static_cast<RocketThrustType>( 0 );
		GroundSpeed = 0;
		Oscillate_Renamed = false;
		ExplosionScale = 0;
		RunAnimSpeed = 0;
		ScaledFactor = 0;
		OscillateSize1 = OscillateSize2 = OscillatePeriod = 0;
		OscillateGravity1 = OscillateGravity2 = 0;
		SameInputDirectionCount = 0;
		FirstPhsxStep = false;
		LastUsedStamp = 0;
		PlacedJump = NextJumpIsPlacedJump = false;
		SingletonInitialized = false;







		CustomPhsx = false;
		Name = Localization::Words_NONE;
		Id = -1;
		Adjective = std::wstring( L"" );
		NameTemplate = std::wstring( L"Hero" );
		DefaultIconWidth = 150;
		CapeOffset = Vector2();
		CapeOffset_Ducking = Vector2( -20, 0 );
		CapeGravity = Vector2( 0, -1.45f ) / 1.45f;
		ModCapeSize = Vector2(1);
		DollCamZoomMod = 1;
		HeroDollShift = Vector2();
		SingletonInitialized = false;
		BlobMod = 1;
		DuckingCount = 0;
		MustHitGroundToReadyJump = false;
		ForceDown = -1.5f;
		BobMaxFallSpeed = -29;
		AirTime = 0;
		UseGroundSpeed = true;
		OverrideSticky = false;
		MaxJumpAccelMultiple = 1;
		JumpAccelModifier = 1;
		JumpLengthModifier = 1;
		SpritePadding = Vector2();
		ModInitSize = Vector2(1);
		DoubleJumpModel = false;
		JetpackModel = false;
		ThrustType = RocketThrustType_NONE;
		Oscillate_Renamed = false;
		ExplosionScale = 1.4f;
		RunAnimSpeed = 1;
		ScaledFactor = 1;
		OscillateSize1 = .32f;
		OscillateSize2 = 2.08f;
		OscillatePeriod = 2 * 3.14159f;
		OscillateGravity1 = 2.534208f;
		OscillateGravity2 = 2.91155f;
		ReverseDirectionBoost = 2.7f;
		DoFastTakeOff = true;
		ReverseDirectionBoostMod = 1;
		FricMod = 1;
		AccelMod = 1;
		IceRun = false;
		SameInputDirectionCount = 0;
		FirstPhsxStep = true;
		LastUsedStamp = 0;
		PlacedJump = false;
		NextJumpIsPlacedJump = false;
	}
}
