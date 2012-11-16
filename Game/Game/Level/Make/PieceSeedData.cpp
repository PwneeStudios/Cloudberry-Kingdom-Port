#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


namespace CloudberryKingdom
{

	void PieceSeedData::CalculateSimple()
	{
		MyUpgrades1->CalcGenData( MyGenData->gen1, Style );

		RndDifficulty::ZeroUpgrades( MyUpgrades2 );
		MyUpgrades1->UpgradeLevels.CopyTo( MyUpgrades2->UpgradeLevels, 0 );
		MyUpgrades2->CalcGenData( MyGenData->gen2, Style );
	}

	std::shared_ptr < AutoGen_Parameters *PieceSeedData::operator []( const std::shared_ptr<AutoGen> &gen )
	{
		return Style_FIND_PARAMS( gen );
	}

	const std::shared_ptr<Upgrades> &PieceSeedData::getu() const
	{
		return MyUpgrades1;
	}

	void PieceSeedData::Release()
	{
		if ( Style != 0 )
			Style_RELEASE();
			Style_SMARTPOINTERRESET();
		PieceSeed.reset();
		MyGenData.reset();
		MyLevelSeed.reset();
	}

	void PieceSeedData::CopyFrom( const std::shared_ptr<PieceSeedData> &piece )
	{
		//Style = piece.Style.Clone();
		MyUpgrades1->CopyFrom( piece->MyUpgrades1 );
		MyUpgrades1->CalcGenData( MyGenData->gen1, Style );
		MyUpgrades2->CopyFrom( piece->MyUpgrades2 );
		MyUpgrades2->CalcGenData( MyGenData->gen2, Style );
	}

	void PieceSeedData::CopyUpgrades( const std::shared_ptr<PieceSeedData> &piece )
	{
		MyUpgrades1->CopyFrom( piece->MyUpgrades1 );
		MyUpgrades2->CopyFrom( piece->MyUpgrades2 );
	}

	void PieceSeedData::CalcBounds()
	{
	}

	void PieceSeedData::StandardClose()
	{
		int TestNumber;

		TestNumber = getRnd()->RndInt(0, 1000);
		Tools::Write( std::wstring::Format( _T( "Test close start: {0}" ), TestNumber ) );

		MyUpgrades1->CalcGenData( MyGenData->gen1, Style );

		RndDifficulty::ZeroUpgrades( MyUpgrades2 );
		MyUpgrades1->UpgradeLevels.CopyTo( MyUpgrades2->UpgradeLevels, 0 );
		MyUpgrades2->CalcGenData( MyGenData->gen2, Style );

		TestNumber = getRnd()->RndInt(0, 1000);
		Tools::Write( std::wstring::Format( _T( "Test close end: {0}" ), TestNumber ) );

		Style_MY_INITIAL_PLATS_TYPE = StyleData::InitialPlatsType_DOOR;
		Style_MY_FINAL_PLATS_TYPE = StyleData::FinalPlatsType_DOOR;
	}

	const std::shared_ptr<Rand> &PieceSeedData::getRnd() const
	{
		return MyLevelSeed->Rnd;
	}

	PieceSeedData::PieceSeedData( const std::shared_ptr<LevelSeedData> &LevelSeed )
	{
		InitializeInstanceFields();
		MyLevelSeed = LevelSeed;
		Init( LevelGeometry_RIGHT );
	}

	PieceSeedData::PieceSeedData( int Index, LevelGeometry Type, const std::shared_ptr<LevelSeedData> &LevelSeed )
	{
		InitializeInstanceFields();
		MyLevelSeed = LevelSeed;
		MyPieceIndex = Index;
		Init( Type );
	}

	void PieceSeedData::Init( LevelGeometry Type )
	{
		GeometryType = Type;

		if ( MyLevelSeed != 0 )
		switch ( GeometryType )
		{
			case LevelGeometry_RIGHT:
				Style = std::make_shared<SingleData>( getRnd() );
				break;
			case LevelGeometry_DOWN:
				Style = std::make_shared<DownData>( getRnd() );
				break;
			case LevelGeometry_UP:
				Style = std::make_shared<UpData>( getRnd() );
				break;
			case LevelGeometry_ONE_SCREEN:
				Style = std::make_shared<OneScreenData>( getRnd() );
				break;
			case LevelGeometry_BIG:
				Style = std::make_shared<BigData>( getRnd() );
				break;
		}

		MyGenData = std::make_shared<RichLevelGenData>();
		MyGenData->gen1 = std::make_shared<LevelGenData>();
		MyGenData->gen2 = std::make_shared<LevelGenData>();

		MyUpgrades1 = std::make_shared<Upgrades>();
		MyUpgrades2 = std::make_shared<Upgrades>();

		//MyGenData.gen3 = new LevelGenData();
		//MyUpgrades1.CalcGenData(MyGenData.gen3);

		Ladder = Level.LadderType_NONE;
	}

	void PieceSeedData::NoBlobs()
	{
		MyUpgrades1[ Upgrade_FALLING_BLOCK ] = __max( MyUpgrades1[ Upgrade_FALLING_BLOCK ], MyUpgrades1[ Upgrade_FLY_BLOB ] );
		MyUpgrades1[ Upgrade_FLY_BLOB ] = 0;

		MyUpgrades2[ Upgrade_MOVING_BLOCK ] = __max( MyUpgrades2[ Upgrade_MOVING_BLOCK ], MyUpgrades2[ Upgrade_FLY_BLOB ] );
		MyUpgrades2[ Upgrade_FLY_BLOB ] = 0;
	}

	void PieceSeedData::InitializeInstanceFields()
	{
		GeometryType = LevelGeometry_RIGHT;
		ZoomType = LevelZoom_NORMAL;
		ExtraBlockLength = 0;
		Paths = -1;
		LockNumOfPaths = false;
		ElevatorBoxStyle = BlockEmitter_Parameters::BoxStyle_TOP_ONLY;
		MyPieceIndex = -1;
	}
}
