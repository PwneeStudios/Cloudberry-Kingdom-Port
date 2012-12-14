#include <global_header.h>

#include <Hacks\List.h>

namespace CloudberryKingdom
{

	void Pendulum_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		float lvl = PieceSeed->MyUpgrades1->Get( Upgrade_PENDULUM );

		Size = Param( PieceSeed );
		Size.SetVal( 230 - ( 230 - 50 ) / 10 * u->Get( Upgrade_PENDULUM ) );

		Motion = static_cast<MotionType>( level->getRnd()->Choose(MotionLevel, static_cast<int>(lvl)) );

		KeepUnused = Param( PieceSeed );
		if ( std::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_PENDULUM ) ) );
		}

		FillWeight = Param( PieceSeed );
		FillWeight.SetVal( u->Get( Upgrade_PENDULUM ) );

		float speed = 300 - 30 * u->Get( Upgrade_SPEED ) + 45 *.5f * ( u->Get( Upgrade_JUMP ) + u->Get( Upgrade_PENDULUM ) );
		Period = Param( PieceSeed );
		Period.SetVal( CoreMath::RestrictVal( 40.f, 1000.f, speed ) );

		MaxAngle = Param( PieceSeed, __min( 750, 30 + 64 *.5f * ( u->Get( Upgrade_JUMP ) + u->Get( Upgrade_PENDULUM ) ) ) );
	}

	void Pendulum_Parameters::InitializeInstanceFields()
	{
		int tempVector[] = { 0, 1, 2, 3, 4, 5, 6 };
		MotionLevel = VecFromArray( tempVector );
	}

	std::shared_ptr<Pendulum_AutoGen> Pendulum_AutoGen::instance = std::make_shared<Pendulum_AutoGen>();

	const std::shared_ptr<Pendulum_AutoGen> &Pendulum_AutoGen::getInstance()
	{
		return instance;
	}

	Pendulum_AutoGen::Pendulum_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
	}

	std::shared_ptr<AutoGen_Parameters> Pendulum_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<Pendulum_Parameters> Params = std::make_shared<Pendulum_Parameters>();
		Params->SetParameters( data, level );

		return std::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	std::shared_ptr<ObjectBase> Pendulum_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		std::shared_ptr<StyleData> Style = level->getStyle();
		std::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		std::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get Pendulum parameters
		std::shared_ptr<Pendulum_Parameters> Params = std::static_pointer_cast<Pendulum_Parameters>( level->getStyle()->FindParams( Pendulum_AutoGen::getInstance() ) );

		Vector2 size = Vector2( Params->Size.GetVal( pos ), 40 );
		Vector2 offset = Vector2( 0, -300 );

		std::shared_ptr<Pendulum> p = std::static_pointer_cast<Pendulum>( level->getRecycle()->GetObject(ObjectType_PENDULUM, true) );
		p->Init( pos + offset, size, level );

		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
			p->PivotPoint.Y = p->getPos().Y + 2000;
		else
		{
			p->PivotPoint.X = level->getMainCamera()->BL.X - 160;
			p->AddAngle = CoreMath::Radians( 90 );
		}

		p->Period = static_cast<int>( Params->Period.GetVal( pos ) );
		p->MaxAngle = static_cast<float>( static_cast<int>( Params->MaxAngle.GetVal( pos ) ) );
		p->MaxAngle *= .001f;
		p->CalculateLength();

		p->Offset = level->getStyle()->GetOffset( p->Period, pos, level->getStyle()->PendulumOffsetType );

		p->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		p->getBlockCore()->GenData.EdgeSafety = static_cast<float>( GenData->Get(DifficultyParam_EDGE_SAFETY, pos) );

		if ( level->getStyle()->RemoveBlockOnOverlap )
			p->getBlockCore()->GenData.RemoveIfOverlap = true;

		Tools::EnsureBounds_X( p, TR, BL );

		level->AddBlock( p );

		return p;
	}
}
