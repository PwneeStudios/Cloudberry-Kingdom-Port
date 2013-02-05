#include <global_header.h>

#include "Hacks/List.h"
#include "Hacks/Queue.h"

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void FlyingBlob::InitializeStatics()
	{
		float tempVector[] = { 2, 0 };
		FlyingBlob::BobMaxSpeed = VecFromArray( tempVector );
		FlyingBlob::BobXAccel = .53f;
		FlyingBlob::BobXFriction = 1;
	}

	// Statics
	boost::shared_ptr<Particle> FlyingBlob::BlobGooTemplate;
	boost::shared_ptr<EzSound> FlyingBlob::SquishSound;
	std::vector<float> FlyingBlob::BobMaxSpeed;
	float FlyingBlob::BobXAccel;
	float FlyingBlob::BobXFriction;


	void FlyingBlob::FlyingBlobTileInfo::InitializeInstanceFields()
	{
		Body = boost::make_shared<SpriteInfo>( boost::shared_ptr<TextureOrAnim>(), Vector2(1.f), Vector2(), Color::White );
		ObjectSize = Vector2( 616.05f, 616.05f );
		GooSprite = 0;
	}

	void FlyingBlob::SetColor( BlobColor color )
	{
		MyColor = color;
		if ( getCore()->BoxesOnly || getMyLevel() == 0 )
			return;

		if ( MyObject->Quads.size() > 0 && MyObject->Quads.size() >= 2 )
		{
			switch ( MyColor )
			{
				case BlobColor_GREEN:
					MyObject->Quads[ 2 ].setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"Blob2_Body" ) ) );
					break;
				case BlobColor_PINK:
					MyObject->Quads[ 2 ].setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"Blob2_Body2" ) ) );
					break;
				case BlobColor_BLUE:
					MyObject->Quads[ 2 ].setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"Blob2_Body3" ) ) );
					break;
				case BlobColor_GREY:
					MyObject->Quads[ 2 ].setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"Blob2_Body4" ) ) );
					break;
				case BlobColor_GOLD:
					MyObject->Quads[ 2 ].setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"Blob2_Body5" ) ) );
					break;
			}
		}

		if ( getInfo()->Blobs->Body->Sprite != 0 )
		{
			if ( MyQuad == 0 )
				MyQuad = boost::make_shared<QuadClass>();
			MyQuad->Set( getInfo()->Blobs->Body );
		}
	}

	boost::shared_ptr<EzTexture> FlyingBlob::GetGooTexture( BlobColor color )
	{
		switch ( color )
		{
			case BlobColor_GREEN:
				return Tools::TextureWad->FindByName( std::wstring( L"BlobGoo" ) );
			case BlobColor_PINK:
				return Tools::TextureWad->FindByName( std::wstring( L"BlobGoo2" ) );
			case BlobColor_BLUE:
				return Tools::TextureWad->FindByName( std::wstring( L"BlobGoo3" ) );
			case BlobColor_GREY:
				return Tools::TextureWad->FindByName( std::wstring( L"BlobGoo4" ) );
			case BlobColor_GOLD:
				return Tools::TextureWad->FindByName( std::wstring( L"BlobGoo5" ) );
		}

		return 0;
	}

	void FlyingBlob::MakeNew()
	{
		_Obstacle::MakeNew();

		PhsxCutoff_Playing = Vector2( 400 );
		PhsxCutoff_BoxesOnly = Vector2( 0, 1000 );

		CopySource.reset();

		Target = TargetVel = Vector2();
		getCore()->Data = PhsxData();

		MyAnimSpeed = .1666f;

		MyPhsxType = PhsxType_PRESCRIBED;
		HasArrived = false;

		RemoveOnArrival = false;
		DeleteOnDeath = false;
		ArrivedRadius = 250;
		FinalizedParams = false;
		DistAccMod = 1;
		Damp = .96f;
		DampRange = 2;

		SetColor( BlobColor_GREEN );

		getCore()->DrawLayer = 4;
		getCore()->MyType = ObjectType_FLYING_BLOB;
		getCore()->Holdable = true;

		Displacement = Vector2();
		Offset = 0;
		Period = 1;


		getCore()->WakeUpRequirements = true;
		NeverSkip = false;

		StartLife = Life = 1;
		Direction = -1;

		GiveVelocity = false;

        KillingBob = KillingBob2 = KillingBob3 = 0;
        KillBobTimeStamp = 0;
	}

	void FlyingBlob::Init( Vector2 pos, const boost::shared_ptr<Level> &level )
	{
		_Obstacle::Init( pos, level );

		Vector2 size = level->getInfo()->Blobs->ObjectSize * level->getInfo()->ScaleAll * level->getInfo()->ScaleAllObjects;
		MyObject->Base.e1 = Vector2( size.X, 0 );
		MyObject->Base.e2 = Vector2( 0, size.Y );

		MyObject->Linear = true;

		MyObject->Boxes[ 0 ]->Animated = false;
		MyObject->Boxes[ 1 ]->Animated = false;

		Box->Initialize( getCore()->Data.Position, Prototypes::FlyingBlobObj->MyObject->Boxes[ 0 ]->Size() / 2 );
		Box2->Initialize( getCore()->Data.Position, Prototypes::FlyingBlobObj->MyObject->Boxes[ 1 ]->Size() / 2 );

		MyObject->Read( 0, 0 );
		MyObject->Update();

		Box->SetTarget( getCore()->Data.Position, Box->Current->Size );
		Box->SwapToCurrent();

		UpdateObject();

		Box2->SetTarget( MyObject->GetBoxCenter( 1 ), Box2->Current->Size );
		Box2->SwapToCurrent();
	}

	FlyingBlob::FlyingBlob( bool BoxesOnly ) :
		Period( 0 ),
		Offset( 0 ),
		HasArrived( false ),
		RemoveOnArrival( false ),
		ArrivedRadius( 0 ),
		MaxVel( 0 ),
		MaxAcc( 0 ),
		DistAccMod( 0 ),
		FinalizedParams( false ),
		Damp( 0 ),
		DampRange( 0 ),
		GiveVelocity( false ),
		MyMoveType( PrescribedMoveType_LINE ),
		MyPhsxType( PhsxType_PRESCRIBED ),
		MyColor( BlobColor_GREEN ),
		MyAnimSpeed( 0 ),
		DeleteOnDeath( false ),
		Life( 0 ),
		StartLife( 0 ),
		Direction( 0 ),
		NeverSkip( false )
	{
		InitializeInstanceFields();
		Construct( BoxesOnly );
	}

	void FlyingBlob::Construct( bool BoxesOnly )
	{
		MyObject = boost::make_shared<SimpleObject>( Prototypes::FlyingBlobObj->MyObject, BoxesOnly );

		Box = boost::make_shared<AABox>();
		Box2 = boost::make_shared<AABox>();

		SetAnimation();

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	void FlyingBlob::SetAnimation()
	{
		Clear( MyObject->AnimQueue );
		MyObject->Read( 0, 0 );
		MyObject->Play = true;
		MyObject->Loop = true;

		MyObject->EnqueueAnimation( 0, static_cast<float>( 0 ), true );
		MyObject->DequeueTransfers();
		MyObject->Update();
	}

	FlyingBlob::FlyingBlob( const std::wstring &file, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad ) :
		Period( 0 ),
		Offset( 0 ),
		HasArrived( false ),
		RemoveOnArrival( false ),
		ArrivedRadius( 0 ),
		MaxVel( 0 ),
		MaxAcc( 0 ),
		DistAccMod( 0 ),
		FinalizedParams( false ),
		Damp( 0 ),
		DampRange( 0 ),
		GiveVelocity( false ),
		MyMoveType( PrescribedMoveType_LINE ),
		MyPhsxType( PhsxType_PRESCRIBED ),
		MyColor( BlobColor_GREEN ),
		MyAnimSpeed( 0 ),
		DeleteOnDeath( false ),
		Life( 0 ),
		StartLife( 0 ),
		Direction( 0 ),
		NeverSkip( false )
	{
		InitializeInstanceFields();
		CoreData = boost::make_shared<ObjectData>();
		getCore()->Active = true;

		// Initialize statics
		SquishSound = Tools::SoundWad->FindByName( std::wstring( L"Blob_Squish" ) );

		BlobGooTemplate = boost::make_shared<Particle>();
		BlobGooTemplate->MyQuad.Init();
		BlobGooTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		BlobGooTemplate->MyQuad.setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"BlobGoo" ) ) );
		BlobGooTemplate->SetSize( 55 );
		BlobGooTemplate->SizeSpeed = Vector2( 4, 4 );
		BlobGooTemplate->AngleSpeed = .06f;
		BlobGooTemplate->Life = 37;
		BlobGooTemplate->MyColor = Vector4( 1.5f, 1.5f, 1.5f, 2 );
		BlobGooTemplate->ColorVel = Vector4( 0.01f, 0.01f, 0, -.072f );
		BlobGooTemplate->Data.Acceleration = Vector2( 0, -1.5f );

		boost::shared_ptr<ObjectClass> SourceObject;
		Tools::UseInvariantCulture();
		//boost::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		//boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( stream, Encoding::UTF8 );
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( file );

		SourceObject = boost::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), TextureWad->FindByName( std::wstring( L"White" ) ) );
		ObjectClass_PostConstruct( SourceObject, Tools::QDrawer, Tools::Device, Tools::Device->PP, 0, 0, EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), TextureWad->FindByName( std::wstring( L"White" ) ) );
		SourceObject->ReadFile( reader, EffectWad, TextureWad );
		
		//reader->Close();
		//stream->Close();
		reader->Close();

		SourceObject->ConvertForSimple();
		MyObject = boost::make_shared<SimpleObject>( SourceObject );
		MyObject->Base.e1 *= 555;
		MyObject->Base.e2 *= 555;

		MyObject->Read( 0, 0 );
		MyObject->Play = true;
		MyObject->EnqueueAnimation( 0, 0, true );
		MyObject->DequeueTransfers();
		MyObject->Update();


		getCore()->Data.Position = Vector2(100, 50);
		getCore()->Data.Velocity = Vector2(0, 0);

		Box = boost::make_shared<AABox>( getCore()->Data.Position, MyObject->Boxes[ 0 ]->Size() / 2 );
		Box2 = boost::make_shared<AABox>( getCore()->Data.Position, MyObject->Boxes[ 1 ]->Size() / 2 );

		StartLife = Life = 1;
		Direction = -1;
	}

	void FlyingBlob::Death()
	{
        // Don't die if we were just recently squished but still have life left.
        if ( getMyLevel()->PlayMode == 0 && !getMyLevel()->Watching && !getMyLevel()->Replay && Life > 0 && getMyLevel()->CurPhsxStep - KillBobTimeStamp < 40)
        {
            return;
        }

		getCore()->Active = false;
		if ( DeleteOnDeath )
			getCore()->getRecycle()->CollectObject( shared_from_this() );
		if ( getCore()->MyLevel->PlayMode != 0 )
			return;

		// Change player's kill stats
		if ( KillingBob != 0 && KillingBob->GiveStats() )
			KillingBob->getMyTempStats()->Blobs++;

		if ( Life < .1f )
			Squish( Vector2() );
	}

	void FlyingBlob::Squish( Vector2 vel )
	{
		boost::shared_ptr<CloudberryKingdom::ParticleEmitter> emitter = getCore()->MyLevel->MainEmitter;

		for ( int k = 0; k < 9; k++ )
		{
			boost::shared_ptr<CloudberryKingdom::Particle> p = emitter->GetNewParticle( BlobGooTemplate );
			if ( getInfo()->Blobs->GooSprite == 0 )
				p->MyQuad.setMyTexture( GetGooTexture( MyColor ) );
			else
				p->MyQuad.setMyTexture( getInfo()->Blobs->GooSprite->MyTexture );

			Vector2 Dir = getMyLevel()->getRnd()->RndDir();
			p->Data.Position = getCore()->Data.Position + 50 * Dir;
			p->Data.Velocity = 20 * static_cast<float>( getMyLevel()->getRnd()->Rnd->NextDouble() ) * Dir;

			p->Data.Velocity.Y = .5f * fabs( p->Data.Velocity.Y );
			p->Data.Velocity.Y += 6;
			p->Data.Velocity += vel;
			p->AngleSpeed *= 2 * static_cast<float>( getMyLevel()->getRnd()->Rnd->NextDouble() - .5f );
		}

		SquishSound->PlayModulated( .02f );
	}

	void FlyingBlob::XAccel( bool Left, bool Right, bool Run )
	{
		if ( Left && getCore()->Data.Velocity.X > -BobMaxSpeed[ static_cast<int>(MyMoveType) ] )
		{
			if ( getCore()->Data.Velocity.X <= 0 )
				getCore()->Data.Velocity.X -= BobXAccel;
			else
				getCore()->Data.Velocity.X -= 2.7f * BobXAccel;

			if ( getCore()->Data.Velocity.X < 0 && getCore()->Data.Velocity.X > -BobMaxSpeed[ static_cast<int>(MyMoveType) ] / 10 )
				getCore()->Data.Velocity.X = -BobMaxSpeed[ static_cast<int>(MyMoveType) ] / 10;
		}
		if ( Right && getCore()->Data.Velocity.X < BobMaxSpeed[ static_cast<int>(MyMoveType) ] )
		{
			if ( getCore()->Data.Velocity.X >= 0 )
				getCore()->Data.Velocity.X += BobXAccel;
			else
				getCore()->Data.Velocity.X += 2.7f * BobXAccel;

			if ( getCore()->Data.Velocity.X > 0 && getCore()->Data.Velocity.X < BobMaxSpeed[ static_cast<int>(MyMoveType) ] / 10 )
				getCore()->Data.Velocity.X = BobMaxSpeed[ static_cast<int>(MyMoveType) ] / 10;
		}

		if ( !( Left || Right ) || !Run && fabs( getCore()->Data.Velocity.X ) > BobMaxSpeed[ static_cast<int>(MyMoveType) ] )
		{
			if ( fabs( getCore()->Data.Velocity.X ) < 2 )
				getCore()->Data.Velocity.X /= 2;
			else
			{
				if ( fabs( getCore()->Data.Velocity.X ) > BobMaxSpeed[ static_cast<int>(MyMoveType) ] )
					getCore()->Data.Velocity.X -= ::Sign(getCore()->Data.Velocity.X) * BobXFriction;
				else
					getCore()->Data.Velocity.X -= ::Sign(getCore()->Data.Velocity.X) * 7.f / 4.f * BobXFriction;
			}
		}
	}

	Vector2 FlyingBlob::TR_Bound()
	{
		Vector2 max = Vector2::Max( Vector2::Max( CalcPosition( 0 ), CalcPosition( .5f ) ), Vector2::Max( CalcPosition( 0.25f ), CalcPosition( .75f ) ) );
		return max;
	}

	Vector2 FlyingBlob::BL_Bound()
	{
		Vector2 min = Vector2::Min( Vector2::Min( CalcPosition( 0 ), CalcPosition( .5f ) ), Vector2::Min( CalcPosition( 0.25f ), CalcPosition( .75f ) ) );

		return min;
	}

	Vector2 FlyingBlob::CalcPosition( float t )
	{
		switch ( MyMoveType )
		{
			case PrescribedMoveType_LINE:
				return getCore()->StartData.Position + Displacement * static_cast<float>(cos(2 * M_PI * t));

			case PrescribedMoveType_CIRCLE:
				return getCore()->StartData.Position + Vector2(Displacement.X * static_cast<float>(cos(2 * M_PI * t)), Displacement.Y * static_cast<float>(sin(2 * M_PI * t)));

			case PrescribedMoveType_STAR:
				return getCore()->StartData.Position + Vector2(Displacement.X * static_cast<float>(cos(2 * M_PI * t)) * (1 + static_cast<float>(cos(2 * M_PI * t))), Displacement.Y * static_cast<float>(sin(2 * M_PI * t)) * (1 + static_cast<float>(cos(2 * M_PI * t))));
		}

		return getCore()->StartData.Position;
	}

	void FlyingBlob::UpdatePos()
	{
		float Step = 0;

        if ( getMyLevel()->PlayMode == 0 && KillingBob != 0 && !getMyLevel()->Watching && !getMyLevel()->Replay )
        {
            getCore()->Data.Position = KilledLocation;
            return;
        }

		switch ( MyPhsxType )
		{
			case PhsxType_PRESCRIBED:
				Step = CoreMath::Modulo( getCore()->GetIndependentPhsxStep() + Offset, static_cast<float>(Period) );

				if ( !getCore()->Held )
					getCore()->Data.Position = CalcPosition(static_cast<float>(Step) / Period);

				break;

			case PhsxType_TO_TARGET:
				Target += TargetVel;
				TargetVel += getCore()->Data.Acceleration;

				Vector2 dif = Target - getCore()->Data.Position;
				float dist = dif.Length();

				if ( dist < ArrivedRadius )
					HasArrived = true;

				float acc = __min( MaxAcc,.0016f * dist * DistAccMod );

				if ( dist < DampRange )
					acc = 0;
				else
					getCore()->Data.Velocity *= Damp;
				if ( dist > 1 )
				{
					dif.Normalize();
					getCore()->Data.Velocity += acc * dif;
				}
				float vel = getCore()->Data.Velocity.Length();
				if ( vel > MaxVel )
					getCore()->Data.Velocity *= MaxVel / vel;

				getCore()->Data.Position += getCore()->Data.Velocity;

				break;
		}
	}

	void FlyingBlob::PhsxStep()
	{
		if ( !getCore()->Active )
			return;

		UpdatePos();

		if ( NeverSkip )
			ActivePhsxStep();
		else
			_Obstacle::PhsxStep();
	}

	void FlyingBlob::ActivePhsxStep()
	{
		if ( !getCore()->BoxesOnly )
			AnimStep();

		bool Right, Left;
		Right = Left = false;

		UpdateObject();

		Box->Current->Center = MyObject->Boxes[ 0 ]->Center();
		Box->Current->Size = MyObject->Boxes[ 0 ]->Size() / 2;
		Box->SetTarget( Box->Current->Center, Box->Current->Size + Vector2( .0f,.02f ) );

		Box2->Current->Center = MyObject->Boxes[ 0 ]->Center();
		Box2->Current->Size = MyObject->Boxes[ 0 ]->Size() / 2;
		Box2->Current->Size.X -= 40;

		Box2->SetTarget( Box2->Current->Center, Box2->Current->Size + Vector2( .0f,.02f ) );

		if ( getCore()->WakeUpRequirements )
		{
			Box->SwapToCurrent();
			Box2->SwapToCurrent();

			getCore()->WakeUpRequirements = false;
		}

		if ( Right )
			MyObject->xFlip = true;
		if ( Left )
			MyObject->xFlip = false;

		if ( HasArrived && RemoveOnArrival )
			CollectSelf();
	}

	void FlyingBlob::PhsxStep2()
	{
		if ( !getCore()->Active )
			return;
		if ( getCore()->SkippedPhsx )
			return;

		if ( Life < 1 )
			Death();

		Box->SwapToCurrent();
		Box2->SwapToCurrent();
	}

	void FlyingBlob::AnimStep()
	{
		MyObject->Linear = false;

		if ( !getCore()->Active )
			return;
		if ( getCore()->SkippedPhsx )
			return;

		if ( CopySource == 0 )
		if ( MyObject->DestinationAnim() == 0 && MyObject->Loop )
			MyObject->PlayUpdate( MyAnimSpeed * getCore()->getIndependentDeltaT() );
	}

	void FlyingBlob::UpdateObject()
	{
		if ( MyObject != 0 )
		{
			MyObject->Base.Origin = getCore()->Data.Position;

			if ( CopySource != 0 )
				MyObject->CopyUpdate( CopySource->MyObject );
			else
				MyObject->Update();
		}
	}

	void FlyingBlob::DrawGraphics()
	{
		if ( Life < 1 ) return;

		if ( !getCore()->Held )
		{
			if ( !getCore()->Active || getCore()->SkippedPhsx )
				return;

			Vector2 BL = Box->Current->BL - Vector2( 225, 225 );
			if ( BL.X > getCore()->MyLevel->getMainCamera()->TR.X || BL.Y > getCore()->MyLevel->getMainCamera()->TR.Y )
				return;
			Vector2 TR = Box->Current->TR + Vector2( 260, 225 );
			if ( TR.X < getCore()->MyLevel->getMainCamera()->BL.X || TR.Y < getCore()->MyLevel->getMainCamera()->BL.Y )
				return;
		}

		if ( MyQuad == 0 )
			MyObject->Draw( Tools::QDrawer, Tools::EffectWad );
		else
		{
			Vector2 shift = Vector2();

			// Hectic
			//double t = 2 * Math.PI * (Core.GetPhsxStep() + Offset) / 12;
			//Vector2 shift = new Vector2(0, (float)Math.Cos(t)) * 3.5f;

			// Not hectic
			if ( Displacement.Y == 0 )
			{
				double t = 2 * M_PI * ( getCore()->GetPhsxStep() + Offset ) / 120;
				shift = Vector2( 0, static_cast<float>( cos( t ) ) ) * 9.5f;
			}

			MyQuad->setPos( getPos() + shift );
			MyQuad->Draw();

			// Extra tweening draw
			//MyQuad.Quad.NextKeyFrame();
			//MyQuad.Alpha = MyQuad.Quad.t - (int)MyQuad.Quad.t;
			//MyQuad.Quad.Playing = false;
			//MyQuad.Draw();
			//MyQuad.Quad.Playing = true;
			//MyQuad.Alpha = 1;
		}
	}

	void FlyingBlob::DrawBoxes()
	{
		Box->Draw( Color::Azure, 10 );
		Box2->Draw( Color::Azure, 10 );
		//Box.DrawT(Color.Blue, 10);
		//Box2.DrawT(Color.Blue, 10);
	}

	void FlyingBlob::MoveToBounded( Vector2 shift )
	{
		Move( shift );
	}

	void FlyingBlob::Move( Vector2 shift )
	{
		_Obstacle::Move( shift );

		Target += shift;

		Box->Move( shift );
		Box2->Move( shift );

		MyObject->Base.Origin += shift;
		MyObject->Update();
	}

	void FlyingBlob::Interact( const boost::shared_ptr<Bob> &bob )
	{
		if ( !getCore()->Active )
			return;
		if ( Life <= 0 )
			return;

		bool UnderFoot, SideHit, Overlap;
		bool Delete = false; // Used for Stage 1 Level Generation
		if ( !getCore()->SkippedPhsx )
		{
			float VelY = Box->Target->TR.Y - Box->Current->TR.Y;

			UnderFoot = SideHit = false;
			ColType Col2 = Phsx::CollisionTest( bob->Box, Box );

			if ( Col2 == ColType_TOP )
				UnderFoot = true;
			else
			{
				ColType Col = Phsx::CollisionTest( bob->Box, Box2 );

				if ( Col == ColType_LEFT || Col == ColType_RIGHT )
				{
					SideHit = true;

					float GraceY = 82; // 76; // Extra grace space for jumping off of blob
					if ( getGame() != 0 && getGame()->ModdedBlobGrace )
						GraceY = getGame()->BlobGraceY;

					if ( bob->Box->Current->BL.Y > Box2->Current->BL.Y - GraceY || bob->Box->Target->BL.Y > Box2->Target->BL.Y - GraceY )
						UnderFoot = true;

					// If this is a computer and it might successfully jump off this blob, then
					if ( UnderFoot && getCore()->MyLevel->PlayMode == 2 )
					{
						// check to make sure we aren't just barely hitting the blob.
						// We want a solid hit.
						float ComputerGraceY = GraceY - getCore()->GenData.EdgeSafety;
						Delete = true;
						if ( bob->Box->Current->BL.Y > Box2->Current->BL.Y - ComputerGraceY || bob->Box->Target->BL.Y > Box2->Target->BL.Y - ComputerGraceY )
							Delete = false;
					}
				}
				else if ( Col == ColType_BOTTOM )
					SideHit = true;
			}

			if ( UnderFoot && !SideHit )
				if ( bob->getCore()->Data.Velocity.Y > 4 && bob->getCore()->Data.Velocity.Y > VelY )
					UnderFoot = false;

			if ( UnderFoot && SideHit )
				SideHit = false;
			if ( !UnderFoot && !SideHit )
				return;

			bool DoInteraction = true;

			if ( getCore()->MyLevel->PlayMode == 2 )
			{
				Overlap = Phsx::BoxBoxOverlap( bob->Box, Box );

				if ( UnderFoot && bob->WantsToLand == false )
					Delete = true;
				if ( UnderFoot && bob->BottomCol )
					Delete = true;
				if ( SideHit )
					Delete = true;
				if ( Overlap && Col2 == ColType_NO_COL )
					Delete = true;
				if ( getCore()->GenData.RemoveIfOverlap )
					Delete = true;
				if ( getCore()->GenData.Used )
					Delete = false;
				if ( Delete )
				{
					getCore()->getRecycle()->CollectObject( shared_from_this() );

					getCore()->Active = false;
					DoInteraction = false;
				}
				else
				{
					StampAsUsed( getCore()->MyLevel->CurPhsxStep );
				}
			}

			if ( DoInteraction && ( UnderFoot || SideHit ) )
			{
                if ( bob == KillingBob || bob == KillingBob2 || bob == KillingBob3 )
                    return;

				if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( getCore()->MyLevel->DefaultHeroType ) != 0 )
					UnderFoot = false;

				if ( UnderFoot )
				{
                    if ( getMyLevel()->PlayMode == 0 && !getMyLevel()->Watching && !getMyLevel()->Replay )
                    {
                        Life -= .25f;
                        KillBobTimeStamp = getMyLevel()->CurPhsxStep;
                        Squish( Vector2(0) );
                    }
                    else
                        Life--;

                    if ( KillingBob == 0 ) { KillingBob = bob; KilledLocation = getPos(); }
                    else if ( KillingBob2 == 0 ) KillingBob2 = bob;
                    else if ( KillingBob3 == 0 ) KillingBob3 = bob;

					if ( bob->GiveStats() )
						bob->getMyTempStats()->Score += 50;

					float NewY = Box->Target->TR.Y + bob->Box->Current->Size.Y + .01f;
					if ( NewY > bob->getCore()->Data.Position.Y && Col2 == ColType_TOP )
						bob->getCore()->Data.Position.Y = NewY;

					// If the player had a reasonable Y-velocity, override it
					if ( bob->getCore()->Data.Velocity.Y <= 30 )
					{
						bob->getCore()->Data.Velocity.Y = 9.5f * bob->MyPhsx->BlobMod;

						if ( GiveVelocity && VelY > 0 )
							bob->getCore()->Data.Velocity.Y += VelY * bob->MyPhsx->BlobMod;

						// The player landed on something
						bob->MyPhsx->LandOnSomething( true, shared_from_this() );
					}

					bob->MyPhsx->MaxJumpAccelMultiple = 1 + .8f * bob->MyPhsx->BlobMod;
				}
				else
                {
                    if ( Life >= 1 )
						bob->Die( BobDeathType_BLOB, shared_from_this() );
				}
			}
		}
	}

	void FlyingBlob::Reset( bool BoxesOnly )
	{
		_Obstacle::Reset( BoxesOnly );

		Life = StartLife;
		getCore()->WakeUpRequirements = true;

		MyObject->Read( 0, 0 );
		MyObject->Play = true;
		MyObject->Loop = true;
		Clear( MyObject->AnimQueue );
		MyObject->EnqueueAnimation( 0, static_cast<float>( getMyLevel()->getRnd()->Rnd->NextDouble() ) * 1.5f, true );
		MyObject->DequeueTransfers();
		MyObject->Update();
	}

	void FlyingBlob::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<FlyingBlob> GoombaA = boost::dynamic_pointer_cast<FlyingBlob>( A );
		Init( A->getCore()->StartData.Position, A->getMyLevel() );

		MyMoveType = GoombaA->MyMoveType;

		Target = GoombaA->Target;
		TargetVel = GoombaA->TargetVel;
		HasArrived = GoombaA->HasArrived;
		RemoveOnArrival = GoombaA->RemoveOnArrival;
		FinalizedParams = GoombaA->FinalizedParams;
		DistAccMod = GoombaA->DistAccMod;
		Damp = GoombaA->Damp;
		DampRange = GoombaA->DampRange;

		SetColor( GoombaA->MyColor );

		Period = GoombaA->Period;
		Offset = GoombaA->Offset;
		Displacement = GoombaA->Displacement;

		Direction = GoombaA->Direction;

		Life = GoombaA->Life;
		StartLife = GoombaA->StartLife;

		GiveVelocity = GoombaA->GiveVelocity;

		getCore()->WakeUpRequirements = true;
	}

	void FlyingBlob::SetStandardTargetParams()
	{
		MaxVel = 31;
		MaxAcc = 4.9f;

		MyPhsxType = FlyingBlob::PhsxType_TO_TARGET;
		getCore()->DrawLayer = 9;
	}

	void FlyingBlob::InitializeInstanceFields()
	{
		KillBobTimeStamp = 0;

		MaxVel = 16;
		MaxAcc = 2;
		DistAccMod = 1;
		FinalizedParams = false;
		Damp = .96f;
		DampRange = 2;
		NeverSkip = false;
	}
}
