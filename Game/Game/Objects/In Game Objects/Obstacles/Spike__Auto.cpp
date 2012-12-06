#include <global_header.h>
namespace CloudberryKingdom
{

	void Spike_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		float lvl = PieceSeed->getu()->Get( Upgrade_SPIKE );

		// General difficulty
		int MinNumOffsets = 1;
		if ( lvl > 2.5f )
			MinNumOffsets = 2;
			if ( lvl > 6.5f )
				MinNumOffsets = 3;
		int MaxNumOffsets = 2;
		if ( lvl > 2.5f )
			MaxNumOffsets = 4;
			if ( lvl > 6.5f )
				MaxNumOffsets = 8;
		NumOffsets = level->getRnd()->RndInt(MinNumOffsets, MaxNumOffsets);

		OffsetStyle = static_cast<OffsetStyles>( level->getRnd()->getRndEnum()<OffsetStyles>() );

		BobWidthLevel = Param( PieceSeed, u->Get( Upgrade_SPIKE ) );

		float dist = 400 - u->Get( Upgrade_SPIKE ) * 40;
		if ( dist < 35 )
			dist = 35;

		SpikeMinDist = Param( PieceSeed, dist );

		MinSpikeDensity = Param( PieceSeed, u->Get( Upgrade_SPIKE ) == 0 ? 0 : DifficultyHelper::Interp( 6, 50, u->Get( Upgrade_SPIKE ) ) );

		MaxSpikeDensity = Param( PieceSeed, u->Get( Upgrade_SPIKE ) == 0 ? 0 : DifficultyHelper::Interp( 9, 80, u->Get( Upgrade_SPIKE ) ) );

		SpikePeriod = Param( PieceSeed, __max( 60, 240 - 20 * u->Get( Upgrade_SPEED ) ) );
	}

	void Spike_Parameters::SetPeriod( const std::shared_ptr<Spike> &spike, const std::shared_ptr<Rand> &Rnd )
	{
		Vector2 pos = spike->getCore()->Data.Position;
		int period = static_cast<int>( SpikePeriod.GetVal( pos ) );

		spike->SetPeriod( period );

		switch ( OffsetStyle )
		{
			case OffsetStyles_RND:
				spike->Offset = ChooseOffset( period, Rnd );
				break;
			case OffsetStyles_SAW_TOOTH:
				spike->Offset = static_cast<int>( ( pos.X / 700 ) * period ) % period;
				break;
			case OffsetStyles_SINE:
				spike->Offset = static_cast<int>( ( .5 * sin( pos.X / 700 * M_PI ) + .5 ) * period );
				break;
		}

		spike->Offset = EnforceOffset( spike->Offset, period );
	}

	Spike_AutoGen::SpikeCleanup::SpikeCleanup( const std::shared_ptr<Spike_Parameters> &Params )
	{
		this->Params = Params;
	}

	Vector2 Spike_AutoGen::SpikeCleanup::Apply( const Vector2 &pos )
	{
		float dist = Params->SpikeMinDist.GetVal( pos );
		return Vector2( dist, dist );
	}

const std::shared_ptr<Spike_AutoGen> Spike_AutoGen::instance = std::make_shared<Spike_AutoGen>();

	const std::shared_ptr<Spike_AutoGen> &Spike_AutoGen::getInstance()
	{
		return instance;
	}

	Spike_AutoGen::Spike_AutoGen()
	{
		Do_PreFill_2 = true;
		//Generators.AddGenerator(this);
	}

	std::shared_ptr<AutoGen_Parameters> Spike_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<Spike_Parameters> Params = std::make_shared<Spike_Parameters>();
		Params->SetParameters( data, level );

		return Params;
	}

	void Spike_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		// Get Spike parameters
		std::shared_ptr<Spike_Parameters> Params = std::static_pointer_cast<Spike_Parameters>( level->getStyle()->FindParams( Spike_AutoGen::getInstance() ) );

		if ( Params->MinSpikeDensity.getVal() <= 0 )
			return;

		float SpikeTopOffset = level->getInfo()->Spikes->TopOffset;
		float SpikeBottomOffset = level->getInfo()->Spikes->BottomOffset;
		float SpikeSideOffset = level->getInfo()->Spikes->SideOffset;

		for ( BlockVec::const_iterator block = level->Blocks.begin(); block != level->Blocks.end(); ++block )
		{
			if ( ( *block )->getCore()->Placed )
				continue;

			if ( !( ( *block )->getBlockCore()->BlobsOnTop || (*block)->getBlockCore()->Ceiling ) )
				continue;

			//if (!(block is NormalBlock)) continue;
			if ( ( *block )->getBlockCore()->Virgin )
				continue;
			if ( ( *block )->getBlockCore()->Finalized )
				continue;
			if ( ( *block )->getBlockCore()->MyType == ObjectType_LAVA_BLOCK )
				continue;


			// Add spikes
			float xdif = ( *block )->getBox()->Current->TR->X - (*block)->getBox()->Current->BL->X - 110;
			float density = level->getRnd()->RndFloat(Params->MinSpikeDensity.GetVal((*block)->getCore()->Data.Position), Params->MaxSpikeDensity.GetVal((*block)->getCore()->Data.Position));
			float average = static_cast<int>( xdif * static_cast<float>( density ) / 2000 );
			int n = static_cast<int>( average );
			//if (average < 1) if (Rnd.Rnd.NextDouble() < average) n = 1;
			if ( average < 2 )
				n = 2;

			for ( int i = 0; i < n; i++ )
			{
				//if (xdif > 15)
			{
					std::shared_ptr<Spike> spike = std::static_pointer_cast<Spike>( level->getRecycle()->GetObject(ObjectType_SPIKE, true) ); //false);
					spike->Init( Vector2(), level );

					float x = static_cast<float>( level->getRnd()->Rnd->NextDouble() ) * xdif + (*block)->getBox()->Target.BL::X + 55;
					float y;

					if ( ( *block )->getBlockCore()->BlobsOnTop )
					{
						y = ( *block )->getBox()->Target.TR::Y + SpikeTopOffset;
						spike->SetDir( 0 );
					}
					else
					{
						y = ( *block )->getBox()->Target.BL::Y - SpikeBottomOffset;
						spike->SetDir( 2 );
					}

					Vector2 pos = Vector2( x, y );
					Tools::MoveTo( spike, pos );

					Params->SetPeriod( spike, level->getRnd() );

					spike->SetParentBlock( *block );
					level->AddObject( spike );
				}
			}

			if ( !( *block )->getBox()->TopOnly )
			{
				float ydif = ( *block )->getBox()->Current->TR->Y - (*block)->getBox()->Current->BL->Y - 110;
				average = static_cast<int>( ydif * static_cast<float>( density ) / 2000 );
				n = static_cast<int>( average );
				if ( average < 1 )
					if ( level->getRnd()->Rnd->NextDouble() < average )
						n = 1;
				n = 4;
				for ( int i = 0; i < n; i++ )
				{
					// Side spikes
					if ( ydif > 15 )
					{
						float y = static_cast<float>( level->getRnd()->Rnd->NextDouble() ) * ydif + (*block)->getBox()->Target.BL::Y + 55;
						float x;

						if ( y < ( *block )->getBox()->TR->Y - level->getInfo()->ObstacleCutoff )
							continue;

						std::shared_ptr<Spike> spike = std::static_pointer_cast<Spike>( level->getRecycle()->GetObject(ObjectType_SPIKE, true) ); //false);
						spike->Init( Vector2(), level );

						if ( level->getRnd()->Rnd->Next(0, 2) == 0 )
						{
							x = ( *block )->getBox()->Target.TR::X + SpikeSideOffset;
							spike->SetDir( 3 );
							y -= 25;
						}
						else
						{
							x = ( *block )->getBox()->Target.BL::X - SpikeSideOffset;
							spike->SetDir( 1 );
						}

						Tools::MoveTo( spike, Vector2( x, y ) );

						Params->SetPeriod( spike, level->getRnd() );

						spike->SetParentBlock( *block );
						level->AddObject( spike );
					}
				}
			}
		}
	}

	void Spike_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );

		// Get Spike parameters
		std::shared_ptr<Spike_Parameters> Params = std::static_pointer_cast<Spike_Parameters>( level->getStyle()->FindParams( Spike_AutoGen::getInstance() ) );

		level->Cleanup( ObjectType_SPIKE, std::make_shared<SpikeCleanup>( Params ), BL, TR );
	}
}
