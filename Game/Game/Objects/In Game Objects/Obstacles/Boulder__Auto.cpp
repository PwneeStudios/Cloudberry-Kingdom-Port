#include <small_header.h>
#include "Game/Objects/In Game Objects/Obstacles/Boulder__Auto.h"

#include "Core/Tools/CoreMath.h"
#include "Core/Tools/Random.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Level/Make/Tools/Tunnel.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Obstacles/Boulder.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
#include "Game/Tools/Unset.h"

#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Tools/Camera.h"
#include "Game/Player/Hero Physics/Base.h"

namespace CloudberryKingdom
{

	void Boulder_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		Tunnel = boost::make_shared<TunnelFill>();
		HallwaySpacing = Vector2( 300 - 5 * u->Get( Upgrade_SPIKEY_GUY ), DifficultyHelper::Interp19( 220, 80, u->Get( Upgrade_SPIKEY_GUY ) ) );

		if ( PieceSeed->MyUpgrades1->Get( Upgrade_SPIKEY_GUY ) > 0 || PieceSeed->MyUpgrades2->Get( Upgrade_SPIKEY_GUY ) > 0 )
			DoStage2Fill = true;
		else
			DoStage2Fill = false;

		// General difficulty
		BobWidthLevel = Param( PieceSeed, u->Get( Upgrade_SPIKEY_GUY ) );

		FloaterMinDist = Param( PieceSeed, __max( 80, 800 - 63.5f * u->Get( Upgrade_SPIKEY_GUY ) ) );

		FloaterPeriod = Param( PieceSeed, __max( 84, 274 - 10 * u->Get( Upgrade_SPEED ) ) );

		FloaterPlaceDelay = Param( PieceSeed,.705f * __max( 4.75f, 9 - u->Get( Upgrade_SPIKEY_GUY ) / 2 ) );

		FloaterMaxAngle = Param( PieceSeed, __min( 750, 30 + 64 * u->Get( Upgrade_SPIKEY_GUY ) ) );

		float sparsity = __max( 10, 10 - 0 * u->Get( Upgrade_SPIKEY_GUY ) );
		if ( u->Get( Upgrade_SPIKEY_GUY ) <= 0 )
			sparsity = -1;

		FloaterSparsity = Param( PieceSeed, sparsity );
	}

	void Boulder_Parameters::InitializeInstanceFields()
	{
		Special.Hallway = false;
		HallwaySpacing = Unset::Vector;
	}

	Boulder_AutoGen::Cleanup_2Helper::Cleanup_2Helper( const boost::shared_ptr<Boulder_Parameters> &Params )
	{
		this->Params = Params;
	}

	Vector2 Boulder_AutoGen::Cleanup_2Helper::Apply( const Vector2 &pos )
	{
		float dist = Params->FloaterMinDist.GetVal( pos );
		return Vector2( dist, dist );
	}

	Boulder_AutoGen::BoulderFillLambda::BoulderFillLambda( const boost::shared_ptr<Level> &level, Vector2 TR, Vector2 BL, const boost::shared_ptr<Boulder_AutoGen> &autogen )
	{
		this->level = level;
		this->TR = TR;
		this->BL = BL;
		this->autogen = autogen;
	}

	void Boulder_AutoGen::BoulderFillLambda::Apply( const Vector2 &pos )
	{
		boost::shared_ptr<Boulder> floater = boost::static_pointer_cast<Boulder>( autogen->CreateAt( level, pos ) );
		Vector2 Padding = Vector2( 200, 375 );

		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
			Tools::EnsureBounds_X( floater, TR - Padding, BL + Padding );
		else
			Tools::EnsureBounds_Y( floater, TR - Padding, BL + Padding );
	}

boost::shared_ptr<Boulder_AutoGen> Boulder_AutoGen::instance = boost::make_shared<Boulder_AutoGen>();

	const boost::shared_ptr<Boulder_AutoGen> &Boulder_AutoGen::getInstance()
	{
		return instance;
	}

	Boulder_AutoGen::Boulder_AutoGen()
	{
		Do_ActiveFill_1 = true;
		Do_PreFill_2 = true;
		//Generators.AddGenerator(this);
	}

	boost::shared_ptr<AutoGen_Parameters> Boulder_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<Boulder_Parameters> Params = boost::make_shared<Boulder_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void Boulder_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );

		// Get Boulder parameters
		boost::shared_ptr<Boulder_Parameters> Params = boost::static_pointer_cast<Boulder_Parameters>( level->getStyle()->FindParams( Boulder_AutoGen::getInstance() ) );

		level->Cleanup( ObjectType_BOULDER, boost::make_shared<Cleanup_2Helper>( Params ), BL + Vector2( 400, 0 ), TR - Vector2( 500, 0 ) );

		if ( Params->Special.Hallway )
			Params->Tunnel->CleanupTunnel( level );
	}

	void Boulder_AutoGen::Hallway( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		boost::shared_ptr<Boulder_Parameters> Params = boost::static_pointer_cast<Boulder_Parameters>( level->getStyle()->FindParams( Boulder_AutoGen::getInstance() ) );

		TR.X += 700;

		Vector2 Spacing = Params->HallwaySpacing;
		float Width = TR.X - BL.X;
		int N = static_cast<int>( Width / Spacing.X );
		float Height = TR.Y - BL.Y;
		int M = static_cast<int>( Height / Spacing.Y );

		Params->Tunnel->Init( N, M );

		for ( int i = 0; i < N; i++ )
		for ( int j = 0; j < M; j++ )
		{
			Vector2 pos = Spacing * Vector2( static_cast<float>( i ), static_cast<float>( j ) ) + BL;

			boost::shared_ptr<Boulder> floater = boost::static_pointer_cast<Boulder>( CreateAt( level, pos ) );
			floater->Offset = 0;
			floater->getCore()->GenData.KeepIfUnused = true;
			floater->getCore()->GenData.EnforceBounds = false;

			Params->Tunnel->TunnelGUIDs[ i ][ j ] = floater->getCore()->MyGuid;
		}
	}

	boost::shared_ptr<ObjectBase> Boulder_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos )
	{
		// Get Floater parameters
		boost::shared_ptr<Boulder_Parameters> Params = boost::static_pointer_cast<Boulder_Parameters>( level->getStyle()->FindParams( Boulder_AutoGen::getInstance() ) );

		// Get the new floater
		boost::shared_ptr<Boulder> NewFloater = boost::static_pointer_cast<Boulder>( level->getRecycle()->GetObject(ObjectType_BOULDER, true) );
		NewFloater->Init( pos, level );

		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
			NewFloater->PivotPoint.Y = level->getMainCamera()->TR.Y + 160;
		else
		{
			NewFloater->PivotPoint.X = level->getMainCamera()->BL.X - 160;
			NewFloater->AddAngle = CoreMath::Radians( 90 );
			NewFloater->PivotLocationType = Boulder::PivotLocationTypes_LEFT_RIGHT;
		}

		NewFloater->Period = static_cast<int>( Params->FloaterPeriod.GetVal( pos ) );
		NewFloater->Offset = level->getRnd()->Rnd->Next(0, NewFloater->Period);
		NewFloater->MaxAngle = static_cast<float>( static_cast<int>( Params->FloaterMaxAngle.GetVal( pos ) ) );
		NewFloater->MaxAngle *= .001f;
		NewFloater->CalculateLength();


		// Discrete period offsets
		int NumOffsets = 8;
		int Period = static_cast<int>( Params->FloaterPeriod.GetVal( pos ) / NumOffsets ) * NumOffsets;
		NewFloater->Period = Period;
		NewFloater->Offset = level->getRnd()->Rnd->Next(0, NumOffsets) * Period / NumOffsets;

		NewFloater->getCore()->GenData.RemoveIfUnused = false;

		level->AddObject( NewFloater );

		return NewFloater;
	}

	Vector2 Boulder_AutoGen::CalcPos( const boost::shared_ptr<Bob> &bob, Vector2 BL, Vector2 TR, const boost::shared_ptr<Rand> &Rnd )
	{
		Vector2 pos = bob->getCore()->Data.Position + Vector2(Rnd->RndFloat(-600, 600), Rnd->RndFloat(-300, 400));
		pos.Y = __min( pos.Y, TR.Y - 400 );
		pos.Y = __max( pos.Y, BL.Y + 220 );
		return pos;
		pos.X = __max( BL.X + 380, __min( pos.X, TR.X - 350 ) );
		if ( ( bob->MyPhsx->OnGround || bob->getCore()->Data.Velocity.Y < 0 ) )
			pos.Y = bob->getCore()->Data.Position.Y + 200;
		pos.Y = __max( bob->getCore()->MyLevel->getMainCamera()->BL.Y + 270, __min(pos.Y, bob->getCore()->MyLevel->getMainCamera()->TR.Y - 550) );
		if ( fabs( bob->getCore()->Data.Position.Y - pos.Y ) < 100 )
			pos.X += .4f * ( pos.X - bob->getCore()->Data.Position.X );

		return pos;
	}

	void Boulder_AutoGen::ActiveFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::ActiveFill_1( level, BL, TR );

		// Get Floater parameters
		boost::shared_ptr<Boulder_Parameters> Params = boost::static_pointer_cast<Boulder_Parameters>( level->getStyle()->FindParams( Boulder_AutoGen::getInstance() ) );

		if ( !Params->DoStage2Fill )
			return;

		int Step = level->GetPhsxStep();

		for ( BobVec::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
		{
			if ( !level->getMainCamera()->OnScreen((*bob)->getCore()->Data.Position, Vector2(-200, -240)) )
				continue;

			Vector2 pos = ( *bob )->getCore()->Data.Position;
			int Delay = static_cast<int>( Params->FloaterPlaceDelay.GetVal( pos ) );
			if ( Step > 90 && Step % Delay == 0 )
			{
				boost::shared_ptr<Boulder> floater = boost::static_pointer_cast<Boulder>( CreateAt( level, CalcPos( *bob, BL, TR, level->getRnd() ) ) );
				Vector2 Padding = Vector2( 200, 375 );

				if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
					Tools::EnsureBounds_X( floater, TR - Padding, BL + Padding );
				else
					Tools::EnsureBounds_Y( floater, TR - Padding, BL + Padding );
			}
		}
	}

	void Boulder_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		// Get Floater parameters
		boost::shared_ptr<Boulder_Parameters> Params = boost::static_pointer_cast<Boulder_Parameters>( level->getStyle()->FindParams( Boulder_AutoGen::getInstance() ) );

		if ( Params->Special.Hallway )
			Hallway( level, BL, TR );

		if ( !Params->DoStage2Fill )
			return;

		float y = ( TR.Y + BL.Y ) / 2;
		Vector2 FillBL = Vector2( BL.X + 600, y - level->getMainCamera()->GetHeight() / 2 + 220 );
		Vector2 FillTR = Vector2( TR.X, y + level->getMainCamera()->GetHeight() / 2 - 350 );

		int Sparsity = static_cast<int>( Params->FloaterSparsity.getVal() );
		level->Fill( FillBL, FillTR, 225.f * Sparsity, 250.f, boost::make_shared<BoulderFillLambda>( level, TR, BL, boost::static_pointer_cast<Boulder_AutoGen>( shared_from_this() ) ) );
	}
}
