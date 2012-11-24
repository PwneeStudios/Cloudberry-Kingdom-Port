#include <global_header.h>
namespace CloudberryKingdom
{

	void Ceiling_Parameters::SetLongCeiling()
	{
		Special.LongCeiling = true;
		Make = false;
	}

	void Ceiling_Parameters::SetCementCeiling()
	{
		Special.CementCeiling = true;
		Make = false;
	}

	void Ceiling_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		MyStyle = static_cast<Style>( level->getRnd()->getRndEnum()<Style>() );

		if ( PieceSeed->getu()[ Upgrade_CEILING ] <= 0 )
			Make = false;

		HeightRange = VectorParam( PieceSeed, DifficultyHelper::InterpRestrict19( Vector2( 100, 900 ), Vector2( 500, 1300 ), u[ Upgrade_CEILING ] ) );

		WidthRange = VectorParam( PieceSeed, DifficultyHelper::InterpRestrict19( Vector2( 450, 1450 ), Vector2( 80, 80 ), u[ Upgrade_CEILING ] ) );

		BufferSize = Param( PieceSeed, DifficultyHelper::InterpRestrict19( 150, 10, u[ Upgrade_CEILING ] ) );
	}

	void Ceiling_Parameters::InitializeInstanceFields()
	{
		Make = true;
	}

const std::shared_ptr<Ceiling_AutoGen> Ceiling_AutoGen::instance = std::make_shared<Ceiling_AutoGen>();

	const std::shared_ptr<Ceiling_AutoGen> &Ceiling_AutoGen::getInstance()
	{
		return instance;
	}

	Ceiling_AutoGen::Ceiling_AutoGen()
	{
		Do_PreFill_1 = true;
	}

	std::shared_ptr<AutoGen_Parameters> Ceiling_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<Ceiling_Parameters> Params = std::make_shared<Ceiling_Parameters>();
		Params->SetParameters( data, level );

		return static_cast<AutoGen_Parameters*>( Params );
	}

	void Ceiling_AutoGen::MakeLongCeiling( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		std::shared_ptr<NormalBlock> cblock = static_cast<NormalBlock*>( level->getRecycle()->GetObject( ObjectType_NORMAL_BLOCK, true ) );
		Vector2 size = TR - BL + Vector2( 4000, 0 );
		Vector2 pos = ( TR + BL ) / 2 + Vector2( 0, 500 );
		cblock->Init( pos, size, level->getMyTileSetInfo() );

		cblock->Extend( Side_BOTTOM, TR.Y - 200 );
		cblock->StampAsFullyUsed( 0 );
		cblock->getBlockCore()->CeilingDraw = true;

		level->AddBlock( cblock );
	}

	void Ceiling_AutoGen::PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		std::shared_ptr<Ceiling_Parameters> Params = static_cast<Ceiling_Parameters*>( level->Style_FIND_PARAMS( Ceiling_AutoGen::getInstance() ) );

		float MaxStartY = -100000;
		for ( int i = 0; i < level->CurMakeData->NumInitialBobs; i++ )
			MaxStartY = __max( MaxStartY, level->CurMakeData->Start[ i ].Position.Y );

		MakeCeiling( level, BL, TR, MaxStartY );
	}

	void Ceiling_AutoGen::MakeCeiling( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR, float MaxStartY )
	{
		if ( !level->MyTileSet->HasCeiling )
			return;

		std::shared_ptr<Ceiling_Parameters> Params = static_cast<Ceiling_Parameters*>( level->Style_FIND_PARAMS( Ceiling_AutoGen::getInstance() ) );

		if ( !Params->Make )
			return;

		// Ceiling
		Vector2 Pos = Vector2( BL.X, TR.Y );
		std::shared_ptr<NormalBlock> cblock, lastblock = 0;
		while ( Pos.X < TR.X )
		{
			Vector2 size = Vector2( Params->WidthRange.RndFloat( Pos, level->getRnd() ), Params->HeightRange.RndFloat(Pos, level->getRnd()) );

			cblock = static_cast<NormalBlock*>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
			cblock->Init( Vector2::Zero, size, level->getMyTileSetInfo() );
			size = cblock->getBox()->Current->Size;

			Vector2 offset = Vector2( size.X, 0 );

			// Make sure the ceiling block isn't past the left or right edges of the level.
			if ( Pos.X + offset.X + size.X > TR.X )
				size.X = TR.X - Pos.X - offset.X;
			if ( Pos.X + offset.X - size.X < BL.X )
				size.X = Pos.X + offset.X - BL.X;
			if ( size.X < 50 )
			{
				Pos.X += 100;
				continue;
			}
			offset = Vector2( size.X, 0 );

			// Initialize the size, make sure to modify it's width, since it's a ceiling block
			cblock->Init( Pos + offset, size, level->getMyTileSetInfo() );
			cblock->getCore()->GenData.RemoveIfUnused = false;
			cblock->getCore()->GenData.KeepIfUnused = true;
			cblock->getBlockCore()->CeilingDraw = cblock->getBlockCore()->Ceiling = true;
			cblock->getBlockCore()->BlobsOnTop = false;
			cblock->getBlockCore()->TopLeftNeighbor = lastblock;
			cblock->getBlockCore()->CeilingDraw = true;
			lastblock = cblock;

			if ( Pos.X < BL.X + 900 )
				cblock->Extend( Side_BOTTOM, __max( cblock->getBox()->Current->BL.Y, MaxStartY + 250 ) );
			if ( cblock->getBox()->Current->Size.X < 40 )
			{
				Pos.X += 100;
				continue;
			}
			cblock->Extend( Side_TOP, TR.Y + 600 + level->CurMakeData->PieceSeed->ExtraBlockLength + 1000 );

			if ( cblock->getBox()->Current->Size.X > 35 )
				level->AddBlock( cblock );

			switch ( Params->MyStyle )
			{
				case Ceiling_Parameters::Style_NORMAL:
					Pos.X += 2 * cblock->getBox()->Current->Size.X;
					break;
				case Ceiling_Parameters::Style_SKIP_ONE:
					Pos.X += 2 * 2 * cblock->getBox()->Current->Size.X;
					break;
				case Ceiling_Parameters::Style_SPARSE:
					Pos.X += level->getRnd()->RndInt(7, 8) * cblock->getBox()->Current->Size.X;
					break;
				case Ceiling_Parameters::Style_RANDOM:
					Pos.X += level->getRnd()->RndInt(2, 8) * cblock->getBox()->Current->Size.X;
					break;
			}
			Pos.X += 20;
		}
	}
}
