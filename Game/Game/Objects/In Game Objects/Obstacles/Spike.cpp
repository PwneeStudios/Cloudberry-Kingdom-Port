#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void Spike::InitializeStatics()
	{
		Spike::PeakOut = true;
	}

	// Statics
	bool Spike::PeakOut;


	void Spike::SpikeTileInfo::InitializeInstanceFields()
	{
		Spike_Renamed = boost::make_shared<SpriteInfo>( boost::shared_ptr<TextureOrAnim>() );
		Base = boost::make_shared<SpriteInfo>( boost::shared_ptr<TextureOrAnim>() );
		PeakHeight = .2f;
		TopOffset = 2;
		BottomOffset = 2;
		SideOffset = 2;
		ObjectSize = Vector2( 575, 535 );
	}

	void Spike::SetPeriod( int Period )
	{
		Period -= 7 + 7;

		float Total = 20 + 40;

		//UpT = (int)(7 * Period / Total);
		WaitT1 = static_cast<int>( 20 * Period / Total );
		//DownT = (int)(7 * Period / Total);
		WaitT2 = static_cast<int>( 40 * Period / Total );
	}

	void Spike::MakeNew()
	{
		MyObject->Linear = true;

		UpT = 7;
		WaitT1 = 20;
		DownT = 7;
		WaitT2 = 40;

		SetDir( Prototypes::SpikeObj->Dir );

		getCore()->Init();
		getCore()->MyType = ObjectType_SPIKE;
		getCore()->ContinuousEnabled = true;
		getCore()->DrawLayer = 2;

		getCore()->GenData.NoBlockOverlap = true;
		getCore()->GenData.LimitGeneralDensity = true;

		getCore()->WakeUpRequirements = true;
	}

	void Spike::Init( Vector2 Pos, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<SpikeTileInfo> info = level->getInfo()->Spikes;

		Vector2 size = info->ObjectSize * level->getInfo()->ScaleAll * level->getInfo()->ScaleAllObjects;
		MyObject->Base.e1 = Vector2( size.X, 0 );
		MyObject->Base.e2 = Vector2( 0, size.Y );

		Box->Initialize( getCore()->Data.Position, Prototypes::SpikeObj->MyObject->Boxes[ 0 ]->Size() / 2 );

		MyObject->Read( 0, 0 );
		MyObject->Update();
		UpdateObject();



		if ( !level->BoxesOnly )
		{
			//if (info.Base.Sprite == null)
			//    MyBaseQuad.Show = false;
			//else
			if ( info->Base->Sprite != 0 )
			{
				MyBaseQuad = boost::make_shared<QuadClass>();
				MyBaseQuad->Set( info->Base );
				MyObject->Quads[ 1 ].Hide = true;
			}

			//if (info.Spike.Sprite == null)
			//    MyQuad.Show = false;
			//else
			if ( info->Spike_Renamed->Sprite != 0 )
			{
				MyQuad = boost::make_shared<QuadClass>();
				MyQuad->Set( info->Spike_Renamed );
				SetHeight = MyQuad->getSize().Y;
				MyObject->Quads[ 1 ].Hide = true;
			}
		}

		Box->SetTarget( getCore()->Data.Position, Box->Current->Size );
		Box->SwapToCurrent();
	}

	Spike::Spike( bool BoxesOnly ) :
		Dir( 0 ),
		Angle( 0 ),
		Offset( 0 ),
		UpT( 0 ),
		DownT( 0 ),
		WaitT1( 0 ),
		WaitT2( 0 ),
		Exposed( false ),
		SetHeight( 0 )
	{
		Construct( BoxesOnly );
	}

	void Spike::Construct( bool BoxesOnly )
	{
		MyObject = boost::make_shared<SimpleObject>( Prototypes::SpikeObj->MyObject, BoxesOnly );

		 _BoxDeath::Construct( BoxesOnly );
	}

	void Spike::SetDir( int dir )
	{
		Dir = dir;
		SetAngle( Dir * static_cast<float>( M_PI ) / 2 );
	}

	void Spike::SetAngle( float Ang )
	{
		Angle = Ang;
		Vector2 Direction = Vector2( static_cast<float>( cos( Ang ) ), static_cast<float>( sin( Ang ) ) );
		CoreMath::PointxAxisTo( MyObject->Base.e1, MyObject->Base.e2, Direction );

		if ( MyQuad != 0 )
			MyQuad->PointxAxisTo( Direction );
		if ( MyBaseQuad != 0 )
		{
			MyBaseQuad->PointxAxisTo( Direction );
			unit = MyBaseQuad->Base.e2;
			unit.Normalize();
		}
	}

	Spike::Spike( const std::wstring &file, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad ) :
		Dir( 0 ),
		Angle( 0 ),
		Offset( 0 ),
		UpT( 0 ),
		DownT( 0 ),
		WaitT1( 0 ),
		WaitT2( 0 ),
		Exposed( false ),
		SetHeight( 0 )
	{
		boost::shared_ptr<ObjectClass> SourceObject;
		Tools::UseInvariantCulture();
		//boost::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		//boost::shared_ptr<BinaryReader> reader = boost::make_shared<BinaryReader>( stream, Encoding::UTF8 );
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<BinaryReader>( file );

		SourceObject = boost::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), TextureWad->FindByName( std::wstring( L"White" ) ) );
		ObjectClass_PostConstruct( SourceObject, Tools::QDrawer, Tools::Device, Tools::Device->PP, 0, 0, EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), TextureWad->FindByName( std::wstring( L"White" ) ) );
		SourceObject->ReadFile( reader, EffectWad, TextureWad );
		//reader->Close();
		//stream->Close();
		reader->Close();

		SourceObject->ConvertForSimple();
		MyObject = boost::make_shared<SimpleObject>( SourceObject );

		MyObject->Quads[ 1 ].Animated = false;

		MyObject->Read( 0, 1 );
		MyObject->Play = true;
		MyObject->EnqueueAnimation( 0, 0, true );
		MyObject->DequeueTransfers();
		MyObject->Update();


		getCore()->Data.Position = Vector2(0, 0);
		getCore()->Data.Velocity = Vector2(0, 0);

		Box = boost::make_shared<AABox>( getCore()->Data.Position, MyObject->Boxes[ 0 ]->Size() / 2 );
	}

	void Spike::PhsxStep()
	{
		getCore()->PosFromParentOffset();

		Vector2 PhsxCutoff = Vector2( 200, 200 );
		if ( getCore()->MyLevel->BoxesOnly )
			PhsxCutoff = Vector2( -150, 200 );
		if ( !getCore()->MyLevel->getMainCamera()->OnScreen(getCore()->Data.Position, PhsxCutoff) )
		{
			getCore()->SkippedPhsx = true;
			getCore()->WakeUpRequirements = true;
			return;
		}
		getCore()->SkippedPhsx = false;

		if ( getCore()->WakeUpRequirements )
		{
			UpdateObject();
		}

		AnimStep();
		UpdateObject();

		Box->Current->Center = MyObject->Boxes[ 0 ]->Center();
		Box->Current->Size = CoreMath::Abs( MyObject->Boxes[ 0 ]->Size() ) / 2;
		Box->SetTarget( Box->Current->Center, Box->Current->Size + Vector2( .0f,.02f ) );

		if ( getCore()->WakeUpRequirements )
		{
			Box->SwapToCurrent();
			getCore()->WakeUpRequirements = false;
		}
	}

	void Spike::PhsxStep2()
	{
		if ( getCore()->SkippedPhsx )
			return;

		Box->SetCurrent( Box->Current->Center, Box->Current->Size );
	}

	void Spike::AnimStep()
	{
		AnimStep( getCore()->SkippedPhsx );
	}

	void Spike::AnimStep( bool Skip )
	{
		if ( Skip )
			return;

		Exposed = true;

		float PeakHeight;
		if ( PeakOut )
			PeakHeight = getInfo()->Spikes->PeakHeight;
		else
			PeakHeight = .01f;

		float AnimSpeed = 0;

		float t = static_cast<float>( CoreMath::Modulo( getCore()->GetIndependentPhsxStep() + Offset, static_cast<float>( UpT + DownT + WaitT1 + WaitT2 ) ) );
		if ( t < UpT )
			MyObject->t = PeakHeight + ( 1 - PeakHeight ) * t / static_cast<float>( UpT );
		else if ( t < UpT + WaitT1 )
			MyObject->t = 1;
		else if ( t < UpT + WaitT1 + DownT )
			MyObject->t = 1 + .9f * ( t - UpT - WaitT1 ) / static_cast<float>( DownT );
		else
			MyObject->t = 1.9f + .1f * ( t - UpT - WaitT1 - DownT ) / static_cast<float>( WaitT2 );

		if ( !getCore()->BoxesOnly )
		{
			// Peak out before showing
			if ( PeakOut )
			{
				float PeakTime = 1.9655f;
				float MaxPeakTime = 1.98f;
				if ( MyObject->t > PeakTime )
				{
					MyObject->t = PeakHeight * __min( 1, ( MyObject->t - PeakTime ) / ( MaxPeakTime - PeakTime ) );
				}
			}
			// Shake before showing
			else
			{
				if ( MyObject->t > 1.9655f )
				{
					float HoldAngle = Angle;
					SetAngle( Angle + getMyLevel()->getRnd()->RndFloat(-.385f,.385f) );
					Angle = HoldAngle;
				}
				else
					SetAngle( Angle );
			}
		}

		if ( t < UpT / 3 )
			Exposed = false;
		if ( t > UpT + WaitT1 + .66f * DownT )
			Exposed = false;

		MyObject->PlayUpdate( AnimSpeed * 1000.f / 60.f / 150.f );

		float s = MyObject->t;
		if ( s > 1 )
			s = 2 - s;
		if ( MyQuad != 0 && MyQuad->Show )
			MyQuad->Base.e2 = unit * SetHeight * s;
	}

	void Spike::UpdateObject()
	{
		if ( MyObject != 0 )
		{
			MyObject->Base.Origin = getCore()->Data.Position;
			MyObject->Update();
		}
	}

	void Spike::DrawGraphics()
	{
		//if (MyBaseQuad.Quad._MyTexture != null)
		if ( MyBaseQuad != 0 )
		{
			MyQuad->setPos( getPos() );
			MyQuad->Draw();

			//MyBaseQuad.Quad.MyEffect = Tools.EffectWad.FindByName("Hsl");
			MyBaseQuad->setPos( getPos() );
			MyBaseQuad->Draw();
		}
		else
			MyObject->Draw( Tools::QDrawer, Tools::EffectWad );
	}

	void Spike::DrawBoxes()
	{
		Box->DrawFilled( Tools::QDrawer, Color::Blue );
	}

	void Spike::Move( Vector2 shift )
	{
		_BoxDeath::Move( shift );

		MyObject->Base.Origin += shift;
		MyObject->Update();
	}

	void Spike::Reset( bool BoxesOnly )
	{
		_BoxDeath::Reset( BoxesOnly );
	}

	void Spike::Interact( const boost::shared_ptr<Bob> &bob )
	{
		if ( !getCore()->SkippedPhsx && Exposed )
		{
			bool Col = Phsx::BoxBoxOverlap( bob->Box2, Box );
			if ( Col )
			{
				if ( getCore()->MyLevel->PlayMode == 0 )
					bob->Die( BobDeathType_SPIKE, shared_from_this() );

				if ( getCore()->MyLevel->PlayMode != 0 )
				{
					bool col = Phsx::BoxBoxOverlap_Tiered( Box, getCore(), bob, Spike_AutoGen::getInstance() );

					if ( col )
						getCore()->getRecycle()->CollectObject( shared_from_this() );
				}
			}
		}
	}

	void Spike::CloneBoxObject( const boost::shared_ptr<SimpleObject> &SimpleObjA, const boost::shared_ptr<SimpleObject> &SimpleObjB )
	{
		SimpleObjA->Base = SimpleObjB->Base;
		for ( int i = 0; i < static_cast<float>( SimpleObjA->Boxes.size() ); i++ )
		{
			SimpleObjA->Boxes[ i ]->TR = SimpleObjB->Boxes[ i ]->TR;
			SimpleObjA->Boxes[ i ]->BL = SimpleObjB->Boxes[ i ]->BL;
		}
	}

	void Spike::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<Spike> SpikeA = boost::dynamic_pointer_cast<Spike>( A );
		Init( A->getPos(), A->getMyLevel() );

		SetDir( SpikeA->Dir );

		Angle = SpikeA->Angle;
		Offset = SpikeA->Offset;
		UpT = SpikeA->UpT;
		DownT = SpikeA->DownT;
		WaitT1 = SpikeA->WaitT1;
		WaitT2 = SpikeA->WaitT2;

		getCore()->WakeUpRequirements = true;
		UpdateObject();

		Exposed = SpikeA->Exposed;
	}
}
