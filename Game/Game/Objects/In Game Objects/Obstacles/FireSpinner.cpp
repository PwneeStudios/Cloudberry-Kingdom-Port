#include <global_header.h>

namespace CloudberryKingdom
{

	void FireSpinner::FireSpinnerTileInfo::InitializeInstanceFields()
	{
		Flame = boost::make_shared<SpriteInfo>( TextureOrAnim::Get( Tools::Texture( std::wstring( L"small flame" ) ) ), Vector2( 72.f, 72.f ), Vector2(), Color::White );
		Base = boost::make_shared<SpriteInfo>( boost::shared_ptr<TextureOrAnim>(), Vector2( 72.f, 72.f ), Vector2(), Color::White );
		SegmentSpacing = 53;
		SpaceFromBase = 0;
		Rotate = true;
		RotateStep = .22f *.82f;
		TopOffset = -80;
		BottomOffset = 80;
	}

	bool FireSpinner::RandomMiniOrientation = true;

	void FireSpinner::MakeNew()
	{
		_LineDeath::MakeNew();

		AutoGenSingleton = FireSpinner_AutoGen::getInstance();
		getCore()->MyType = ObjectType_FIRE_SPINNER;
		DeathType = BobDeathType_FIRE_SPINNER;
		getCore()->DrawLayer = 3;

		PhsxCutoff_Playing = Vector2( 1000, 1000 );
		PhsxCutoff_BoxesOnly = Vector2( -100, 400 );

		getCore()->GenData.NoBlockOverlap = true;
		getCore()->GenData.LimitGeneralDensity = true;

		getCore()->WakeUpRequirements = true;
	}

	void FireSpinner::Init( Vector2 pos, const boost::shared_ptr<Level> &level )
	{
		_LineDeath::Init( pos, level );

		if ( !getCore()->BoxesOnly )
		{
			MyQuad->Set( getInfo()->Spinners->Flame );
			MyQuad->Quad_Renamed.UseGlobalIllumination = false;

			MyBaseQuad->Set( getInfo()->Spinners->Base );
		}

		int CurPhsxStep = level->CurPhsxStep;
		Angle = 2 * static_cast<float>( M_PI ) * ( CurPhsxStep + Offset ) / static_cast<float>( Period );
		MiniAngle = CurPhsxStep *.22f;
		if ( RandomMiniOrientation )
			MiniAngle_Offset = getMyLevel()->getRnd()->RndFloat(0, 100);

		dir = Vector2( static_cast<float>( cos( Angle ) ), static_cast<float>( sin( Angle ) ) );
		MyLine.Target.p2 = dir * Radius + getCore()->Data.Position;
		MyLine.Target.p1 = getCore()->Data.Position;

		MyLine.Current = MyLine.Target;

		MyLine.SkipEdge = true;
	}

	FireSpinner::FireSpinner( bool BoxesOnly ) :
		Offset( 0 ),
		Period( 0 ),
		Radius( 0 ),
		Angle( 0 ),
		MiniAngle( 0 ),
		MiniAngle_Offset( 0 ),
		Orientation( 0 )
	{
		if ( !BoxesOnly )
		{
			MyQuad = boost::make_shared<QuadClass>();
			MyBaseQuad = boost::make_shared<QuadClass>();
		}

		Construct( BoxesOnly );
	}

	void FireSpinner::ActivePhsxStep()
	{
		if ( getCore()->WakeUpRequirements )
		{
			SetTarget( getCore()->GetIndependentPhsxStep() - 1 );
			getCore()->WakeUpRequirements = false;
		}

		MiniAngle = Orientation * ( getCore()->MyLevel->IndependentPhsxStep + MiniAngle_Offset ) * getInfo()->Spinners->RotateStep;
		SetTarget( getCore()->GetIndependentPhsxStep() );
	}

	void FireSpinner::SetCurrent( float Step )
	{
		Vector2 p1 = Vector2(), p2 = Vector2();
		GetLine( Step, p1, p2 );
		MyLine.SetCurrent( p1, p2 );
	}

	void FireSpinner::SetTarget( float Step )
	{
		Vector2 p1 = Vector2(), p2 = Vector2();
		GetLine( Step, p1, p2 );
		MyLine.SetTarget( p1, p2 );
	}

	void FireSpinner::GetLine( float Step, Vector2 &p1, Vector2 &p2 )
	{
		Angle = Orientation * 2 * static_cast<float>( M_PI ) * ( Step + Offset ) / static_cast<float>( Period );
		dir = Vector2( static_cast<float>( cos( Angle ) ), static_cast<float>( sin( Angle ) ) );

		p1 = getCore()->Data.Position;
		p2 = getCore()->Data.Position + dir * Radius;
	}

	void FireSpinner::DrawGraphics()
	{
		// Draw base
		if ( MyBaseQuad->Quad_Renamed._MyTexture != 0 )
		{
			MyBaseQuad->setPos( getPos() );
			MyBaseQuad->Draw();
		}

		// Draw flames
		float BallLength = getInfo()->Spinners->SegmentSpacing;
		Vector2 dif = MyLine.Current.p2 - MyLine.Current.p1;
		float CurRadius = dif.Length();
		dif /= CurRadius;
		int Balls = static_cast<int>( CurRadius / BallLength + .5f );
		BallLength = ( CurRadius - 10 ) / Balls;

		Vector2 minidir;
		if ( getInfo()->Spinners->Rotate )
			minidir = Vector2( static_cast<float>( cos( MiniAngle ) ), static_cast<float>( sin( MiniAngle ) ) );
		else
			minidir = Vector2( 1, 0 );
		MyQuad->PointxAxisTo( minidir );

		Vector2 start = MyLine.Current.p1 + dif * getInfo()->Spinners->SpaceFromBase;
		Vector2 end = MyLine.Current.p2;

		/*
		// Vanilla animation
		bool HoldPlaying = MyQuad.Quad.Playing;
		for (int i = 0; i < Balls; i++)
		{
		    float t = (float)i / (float)(Balls - 1);
		    MyQuad.Pos = (1 - t) * start + t * end;
	
		    if (HoldPlaying && i > 0)
		    {
		        MyQuad.Quad.Playing = false;
		        MyQuad.Quad.NextKeyFrame();
		    }
	
		    MyQuad.Draw();
		}
		MyQuad.Quad.Playing = HoldPlaying;
		 * */

		// Tweening animation
		bool HoldPlaying = MyQuad->Quad_Renamed.Playing;
		MyQuad->Quad_Renamed.Playing = false;
		for ( int i = 0; i < Balls; i++ )
		{
			float t = static_cast<float>( i ) / static_cast<float>( Balls - 1 );
			MyQuad->setPos( ( 1 - t ) * start + t * end );

			if ( HoldPlaying && i == 0 )
			{
				MyQuad->Quad_Renamed.UpdateTextureAnim();
			}

			MyQuad->setAlpha( 1 );
			MyQuad->Draw();

			if ( HoldPlaying && i > 0 )
			{
				MyQuad->Quad_Renamed.Playing = false;
				MyQuad->Quad_Renamed.NextKeyFrame();
			}

			MyQuad->setAlpha( MyQuad->Quad_Renamed.t - static_cast<int>( MyQuad->Quad_Renamed.t ) );
			MyQuad->Draw();
		}
		MyQuad->Quad_Renamed.Playing = HoldPlaying;
	}

	void FireSpinner::Move( Vector2 shift )
	{
		_LineDeath::Move( shift );
	}

	void FireSpinner::Interact( const boost::shared_ptr<Bob> &bob )
	{
		if ( !getCore()->SkippedPhsx )
		if ( Phsx::AABoxAndLineCollisionTest( bob->Box2, MyLine ) )
		{
			if ( getCore()->MyLevel->PlayMode == 0 )
			{
				bob->Die( BobDeathType_FIRE_SPINNER, shared_from_this() );
			}

			if ( getCore()->MyLevel->PlayMode == 1 )
			{
				bool col = Phsx::AABoxAndLineCollisionTest_Tiered( MyLine, getCore(), bob, FireSpinner_AutoGen::getInstance() );

				if ( col )
					getCore()->getRecycle()->CollectObject( shared_from_this() );
			}
		}
	}

	void FireSpinner::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());
		getCore()->WakeUpRequirements = true;

		boost::shared_ptr<FireSpinner> SpinnerA = boost::dynamic_pointer_cast<FireSpinner>( A );
		Init( SpinnerA->getPos(), SpinnerA->getMyLevel() );

		Radius = SpinnerA->Radius;

		Offset = SpinnerA->Offset;
		Period = SpinnerA->Period;
		Orientation = SpinnerA->Orientation;

		Angle = SpinnerA->Angle;

		MyLine.SkipEdge = SpinnerA->MyLine.SkipEdge;
	}
}
