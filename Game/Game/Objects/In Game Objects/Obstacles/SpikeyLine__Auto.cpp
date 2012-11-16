#include <global_header.h>
namespace CloudberryKingdom
{

	void SpikeyLine_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		if ( PieceSeed->MyUpgrades1[ Upgrade_SPIKEY_LINE ] > 0 || PieceSeed->MyUpgrades2[ Upgrade_SPIKEY_LINE ] > 0 )
			Make = true;
		else
			Make = false;

		// General difficulty
		float FloaterLevel = PieceSeed->MyUpgrades1[ Upgrade_SPIKEY_LINE ];
		if ( FloaterLevel > 6 )
			NumOffsets = 8;
		else
			NumOffsets = 4;

		BobWidthLevel = Param( PieceSeed, u[ Upgrade_SPIKEY_LINE ] );

		LineStep = Param( PieceSeed, DifficultyHelper::Interp159( 1550, 800, 340, u[ Upgrade_SPIKEY_LINE ] ) );

		LinePeriod = Param( PieceSeed, __max( 70, 200 - 11 * u[ Upgrade_SPEED ] ) );
	}

const std::shared_ptr<SpikeyLine_AutoGen> SpikeyLine_AutoGen::instance = std::make_shared<SpikeyLine_AutoGen>();

	const std::shared_ptr<SpikeyLine_AutoGen> &SpikeyLine_AutoGen::getInstance() const
	{
		return instance;
	}

	SpikeyLine_AutoGen::SpikeyLine_AutoGen()
	{
	}

	SpikeyLine_AutoGen::SpikeyLine_AutoGen()
	{
		Do_PreFill_2 = true;
	}

	std::shared_ptr<AutoGen_Parameters> SpikeyLine_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<SpikeyLine_Parameters> Params = std::make_shared<SpikeyLine_Parameters>();
		Params->SetParameters( data, level );

		return static_cast<AutoGen_Parameters*>( Params );
	}

	void SpikeyLine_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	void SpikeyLine_AutoGen::CreateLine( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		// Get Floater parameters
		std::shared_ptr<SpikeyLine_Parameters> Params = static_cast<SpikeyLine_Parameters*>( level->Style_FIND_PARAMS( SpikeyLine_AutoGen::getInstance() ) );
		float Period = Params->LinePeriod.GetVal( pos );

		int n = 6;
		//int n = 12;
		//List<SpikeyLine> Line = new List<SpikeyLine>(n);

		float periodstep = Period / n;
		for ( int i = 0; i < n; i++ )
		{
			std::shared_ptr<SpikeyLine> spikey = static_cast<SpikeyLine*>( CreateAt( level, pos ) );
			spikey->Offset = static_cast<int>( i * periodstep );

			//Line.Add(spikey);
		}

		//Params.Lines.Add(Line);
	}

	std::shared_ptr<ObjectBase> SpikeyLine_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		// Get Floater parameters
		std::shared_ptr<SpikeyLine_Parameters> Params = static_cast<SpikeyLine_Parameters*>( level->Style_FIND_PARAMS( SpikeyLine_AutoGen::getInstance() ) );

		// Get the new floater
		std::shared_ptr<SpikeyLine> NewFloater = static_cast<SpikeyLine*>( level->getRecycle()->GetObject(ObjectType_SPIKEY_LINE, true) );

		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
		{
			NewFloater->p1.Y = level->getMainCamera()->TR.Y + 300;
			NewFloater->p2.Y = level->getMainCamera()->BL.Y - 300;
		}
		else
		{
			NewFloater->p1.Y = NewFloater->p2.Y = 0;
			NewFloater->p1.X = level->getMainCamera()->TR.X + 200;
			NewFloater->p2.X = level->getMainCamera()->BL.X - 200;
		}

		NewFloater->Move( pos );

		NewFloater->Offset = level->getRnd()->Rnd->Next(0, NewFloater->Period);

		// Discrete period offsets
		int NumOffsets = Params->NumOffsets;
		int Period = static_cast<int>( Params->LinePeriod.GetVal( pos ) / NumOffsets ) * NumOffsets;
		NewFloater->Period = Period;
		NewFloater->Offset = level->getRnd()->Rnd->Next(0, NumOffsets) * Period / NumOffsets;

		NewFloater->getCore()->GenData.RemoveIfUnused = false;

		// Bigger range for bigger levels
		//if (level.PieceSeed.ZoomType == LevelZoom.Big)
		//{
		//    NewFloater.p1.Y += 1300;
		//    NewFloater.p2.Y -= 1300;
		//}

		level->AddObject( NewFloater );

		return NewFloater;
	}

	void SpikeyLine_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		// Get Floater parameters
		std::shared_ptr<SpikeyLine_Parameters> Params = static_cast<SpikeyLine_Parameters*>( level->Style_FIND_PARAMS( SpikeyLine_AutoGen::getInstance() ) );

		if ( !Params->Make )
			return;

		float step = 5;

		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
		{
			Vector2 loc = Vector2( BL.X + 600, ( TR.Y + BL.Y ) / 2 );

			while ( loc.X < TR.X )
			{
				step = level->getRnd()->RndFloat(Params->LineStep.GetVal(loc), Params->LineStep.GetVal(loc));

				CreateLine( level, loc );

				loc.X += step;
			}
		}
		else
		{
			Vector2 loc = Vector2( ( TR.X + BL.X ) / 2, BL.Y + 600 );

			while ( loc.Y < TR.Y )
			{
				step = level->getRnd()->RndFloat(Params->LineStep.GetVal(loc), Params->LineStep.GetVal(loc));

				CreateLine( level, loc );

				loc.Y += step;
			}
		}
	}
}
