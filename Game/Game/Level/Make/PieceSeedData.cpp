#include <global_header.h>

#include <Hacks/List.h>
#include <Hacks/String.h>

namespace CloudberryKingdom
{

	struct MetaGameEscalationProxy : public Lambda_2<boost::shared_ptr<Level>, boost::shared_ptr<PieceSeedData> >
	{
		void Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p )
		{
            boost::shared_ptr<Coin_Parameters> Params = boost::static_pointer_cast<Coin_Parameters>( p->Style->FindParams( Coin_AutoGen::getInstance() ) );
            Params->StartFrame = 90;
            Params->FillType = Coin_Parameters::FillTypes_REGULAR;
		}
	};

	struct MetaGameTimeCrisisProxy : public Lambda_2<boost::shared_ptr<Level>, boost::shared_ptr<PieceSeedData> >
	{
		void Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p )
		{
			boost::shared_ptr<Coin_Parameters> Params = boost::static_pointer_cast<Coin_Parameters>( p->Style->FindParams( Coin_AutoGen::getInstance() ) );
			Params->FillType = Coin_Parameters::FillTypes_RUSH;
		}
	};

    void PieceSeedData::ApplyMetaGameStyling()
    {
        switch (MyMetaGameType)
        {
            case MetaGameType_ESCALATION:
                // Shorten the initial computer delay
                Style->ComputerWaitLengthRange = Vector2(8, 35);

                Style->MyModParams->Add( boost::make_shared<MetaGameEscalationProxy>() );

                break;

            case MetaGameType_TIME_CRISIS:
                // Shorten the initial computer delay
                Style->ComputerWaitLengthRange = Vector2(4, 23);

                // Only one path
                Paths = 1; LockNumOfPaths = true;

				Style->MyModParams->Add( boost::make_shared<MetaGameTimeCrisisProxy>() );

                break;

            default:
                break;
        }
    }

	void PieceSeedData::CalculateSimple()
	{
		MyUpgrades1->CalcGenData( MyGenData->gen1, Style );

		RndDifficulty::ZeroUpgrades( MyUpgrades2 );
		CopyFromTo( MyUpgrades1->UpgradeLevels, MyUpgrades2->UpgradeLevels );
		MyUpgrades2->CalcGenData( MyGenData->gen2, Style );
	}

	boost::shared_ptr<AutoGen_Parameters> PieceSeedData::operator []( const boost::shared_ptr<AutoGen> &gen )
	{
		return Style->FindParams( gen );
	}

	const boost::shared_ptr<Upgrades> &PieceSeedData::getu() const
	{
		return MyUpgrades1;
	}

	void PieceSeedData::Release()
	{
		PreStage1.reset();
		PreStage2.reset();
		if ( Style != 0 ) Style->Release(); Style.reset();
		PieceSeed.reset();
		
		if ( MyGenData != 0 )
		{
			MyGenData->gen1.reset();
			MyGenData->gen2.reset();
		}
		MyGenData.reset();

		MyLevelSeed.reset();
		MyUpgrades1.reset(); MyUpgrades2.reset();
	}

	void PieceSeedData::CopyFrom( const boost::shared_ptr<PieceSeedData> &piece )
	{
		//Style = piece.Style.Clone();
		MyUpgrades1->CopyFrom( piece->MyUpgrades1 );
		MyUpgrades1->CalcGenData( MyGenData->gen1, Style );
		MyUpgrades2->CopyFrom( piece->MyUpgrades2 );
		MyUpgrades2->CalcGenData( MyGenData->gen2, Style );
	}

	void PieceSeedData::CopyUpgrades( const boost::shared_ptr<PieceSeedData> &piece )
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
		Tools::Write( Format( _T( "Test close start: %d" ), TestNumber ).c_str() );

		MyUpgrades1->CalcGenData( MyGenData->gen1, Style );

		RndDifficulty::ZeroUpgrades( MyUpgrades2 );
		CopyFromTo( MyUpgrades1->UpgradeLevels, MyUpgrades2->UpgradeLevels );
		MyUpgrades2->CalcGenData( MyGenData->gen2, Style );

		TestNumber = getRnd()->RndInt(0, 1000);
		Tools::Write( Format( _T( "Test close end: %d" ), TestNumber ).c_str() );

		Style->MyInitialPlatsType = StyleData::InitialPlatsType_DOOR;
		Style->MyFinalPlatsType = StyleData::FinalPlatsType_DOOR;
	}

	const boost::shared_ptr<Rand> &PieceSeedData::getRnd() const
	{
		return MyLevelSeed->Rnd;
	}

	PieceSeedData::PieceSeedData( const boost::shared_ptr<LevelSeedData> &LevelSeed )
	{
		InitializeInstanceFields();
		MyLevelSeed = LevelSeed;
		Init( LevelGeometry_RIGHT );
	}

	PieceSeedData::PieceSeedData( int Index, LevelGeometry Type, const boost::shared_ptr<LevelSeedData> &LevelSeed )
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
				Style = boost::make_shared<SingleData>( getRnd() );
				break;
			case LevelGeometry_DOWN:
				Style = boost::make_shared<DownData>( getRnd() );
				break;
			case LevelGeometry_UP:
				Style = boost::make_shared<UpData>( getRnd() );
				break;
			case LevelGeometry_ONE_SCREEN:
				Style = boost::make_shared<OneScreenData>( getRnd() );
				break;
			case LevelGeometry_BIG:
				Style = boost::make_shared<BigData>( getRnd() );
				break;
		}

		MyGenData = boost::make_shared<RichLevelGenData>();
		MyGenData->gen1 = boost::make_shared<LevelGenData>();
		MyGenData->gen2 = boost::make_shared<LevelGenData>();

		MyUpgrades1 = boost::make_shared<Upgrades>();
		MyUpgrades2 = boost::make_shared<Upgrades>();

		//MyGenData.gen3 = new LevelGenData();
		//MyUpgrades1.CalcGenData(MyGenData.gen3);

		Ladder = LadderType_NONE;
	}

	void PieceSeedData::NoBlobs()
	{
		MyUpgrades1->Get( Upgrade_FALLING_BLOCK ) = __max( MyUpgrades1->Get( Upgrade_FALLING_BLOCK ), MyUpgrades1->Get( Upgrade_FLY_BLOB ) );
		MyUpgrades1->Get( Upgrade_FLY_BLOB ) = 0;

		MyUpgrades2->Get( Upgrade_MOVING_BLOCK ) = __max( MyUpgrades2->Get( Upgrade_MOVING_BLOCK ), MyUpgrades2->Get( Upgrade_FLY_BLOB ) );
		MyUpgrades2->Get( Upgrade_FLY_BLOB ) = 0;
	}

	void PieceSeedData::InitializeInstanceFields()
	{
		MyMetaGameType = MetaGameType_NONE;

		CheckpointsAtStart = false; InitialCheckpointsHere = false;

		MyPieceIndex = 0;

		GeometryType = LevelGeometry_RIGHT;
		ZoomType = LevelZoom_NORMAL;
		ExtraBlockLength = 0;
		Paths = -1;
		LockNumOfPaths = false;
		ElevatorBoxStyle = BoxStyle_TOP_ONLY;
		MyPieceIndex = -1;
	}
}
