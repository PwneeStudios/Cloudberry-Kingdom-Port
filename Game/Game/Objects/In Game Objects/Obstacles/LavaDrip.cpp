#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;


namespace CloudberryKingdom
{

	void LavaDrip::LavaDripTileInfo::InitializeInstanceFields()
	{
		Line_Renamed = std::make_shared<LineSpriteInfo>( _T( "Lava_Drip_1" ), _T( "Lava_Drip_2" ), _T( "Lava_Drip_3" ), 440 );
		BoxSize = Vector2( 118, 1300 );
	}

	void LavaDrip::MakeNew()
	{
		_BoxDeath::MakeNew();

		AutoGenSingleton = LavaDrip_AutoGen::getInstance();
		getCore()->MyType = ObjectType_LAVA_DRIP;
		DeathType = Bob::BobDeathType_LAVA_FLOW;
		getCore()->DrawLayer = 8;

		PhsxCutoff_Playing = Vector2( 200, 4000 );
		PhsxCutoff_BoxesOnly = Vector2( -150, 4000 );

		getCore()->GenData.NoBlockOverlap = false;
		getCore()->GenData.LimitGeneralDensity = false;

		getCore()->WakeUpRequirements = true;
	}

	void LavaDrip::Init( Vector2 pos, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<LavaDripTileInfo> info = level->getInfo()->LavaDrips;

		BoxSize.X = info->BoxSize.X * level->getInfo()->ScaleAll * level->getInfo()->ScaleAllObjects;

		Start = Vector2( pos.X, level->MyCamera->TR.Y + BoxSize.Y );
		End = Vector2( pos.X, level->MyCamera->BL.Y - BoxSize.Y );

		_BoxDeath::Init( pos, level );
	}

	LavaDrip::LavaDrip( bool BoxesOnly )
	{
		Construct( BoxesOnly );
	}

	void LavaDrip::SetPeriod( float speed )
	{
		DownT = static_cast<int>( 230 * ( BoxSize.Y + 1500 ) / ( 1300 + 1500 ) );
		PeakT = 65;
		WaitT = 340 - DownT - PeakT;

		DownT = static_cast<int>( DownT / speed );
		PeakT = static_cast<int>( PeakT / speed );
		WaitT = static_cast<int>( WaitT / speed );

		Period = DownT + PeakT + WaitT;
	}

	void LavaDrip::ActivePhsxStep()
	{
		_BoxDeath::ActivePhsxStep();
		AnimStep();
	}

	void LavaDrip::AnimStep()
	{
		AnimStep( getCore()->SkippedPhsx );
	}

	void LavaDrip::AnimStep( bool Skip )
	{
		if ( Skip )
			return;

		const float tempVector[] = { 0,.5f,.8f,.9f,.95f,.975f, 1 };
		std::vector<Vector2> KeyFrames_Peak = Tools::FloatArrayToVectorArray_y( std::vector<float>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) ) );
		const float tempVector2[] = { .065f, 1 };
		std::vector<Vector2> KeyFrames_Down = Tools::FloatArrayToVectorArray_y( std::vector<float>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) ) );

		Exposed = true;

		float t = static_cast<float>( CoreMath::Modulo( getCore()->GetIndependentPhsxStep() + Offset, DownT + WaitT + PeakT ) );

		float s = 0;
		if ( t < PeakT )
			s = CoreMath::FancyLerp( t / PeakT, KeyFrames_Peak ).Y * KeyFrames_Down[ 0 ]->Y;
		else if ( t < PeakT + DownT )
			s = CoreMath::FancyLerp( ( t - PeakT ) / static_cast<float>( DownT ), KeyFrames_Down ).Y;
		else
			s = 1;

		setPos( Vector2::Lerp( Start, End, s ) );
	}

	void LavaDrip::DrawGraphics()
	{
		Tools::QDrawer->DrawLine( Vector2( getPos().X, Box->Current->BL.Y ), Vector2(getPos().X, Box->Current->TR.Y), getInfo()->LavaDrips->Line_Renamed );
	}

	void LavaDrip::Move( Vector2 shift )
	{
		_BoxDeath::Move( shift );
	}

	void LavaDrip::Reset( bool BoxesOnly )
	{
		_BoxDeath::Reset( BoxesOnly );
	}

	void LavaDrip::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());
		std::shared_ptr<LavaDrip> LavaDripA = dynamic_cast<LavaDrip*>( A );

		BoxSize = LavaDripA->BoxSize;
		Init( A->getCore()->StartData.Position, A->getMyLevel() );

		Offset = LavaDripA->Offset;
		DownT = LavaDripA->DownT;
		PeakT = LavaDripA->PeakT;
		WaitT = LavaDripA->WaitT;
		Period = LavaDripA->Period;

		Exposed = LavaDripA->Exposed;

		getCore()->WakeUpRequirements = true;
	}
}
