#include <global_header.h>

namespace CloudberryKingdom
{

	void Laser::LaserTileInfo::InitializeInstanceFields()
	{
		Line_Renamed = boost::make_shared<LineSpriteInfo>( TextureOrAnim::Get( _T( "Laser" ) ), 100.f, 60.f, 1, Vector4( 1.f ) );
		Tint_Full = Vector4( 1.f, 1.f, 1.f, .95f );
		Tint_Half = Vector4( 1,.5f,.5f,.4f );
		Scale = 1;
	}

	void Laser::MakeNew()
	{
		_LineDeath::MakeNew();

		AutoGenSingleton = Laser_AutoGen::getInstance();
		getCore()->MyType = ObjectType_LASER;
		DeathType = BobDeathType_LASER;

		PhsxCutoff_Playing = Vector2( 500 );
		PhsxCutoff_BoxesOnly = Vector2( -100 );

		SmallerWidth = 170 / 200;

		AlwaysOn = false;
		AlwaysOff = false;
		StateChange = 0;

		getCore()->Init();
		getCore()->MyType = ObjectType_LASER;
		getCore()->DrawLayer = 9;
		getCore()->ContinuousEnabled = true;

		getCore()->WakeUpRequirements = true;
	}

	Laser::Laser( bool BoxesOnly )
	{
		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	void Laser::SetLine( Vector2 p, float degrees )
	{
		SetLine( p + CoreMath::DegreesToDir( degrees ) * 3800, p - CoreMath::DegreesToDir( degrees ) * 3800 );
	}

	void Laser::SetLine( Vector2 p1, Vector2 p2 )
	{
		this->p1 = p1;
		this->p2 = p2;

		getCore()->Data.Position = (p1 + p2) / 2;

		MyLine.Target.p2 = p2;
		MyLine.Target.p1 = p1;

		MyLine.Current = MyLine.Target;

		MyLine.SkipEdge = true;

		BL = BL_Bound();
		TR = TR_Bound();
	}

	Vector2 Laser::TR_Bound()
	{
		return Vector2::Max( p1, p2 );
	}

	Vector2 Laser::BL_Bound()
	{
		return Vector2::Min( p1, p2 );
	}

	void Laser::ActivePhsxStep()
	{
		if ( getCore()->WakeUpRequirements )
		{
			MyLine.SetCurrent( p1, p2 );
			getCore()->WakeUpRequirements = false;
		}

		if ( AlwaysOn )
		{
			MyState = LaserState_ON;
			float TargetState = CoreMath::PeriodicCentered( .86f, 1.f, 70.f, static_cast<float>( getCore()->MyLevel->CurPhsxStep ) );
			StateChange += .02f * ::Sign( TargetState - StateChange );
			if ( StateChange > 1 )
				StateChange = 1;
		}
		else if ( AlwaysOff )
		{
			MyState = LaserState_OFF;
			float TargetState = 0;
			StateChange += .02f * ::Sign( TargetState - StateChange );
			if ( StateChange < 0 )
				StateChange = 0;
		}
		else
		{
			//int Step = CoreMath.Modulo(Core.MyLevel.GetPhsxStep() + Offset, Period);
			float Step = CoreMath::Modulo( getCore()->MyLevel->GetIndependentPhsxStep() + Offset, static_cast<float>( Period ) );
			if ( Step < WarnDuration )
			{
				MyState = LaserState_WARN;
				StateChange = __min( 1, ( WarnDuration - Step ) / 7 );
			}
			else if ( Step < WarnDuration + Duration )
			{
				MyState = LaserState_ON;
				StateChange = __min( 1, ( WarnDuration + Duration - Step ) / 4 );
			}
			else
			{
				MyState = LaserState_OFF;
				StateChange = __min( 1, ( Period - Step ) / 3 );
			}
		}

		MyLine.SetTarget( p1, p2 );
	}

	void Laser::DrawGraphics()
	{
		boost::shared_ptr<CloudberryKingdom::Laser::LaserTileInfo> info = getInfo()->Lasers;
		float scale = info->Scale;
		Vector4 Full = info->Tint_Full;
		Vector4 Half = info->Tint_Half;

		if ( AlwaysOff )
		{
			Tools::QDrawer->DrawLine( MyLine.Target.p1, MyLine.Target.p2, info->Line_Renamed, ( 1 - StateChange ) * Vector4( 1, 1, 1, 0 ) + StateChange * Full, ( 1 - StateChange ) * 120 + StateChange * 200 * SmallerWidth );
		}
		else
		{
			if ( MyState == LaserState_WARN )
			{
				Tools::QDrawer->DrawLine( MyLine.Target.p1, MyLine.Target.p2, info->Line_Renamed, ( 1 - StateChange ) * Full + StateChange * Half, ( ( 1 - StateChange ) * 170 + StateChange * 60 ) * scale );
			}
			if ( MyState == LaserState_ON )
			{
				Tools::QDrawer->DrawLine( MyLine.Target.p1, MyLine.Target.p2, info->Line_Renamed, ( 1 - StateChange ) * Vector4( 1, 1, 1, 0 ) + StateChange * Full, ( ( 1 - StateChange ) * 200 + StateChange * 200 * SmallerWidth ) * scale, Tools::t * 3.5f );
			}
			if ( MyState == LaserState_OFF && StateChange < .95f )
			{
				Tools::QDrawer->DrawLine( MyLine.Target.p1, MyLine.Target.p2, info->Line_Renamed, ( 1 - StateChange ) * Half + StateChange * Vector4( 1, 1, 1, 0 ), ( ( 1 - StateChange ) * 60 + StateChange * 40 ) * scale );
			}
		}
	}

	void Laser::DrawBoxes()
	{
		Vector4 Full, Half;
		Full = Vector4( 1, 1, 1,.95f );
		Half = Vector4( 1,.5f,.5f,.4f );

		if ( AlwaysOff )
		{
			Tools::QDrawer->DrawLine( MyLine.Target.p1, MyLine.Target.p2, Color( ( 1 - StateChange ) * Vector4( 1, 1, 1, 0 ) + StateChange * Full ), 60 );
		}
		else
		{
			if ( MyState == LaserState_WARN )
			{
				Tools::QDrawer->DrawLine( MyLine.Target.p1, MyLine.Target.p2, Color( ( 1 - StateChange ) * Full + StateChange * Half ), 60 );
			}
			if ( MyState == LaserState_ON )
			{
				Tools::QDrawer->DrawLine( MyLine.Target.p1, MyLine.Target.p2, Color( ( 1 - StateChange ) * Vector4( 1, 1, 1, 0 ) + StateChange * Full ), 60 );
			}
			if ( MyState == LaserState_OFF && StateChange < .95f )
			{
				Tools::QDrawer->DrawLine( MyLine.Target.p1, MyLine.Target.p2, Color( ( 1 - StateChange ) * Half + StateChange * Vector4( 1, 1, 1, 0 ) ), 60 );
			}
		}
	}

	void Laser::MoveToBounded( Vector2 shift )
	{
		Move( shift );
	}

	void Laser::Move( Vector2 shift )
	{
		_LineDeath::Move( shift );

		MyLine.Current.p1 += shift;
		MyLine.Current.p2 += shift;
		MyLine.Target.p1 += shift;
		MyLine.Target.p2 += shift;

		p1 += shift;
		p2 += shift;
	}

	void Laser::Interact( const boost::shared_ptr<Bob> &bob )
	{
		if ( MyState == LaserState_ON && !getCore()->SkippedPhsx )
			_LineDeath::Interact( bob );
	}

	void Laser::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());
		getCore()->WakeUpRequirements = true;

		boost::shared_ptr<Laser> LaserA = boost::dynamic_pointer_cast<Laser>( A );
		Init( A->getPos(), A->getMyLevel() );

		SetLine( LaserA->p1, LaserA->p2 );

		AlwaysOn = LaserA->AlwaysOn;
		AlwaysOff = LaserA->AlwaysOff;
		SmallerWidth = LaserA->SmallerWidth;

		Offset = LaserA->Offset;
		Period = LaserA->Period;
		WarnDuration = LaserA->WarnDuration;
		Duration = LaserA->Duration;

		MyLine.SkipEdge = LaserA->MyLine.SkipEdge;
	}
}
