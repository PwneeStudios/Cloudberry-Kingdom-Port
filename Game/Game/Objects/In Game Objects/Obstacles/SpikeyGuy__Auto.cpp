#include <global_header.h>
namespace CloudberryKingdom
{

	void SpikeyGuy_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		if ( PieceSeed->MyUpgrades1->Get( Upgrade_PINKY ) > 0 || PieceSeed->MyUpgrades2->Get( Upgrade_PINKY ) > 0 )
			Make = true;
		else
			Make = false;

		// General difficulty
		float FloaterLevel = PieceSeed->MyUpgrades1->Get( Upgrade_PINKY );
		if ( FloaterLevel > 6 )
			NumOffsets = 8;
		else
			NumOffsets = 4;

		BobWidthLevel = Param( PieceSeed, u->Get( Upgrade_PINKY ) );

		FloaterMinDist = Param( PieceSeed, DifficultyHelper::Interp159( 700, 320, 100, u->Get( Upgrade_PINKY ) ) );

		FloaterScale = Param( PieceSeed, __min( 160, 90 + 7 * u->Get( Upgrade_PINKY ) ) );

		FloaterPeriod = Param( PieceSeed, __max( 84, 274 - 10 * u->Get( Upgrade_SPEED ) ) );

		Density = Param( PieceSeed, u->Get( Upgrade_PINKY ) == 0 ? 0 : DifficultyHelper::Interp( 40, 73, u->Get( Upgrade_PINKY ) ) );
	}

	SpikeyGuy_AutoGen::MinDistHelper::MinDistHelper( const std::shared_ptr<SpikeyGuy_Parameters> &Params )
	{
		this->Params = Params;
	}

	Vector2 SpikeyGuy_AutoGen::MinDistHelper::Apply( const Vector2 &pos )
	{
		float dist = Params->FloaterMinDist.GetVal( pos );
		return Vector2( dist, dist );
	}

	SpikeyGuy_AutoGen::SpikeyGuyCleanupMetricLambda::SpikeyGuyCleanupMetricLambda()
	{
	}

	Vector2 SpikeyGuy_AutoGen::SpikeyGuyCleanupMetricLambda::Apply( const std::shared_ptr<ObjectBase> &A, const std::shared_ptr<ObjectBase> &B )
	{
		std::shared_ptr<SpikeyGuy> floater_A = std::dynamic_pointer_cast<SpikeyGuy>( A );
		std::shared_ptr<SpikeyGuy> floater_B = std::dynamic_pointer_cast<SpikeyGuy>( B );
		return CoreMath::Abs( floater_A->PivotPoint - floater_B->PivotPoint );
	}

const std::shared_ptr<SpikeyGuy_AutoGen> SpikeyGuy_AutoGen::instance = std::make_shared<SpikeyGuy_AutoGen>();

	const std::shared_ptr<SpikeyGuy_AutoGen> &SpikeyGuy_AutoGen::getInstance()
	{
		return instance;
	}

	SpikeyGuy_AutoGen::SpikeyGuy_AutoGen()
	{
		Do_PreFill_2 = true;
	}

	std::shared_ptr<AutoGen_Parameters> SpikeyGuy_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<SpikeyGuy_Parameters> Params = std::make_shared<SpikeyGuy_Parameters>();
		Params->SetParameters( data, level );

		return std::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void SpikeyGuy_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );

		// Get Floater parameters
		std::shared_ptr<SpikeyGuy_Parameters> Params = std::static_pointer_cast<SpikeyGuy_Parameters>( level->getStyle()->FindParams( SpikeyGuy_AutoGen::getInstance() ) );

		level->Cleanup( ObjectType_SPIKEY_GUY, std::make_shared<MinDistHelper>( Params ), BL + Vector2( 400, 0 ), TR - Vector2( 500, 0 ), std::make_shared<SpikeyGuyCleanupMetricLambda>() );
	}

	std::shared_ptr<ObjectBase> SpikeyGuy_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		// Get Floater parameters
		std::shared_ptr<SpikeyGuy_Parameters> Params = std::static_pointer_cast<SpikeyGuy_Parameters>( level->getStyle()->FindParams( SpikeyGuy_AutoGen::getInstance() ) );

		// Get the new floater
		std::shared_ptr<SpikeyGuy> NewFloater = std::static_pointer_cast<SpikeyGuy>( level->getRecycle()->GetObject(ObjectType_SPIKEY_GUY, true) );
		NewFloater->Length = 650;
		NewFloater->Init( pos, level );

		NewFloater->Offset = level->getRnd()->Rnd->Next(0, NewFloater->Period);

		// Discrete period offsets
		int NumOffsets = Params->NumOffsets;
		int Period = static_cast<int>( Params->FloaterPeriod.GetVal( pos ) / NumOffsets ) * NumOffsets;
		NewFloater->Period = Period;
		NewFloater->Offset = Params->ChooseOffset( Period, level->getRnd() );

		NewFloater->getCore()->GenData.RemoveIfUnused = false;

		level->AddObject( NewFloater );

		return NewFloater;
	}

	void SpikeyGuy_AutoGen::Circle( const std::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir )
	{
		for ( int j = 0; j < Num; j++ )
		{
			std::shared_ptr<SpikeyGuy> floater = std::static_pointer_cast<SpikeyGuy>( CreateAt( level, Center ) );

			floater->Period = 3 * floater->Period / 2;
			floater->Offset = static_cast<int>( j * ( static_cast<float>( floater->Period ) / Num ) );
			floater->Length = Radius;

			floater->Dir = Dir;

			floater->getCore()->GenData.KeepIfUnused = true;

			level->AddObject( floater );
		}
	}

	void SpikeyGuy_AutoGen::Rockwheel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		Vector2 Center = ( TR + BL ) / 2;

		for ( int i = 7; i > 1; i-- )
		{
			int Num = 10;
			for ( int k = 0; k < 2; k++ )
				Circle( level, Center, 160 * i, Num, k % 2 == 0 ? 1 : -1 );
		}
	}

	void SpikeyGuy_AutoGen::Pinwheel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		Vector2 Center = ( TR + BL ) / 2;

		int Num = 30;

		if ( level->getRnd()->RndBool() )
		{
			for ( int k = 0; k < 2; k++ )
				Circle( level, Center, 160 * 7, Num, k % 2 == 0 ? 1 : -1 );
		}
		else
		{
			Circle( level, Center, 160 * 6, Num, 1 );
			Circle( level, Center, 160 * 7, Num, -1 );
		}
	}

	void SpikeyGuy_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		// Get Floater parameters
		std::shared_ptr<SpikeyGuy_Parameters> Params = std::static_pointer_cast<SpikeyGuy_Parameters>( level->getStyle()->FindParams( SpikeyGuy_AutoGen::getInstance() ) );

		if ( Params->Special.Rockwheel )
			Rockwheel( level, BL, TR );
		if ( Params->Special.Pinwheel )
			Pinwheel( level, BL, TR );

		if ( !Params->Make )
			return;

		for ( BlockVec::const_iterator block = level->Blocks.begin(); block != level->Blocks.end(); ++block )
		{
			if ( ( *block )->getCore()->Placed )
				continue;

			if ( ( *block )->getBlockCore()->Virgin )
				continue;
			if ( ( *block )->getBlockCore()->Finalized )
				continue;
			if ( ( *block )->getBlockCore()->MyType == ObjectType_LAVA_BLOCK )
				continue;

			// Add spinners
			float xdif = ( *block )->getBox()->Current->TR->X - (*block)->getBox()->Current->BL->X - 30;
			float density = level->getRnd()->RndFloat(Params->Density.GetVal((*block)->getCore()->Data.Position), Params->Density.GetVal((*block)->getCore()->Data.Position));
			float average = static_cast<int>( xdif * density / 2000 );
			int n = static_cast<int>( average );
			if ( average < 1 )
				if ( level->getRnd()->Rnd->NextDouble() < average )
					n = 1;

			for ( int i = 0; i < n; i++ )
			{
				if ( xdif > 0 )
				{
					float x = static_cast<float>( level->getRnd()->Rnd->NextDouble() ) * xdif + (*block)->getBox()->Target.BL::X + 35;
					float y;

					if ( ( *block )->getBlockCore()->BlobsOnTop )
					{
						y = ( *block )->getBox()->Target.TR::Y - 80 + 50;
					}
					else
					{
						y = ( *block )->getBox()->Target.BL::Y + 80 - 50;
					}

					if ( x > level->CurMakeData->PieceSeed->End.X - 400 )
						continue;

					std::shared_ptr<SpikeyGuy> floater = std::static_pointer_cast<SpikeyGuy>( CreateAt( level, Vector2( x, y ) ) );

					floater->SetParentBlock( *block );

					level->AddObject( floater );
				}
			}
		}
	}
}
