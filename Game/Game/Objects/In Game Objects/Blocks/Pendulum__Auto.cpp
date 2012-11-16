#include <global_header.h>
namespace CloudberryKingdom
{

	void Pendulum_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		float lvl = PieceSeed->MyUpgrades1[ Upgrade_PENDULUM ];

		Size = Param( PieceSeed );
		Size.SetVal( 230 - ( 230 - 50 ) / 10 * u[ Upgrade_PENDULUM ] );

		Motion = static_cast<MotionType>( level->getRnd()->Choose(MotionLevel, static_cast<int>(lvl)) );

		KeepUnused = Param( PieceSeed );
		if ( dynamic_cast<BobPhsxSpaceship*>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u[ Upgrade_PENDULUM ] ) );
		}

		FillWeight = Param( PieceSeed );
		FillWeight.SetVal( u[ Upgrade_PENDULUM ] );

		float speed = 300 - 30 * u[ Upgrade_SPEED ] + 45 *.5f * ( u[ Upgrade_JUMP ] + u[ Upgrade_PENDULUM ] );
		Period = Param( PieceSeed );
		Period.SetVal( CoreMath::Restrict( 40, 1000, speed ) );

		MaxAngle = Param( PieceSeed, __min( 750, 30 + 64 *.5f * ( u[ Upgrade_JUMP ] + u[ Upgrade_PENDULUM ] ) ) );
	}

	void Pendulum_Parameters::InitializeInstanceFields()
	{
		const int tempVector[] = { 0, 1, 2, 3, 4, 5, 6 };
		std::vector<int> temp_MotionLevel = std::vector<int>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
		for ( int element = 0; element < sizeof( temp_MotionLevel ) / sizeof( temp_MotionLevel[ 0 ] ); element++ )
			MotionLevel[ element ] = temp_MotionLevel[ element ];
	}

const std::shared_ptr<Pendulum_AutoGen> Pendulum_AutoGen::instance = std::make_shared<Pendulum_AutoGen>();

	const std::shared_ptr<Pendulum_AutoGen> &Pendulum_AutoGen::getInstance() const
	{
		return instance;
	}

	Pendulum_AutoGen::Pendulum_AutoGen()
	{
	}

	Pendulum_AutoGen::Pendulum_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
	}

	std::shared_ptr<AutoGen_Parameters> Pendulum_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<Pendulum_Parameters> Params = std::make_shared<Pendulum_Parameters>();
		Params->SetParameters( data, level );

		return static_cast<AutoGen_Parameters*>( Params );
	}

	std::shared_ptr<ObjectBase> Pendulum_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		std::shared_ptr<StyleData> Style = level->getStyle();
		std::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		std::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get Pendulum parameters
		std::shared_ptr<Pendulum_Parameters> Params = static_cast<Pendulum_Parameters*>( level->Style_FIND_PARAMS( Pendulum_AutoGen::getInstance() ) );

		Vector2 size = Vector2( Params->Size.GetVal( pos ), 40 );
		Vector2 offset = Vector2( 0, -300 );

		std::shared_ptr<Pendulum> p = static_cast<Pendulum*>( level->getRecycle()->GetObject(ObjectType_PENDULUM, true) );
		p->Init( pos + offset, size, level );

		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
			p->PivotPoint.Y = p->getPos().Y + 2000;
		else
		{
			p->PivotPoint.X = level->getMainCamera()->BL.X - 160;
			p->AddAngle = CoreMath::Radians( 90 );
		}

		p->Period = static_cast<int>( Params->Period.GetVal( pos ) );
		p->MaxAngle = static_cast<int>( Params->MaxAngle.GetVal( pos ) );
		p->MaxAngle *= .001f;
		p->CalculateLength();

		p->Offset = level->Style_GET_OFFSET( p->Period, pos, level->Style_PENDULUM_OFFSET_TYPE );

		p->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		p->getBlockCore()->GenData.EdgeSafety = GenData->Get(DifficultyParam_EDGE_SAFETY, pos);

		if ( level->Style_REMOVE_BLOCK_ON_OVERLAP )
			p->getBlockCore()->GenData.RemoveIfOverlap = true;

		Tools::EnsureBounds_X( p, TR, BL );

		level->AddBlock( p );

		return p;
	}
}
