#include <global_header.h>

#include "Door.h"

namespace CloudberryKingdom
{

	Door::ShakeLambda::ShakeLambda( const boost::shared_ptr<Door> &door, int Length, int Intensity, bool Sound )
	{
		Length_ = Length;
		Intensity_ = Intensity;
		Sound_ = Sound;
		Door_ = door;
	}

	void Door::ShakeLambda::Apply()
	{
		Door_->Shake( Length_, Intensity_, Sound_ );
	}

	void Door::DoorTileInfo::InitializeInstanceFields()
	{
		Sprite = boost::make_shared<SpriteInfo>( boost::shared_ptr<TextureOrAnim>( 0 ) );
		Show = true;
		SizePadding = Vector2();
		ShiftBottom = Vector2();
		ShiftStart = Vector2();
		CollisionSize = Vector2( 100, 200 );
		DoorOpen = Tools::NewSound( std::wstring( L"Door_Opening" ), 1 );
		DoorClose = Tools::NewSound( std::wstring( L"Door_Slamming" ), 1 );
		Sign_Renamed = boost::make_shared<SpriteInfo>( TextureOrAnim::Get( std::wstring( L"Sign_Off" ) ), Vector2( 275, -1 ) );
		ShowSign = false;
	}

	const boost::shared_ptr<LevelSeedData> &Door::getNextLevelSeedData() const
	{
		return _NextLevelSeedData;
	}

	void Door::setNextLevelSeedData( const boost::shared_ptr<LevelSeedData> &value )
	{
		_NextLevelSeedData = value;
	}

	void Door::Release()
	{
		ObjectBase::Release();

		InteractingBob.reset();
		MyBackblock.reset();

		_OnOpen.reset();
		_OnEnter.reset();
		ExtraPhsx.reset();
	}

	boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > Door::getOnOpen() const
	{
		return boost::static_pointer_cast<Lambda_1<boost::shared_ptr<Door> > >( _OnOpen );
	}

	void Door::setOnOpen( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > &value )
	{
		_OnOpen = value;
	}

	const boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > &Door::getOnEnter() const
	{
		return _OnEnter;
	}

	void Door::setOnEnter( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > &value )
	{
		_OnEnter = value;
	}

	void Door::MakeNew()
	{
		getCore()->Init();
		getCore()->MyType = ObjectType_DOOR;
		getCore()->DrawLayer = 1;
		getCore()->DrawLayer2 = 1;
		getCore()->DrawSubLayer = 1000;
		getCore()->FixSubLayer = true;
		getCore()->ResetOnlyOnReset = true;

		getCore()->EditHoldable = true;

		UsedOnce = false;

		MoveFeet = false;
		NoNote = false;

		Locked = false;

		MyBackblock.reset();
	}

	void Door::SetDoorType( const boost::shared_ptr<TileSet> &TileSetType, const boost::shared_ptr<Level> &level )
	{
		if ( level != 0 && level->CurMakeData != 0 && level->CurMakeData->PieceSeed != 0 )
			HitBoxPadding = level->getStyle()->DoorHitBoxPadding;

		getCore()->setMyTileSet(TileSetType);

		boost::shared_ptr<CloudberryKingdom::Door::DoorTileInfo> info = TileSetType->MyTileSetInfo->Doors;
		MyQuad->Quad_Renamed.Init();

		if ( Mirror )
		{
			info->Sprite->Offset.X *= -1;
			MyQuad->Set( info->Sprite );
			MyQuad->Quad_Renamed.MirrorUV_Horizontal();
			info->Sprite->Offset.X *= -1;
		}
		else
			MyQuad->Set( info->Sprite );

		ShiftStart = info->ShiftStart;
		ShiftBottom = info->ShiftBottom;
		DoorSize = info->CollisionSize;

		MyQuad->Quad_Renamed.Playing = false;

		SetObjectState();
	}

	Door::Door( bool BoxesOnly ) :
		SkipPhsx( false ),
		TemporaryBlock( false ),
		Locked( false ),
		Mirror( false ),
		SuppressSound( false ),
		ShakeStep( 0 ), ShakeIntensity( 0 ),
		step( 0 ),
		shake( false ),
		NearCount( 0 ),
		MoveFeet( false ),
		NoNote( false ),
		_DelayToShowNote_First( 0 ),
		_DelayToShowNote_Second( 0 ),
		_DelayToShowNote_Nth( 0 ),
		UsedOnce( false )
	{
		InitializeInstanceFields();
		getCore()->BoxesOnly = BoxesOnly;

		MyQuad = boost::make_shared<QuadClass>();

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	Vector2 Door::GetBottom()
	{
		MyQuad->Update();
		//return ShiftBottom + new Vector2(Pos.X, MyQuad.BL.Y + 11.5f);
		return getPos();
	}

	Vector2 Door::GetTop()
	{
		MyQuad->Update();
		//return new Vector2(Pos.X, MyQuad.TR.Y + 11.5f);
		return getPos() + Vector2(0, 400);
	}

	void Door::SetObjectState()
	{
		if ( MyQuad == 0 || MyQuad->Show == false )
			return;

		if ( Locked )
		{
			MyQuad->Quad_Renamed.CalcTexture( 0, 1 );
		}
		else
		{
			MyQuad->Quad_Renamed.CalcTexture( 0, 0 );
		}
	}

	void Door::HideBobs()
	{
		for ( BobVec::const_iterator bob = getCore()->MyLevel->Bobs.begin(); bob != getCore()->MyLevel->Bobs.end(); ++bob )
			( *bob )->getCore()->Show = false;
	}

	void Door::ShowBobs()
	{
		for ( BobVec::const_iterator bob = getCore()->MyLevel->Bobs.begin(); bob != getCore()->MyLevel->Bobs.end(); ++bob )
			( *bob )->getCore()->Show = true;
	}

	void Door::SetLock( bool Locked )
	{
		SetLock( Locked, false, false, true );
	}

	void Door::SetLock( bool Locked, bool AlwaysSet, bool PlaySound )
	{
		SetLock( Locked, AlwaysSet, PlaySound, true );
	}

	void Door::SetLock( bool Locked, bool AlwaysSet, bool PlaySound, bool Hide )
	{
		if ( this->Locked != Locked || AlwaysSet )
		{
			this->Locked = Locked;

			SetObjectState();

			if ( Locked )
			{
				// Hide the player closing the door
				if ( Hide && HideInteractingBobOnDoorClose && InteractingBob != 0 )
				{
					if ( ActivatingBob != 0 )
					{
						ActivatingBob->getCore()->Show = false;
						ActivatingBob->SetLightSourceToFade();
					}
					else
					{
						InteractingBob->getCore()->Show = false;
						InteractingBob->SetLightSourceToFade();
					}
				}

				if ( PlaySound && !SuppressSound )
					getInfo()->Doors->DoorClose->Play();
			}
			else
			{
				if ( PlaySound && !SuppressSound )
					getInfo()->Doors->DoorOpen->Play();
			}
		}
	}

	void Door::Update()
	{
		if ( getCore()->BoxesOnly )
			return;

		MyQuad->Base.Origin = getPos();
	}

	void Door::MakeNote()
	{
		if ( getCore()->BoxesOnly || getCore()->MyLevel == 0 )
			return;

		// Don't show a note for this door if it has been used before.
		if ( UsedOnce )
			return;

		if ( MyPressNote == 0 )
		{
			MyPressNote = MakeMagic( PressNote, ( boost::static_pointer_cast<Door>( shared_from_this() ) ) );
			getCore()->MyLevel->MyGame->AddGameObject(MyPressNote);
		}
		else
			MyPressNote->FadeIn();
	}

	void Door::KillNote()
	{
		if ( MyPressNote != 0 )
		{
			MyPressNote->CollectSelf();
			MyPressNote.reset();
		}
	}

	void Door::Shake( int Length, int Intensity, bool Sound )
	{
		ShakeStep = Length;
		ShakeIntensity = Intensity;
		save = getPos();

		if ( Sound )
			Tools::SoundWad->FindByName( std::wstring( L"Bash" ) )->Play( 1 );
	}

	void Door::DoShake()
	{
		if ( ShakeStep > 0 )
		{
			if ( step % 2 == 0 )
			{
				setPos( save );
				setPos( getPos() + Vector2(
					static_cast<float>( getMyLevel()->getRnd()->Rnd->Next( -ShakeIntensity, ShakeIntensity ) ),
					static_cast<float>( getMyLevel()->getRnd()->Rnd->Next( -ShakeIntensity, ShakeIntensity ) ) ) );
			}

			ShakeStep--;
			if ( ShakeStep == 0 )
				setPos( save );
		}
	}

	void Door::PhsxStep()
	{
		DoShake();

		if ( ExtraPhsx != 0 )
			ExtraPhsx->Apply( boost::static_pointer_cast<Door>( shared_from_this() ) );
	}

	bool Door::OnScreen()
	{
		if ( getCore()->BoxesOnly )
			return false;

		float Grace = 300;
		if ( getCore()->MyLevel->ModZoom.X < 0 )
			Grace += 500;

		if ( getPos().X > getCore()->MyLevel->getMainCamera()->TR.X + Grace + MyQuad->Base.e1.X || getPos().Y > getCore()->MyLevel->getMainCamera()->TR.Y + Grace + MyQuad->Base.e2.Y )
			return false;
		if ( getPos().X < getCore()->MyLevel->getMainCamera()->BL.X - Grace - MyQuad->Base.e1.X || getPos().Y < getCore()->MyLevel->getMainCamera()->BL.Y - 500 - MyQuad->Base.e2.Y )
			return false;

		return true;
	}

	void Door::Draw()
	{
		if ( !OnScreen() || !getCore()->Active )
			return;

		if ( Tools::DrawGraphics )
		{
			Update();

			if ( !getInfo()->Doors->Show )
				return;

			MyQuad->Draw();
		}

		if ( Tools::DrawBoxes )
		{
			Tools::QDrawer->DrawCircle( getPos(), 30, Color::Red );
		}
	}

	void Door::PlaceAt( Vector2 pos )
	{
		Move( pos + ShiftStart - getPos() );
		//Move(pos - GetBottom());
		//Move(pos - Pos);
	}

	void Door::Move( Vector2 shift )
	{
		setPos( getPos() + shift );
		Update();
	}

	void Door::Reset( bool BoxesOnly )
	{
		getCore()->Active = true;

		SetDoorType( getCore()->getMyTileSet(), 0 );

		MyPressNote.reset();
	}

	void Door::MoveBobs()
	{
		for ( BobVec::const_iterator bob = getCore()->MyLevel->Bobs.begin(); bob != getCore()->MyLevel->Bobs.end(); ++bob )
			MoveBobToHere( *bob );
	}

	void Door::MoveBobToHere( const boost::shared_ptr<Bob> &bob )
	{
		if ( MoveFeet )
		{
			bob->Move( ShiftStart + GetBottom() - bob->Feet() + Vector2(0, 1) );
		}
		else
			bob->Move( ShiftStart + getPos() - bob->getPos() );

		bob->getCore()->Data.Velocity = Vector2();
		TemporaryBlock = true;
	}

	void Door::ClearNote()
	{
		MyPressNote.reset();
		NearCount = 0;
	}

	const int Door::getDelayToShowNote() const
	{
		if ( NoNote )
			return 100000;

		if ( DoorOperated == 0 )
			return _DelayToShowNote_First;
		else if ( DoorOperated == 1 )
			return _DelayToShowNote_Second;
		else
			return _DelayToShowNote_Nth;
	}

	int Door::DoorOperated = 0;
	bool Door::AllowCompControl = false;

	void Door::Interact( const boost::shared_ptr<Bob> &bob )
	{
		if ( Locked || getOnOpen() == 0 || getMyLevel()->PlayMode != 0 )
			return;

		// Don't interact with code controlled Bobs
		if ( bob->CodeControl )
			return;

		InteractingBob = bob;

		float scale = bob->GetScale().X;

		float x_pad = DoorSize.X + HitBoxPadding.X + getInfo()->Doors->SizePadding.X + 22 + .018f * bob->Box->Current->Size.X + __max(0, 36 * (scale - 1));
		x_pad = CoreMath::RestrictVal( fabs( bob->getCore()->Data.Velocity.X * 1.3f ), 500.f, x_pad );
		float y_pad = DoorSize.Y + HitBoxPadding.Y + getInfo()->Doors->SizePadding.X + 50 + __max(0, 80 * (scale - 1));

		bool InteractedWith = false;
		if ( ( ( fabs( bob->getPos().X - getPos().X ) < x_pad && fabs(bob->getPos().Y - getPos().Y) < y_pad ) ) && (!bob->CompControl || AllowCompControl) && !getCore()->MyLevel->Watching && !getCore()->MyLevel->Replay )
		{
			NearCount++;
			//if (NearCount > 10 || MyPressNote != null) // For debugging purposes, always have the note show up.
			if ( NearCount > getDelayToShowNote() || MyPressNote != 0 )
				MakeNote();

	#if defined(WINDOWS)
			if ( ButtonCheck::State( ControllerButtons_X, static_cast<int>( bob->MyPlayerIndex ) ).Down || ( bob->CurInput.xVec.Y > .85f && bob->GetPlayerData()->KeyboardUsedLast ) || AutoOpen )
	#elif CAFE
			bool down = false || AutoOpen;
			if ( !down )
			{
				ButtonData bd_X = ButtonCheck::State( ControllerButtons_X, bob->MyPlayerIndex );
				if ( bd_X.Down && bd_X.Type == ControllerType_Standard ) down = true;
			}
			if ( !down )
			{
				ButtonData bd_B = ButtonCheck::State( ControllerButtons_B, bob->MyPlayerIndex );
				if ( bd_B.Down && bd_B.Type == ControllerType_Mini ) down = true;
			}

			if ( down )
	#else
			if ( ButtonCheck::State( ControllerButtons_X, bob->MyPlayerIndex ).Down || AutoOpen )
	#endif
			{
				InteractedWith = true;
				HaveBobUseDoor( bob );
			}
		}
		else
		{
			NearCount = CoreMath::RestrictVal( 0, 30, NearCount );
			NearCount--;
		}

		if ( !InteractedWith )
			TemporaryBlock = false;
	}

	void Door::Do()
	{
		getOnOpen()->Apply( boost::static_pointer_cast<Door>( shared_from_this() ) );
	}

	void Door::HaveBobUseDoor( const boost::shared_ptr<Bob> &bob )
	{
		ActivatingBob = bob;
		UsedOnce = true;

		if ( !TemporaryBlock )
		{
			Awardments::CheckForAward_Bungee( getMyLevel()->MyGame );

			getOnOpen()->Apply( boost::static_pointer_cast<Door>( shared_from_this() ) );
			DoorOperated++;
		}
	}

	void Door::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone( A->getCore() );

		boost::shared_ptr<Door> DoorA = boost::static_pointer_cast<Door>( A );

		DoorA->MyQuad->Clone( MyQuad );
		Locked = DoorA->Locked;
		SuppressSound = DoorA->SuppressSound;

		HitBoxPadding = DoorA->HitBoxPadding;
	}

	void Door::Write( const boost::shared_ptr<BinaryWriter> &writer )
	{
		getCore()->Write(writer);

		MyQuad->Write( writer );
	}

	void Door::Read( const boost::shared_ptr<BinaryReader> &reader )
	{
		getCore()->Read(reader);

		MyQuad->Read( reader );
	}

	void Door::InitializeInstanceFields()
	{
		ShiftStart = Vector2();
		ShiftBottom = Vector2();
		Mirror = false;
		HitBoxPadding = Vector2();
		SuppressSound = false;
		step = 0;
		MoveFeet = false;
		HideInteractingBobOnDoorClose = true;
		NearCount = 0;
		NoNote = false;
		_DelayToShowNote_First = 60;
		_DelayToShowNote_Second = 75;
		_DelayToShowNote_Nth = 180;
		UsedOnce = false;
		AutoOpen = false;
	}
}
