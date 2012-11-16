#include <global_header.h>

namespace CloudberryKingdom
{

	void TileInfoBase::InitializeInstanceFields()
	{
		Icon = std::make_shared<SpriteInfo>( 0, Vector2( 50, -1 ) );
		Icon_Big = 0;
	}

	void TileSet::TileSetInfo::InitializeInstanceFields()
	{
		ScaleAll = 1;
		ScaleAllBlocks = 1;
		ScaleAllObjects = 1;
		AllowLava = true;
		ObstacleCutoff = 1000;
		ShiftStartDoor = 0;
		ShiftStartBlock = Vector2::Zero;
		AllowTopOnlyBlocks = true;
		Walls = std::make_shared<Wall::WallTileInfo>();
		Pendulums = std::make_shared<Pendulum::PendulumTileInfo>();
		LavaDrips = std::make_shared<LavaDrip::LavaDripTileInfo>();
		Serpents = std::make_shared<Serpent::SerpentTileInfo>();
		Firesnakes = std::make_shared<Firesnake::FiresnakeTileInfo>();
		Clouds = std::make_shared<Cloud::CloudTileInfo>();
		Elevators = std::make_shared<MovingPlatform::ElevatorTileInfo>();
		MovingBlocks = std::make_shared<MovingBlock::MovingBlockTileInfo>();
		BouncyBlocks = std::make_shared<BouncyBlock::BouncyBlockTileInfo>();
		FallingBlocks = std::make_shared<FallingBlock::FallingBlockTileInfo>();
		GhostBlocks = std::make_shared<GhostBlock::GhostBlockTileInfo>();
		Blobs = std::make_shared<FlyingBlob::FlyingBlobTileInfo>();
		Lasers = std::make_shared<Laser::LaserTileInfo>();
		SpikeyLines = std::make_shared<SpikeyLine::SpikeyLineTileInfo>();
		SpikeyGuys = std::make_shared<SpikeyGuy::SpikeyGuyTileInfo>();
		Boulders = std::make_shared<Boulder::BoulderTileInfo>();
		Spikes = std::make_shared<Spike::SpikeTileInfo>();
		Spinners = std::make_shared<FireSpinner::FireSpinnerTileInfo>();
		Fireballs = std::make_shared<Fireball::FireballTileInfo>();
		Checkpoints = std::make_shared<Checkpoint::CheckpointTileInfo>();
		Coins = std::make_shared<Coin::CoinTileInfo>();
		Doors = std::make_shared<Door::DoorTileInfo>();
	}

	std::shared_ptr<TileInfoBase> TileSet::UpgradeToInfo( Upgrade upgrade, const std::shared_ptr<TileSet> &tile )
	{
		std::shared_ptr<TileSet::TileSetInfo> info = tile->MyTileSetInfo;

		switch ( upgrade )
		{
			case Upgrade_BOUNCY_BLOCK:
				return info->BouncyBlocks;
			case Upgrade_CEILING:
				return 0;
			case Upgrade_CLOUD:
				return info->Clouds;
			case Upgrade_CONVEYOR:
				return 0;
			case Upgrade_ELEVATOR:
				return info->Elevators;
			case Upgrade_FALLING_BLOCK:
				return info->FallingBlocks;
			case Upgrade_FIREBALL:
				return info->Fireballs;
			case Upgrade_FIRESNAKE:
				return info->Firesnakes;
			case Upgrade_FIRE_SPINNER:
				return info->Spinners;
			case Upgrade_FLY_BLOB:
				return info->Blobs;
			case Upgrade___UNUSED__1:
				return 0;
			case Upgrade_GENERAL:
				return 0;
			case Upgrade_GHOST_BLOCK:
				return info->GhostBlocks;
			case Upgrade_JUMP:
				return 0;
			case Upgrade_LASER:
				return info->Lasers;
			case Upgrade_LAVA_DRIP:
				return info->LavaDrips;
			case Upgrade_MOVING_BLOCK:
				return info->MovingBlocks;
			case Upgrade_PENDULUM:
				return info->Pendulums;
			case Upgrade_PINKY:
				return info->SpikeyGuys;
			case Upgrade_SERPENT:
				return info->Serpents;
			case Upgrade_SPEED:
				return 0;
			case Upgrade_SPIKE:
				return info->Spikes;
			case Upgrade_SPIKEY_GUY:
				return info->Boulders;
			case Upgrade_SPIKEY_LINE:
				return info->SpikeyLines;

			default:
				return 0;
		}
	}

	TileSet::operator TileSet*( const std::wstring &name )
	{
		return TileSets::NameLookup[ name ];
	}

	TileSet::TileSet()
	{
		InitializeInstanceFields();
		MakeNew();
	}

	std::shared_ptr<TileSet> TileSet::SetName( const std::wstring &Name )
	{
		this->Name = Name;
		return this;
	}

	std::shared_ptr<TileSet> TileSet::SetNameInGame( Localization::Words Name )
	{
		this->NameInGame = Name;
		return this;
	}

	std::shared_ptr<TileSet> TileSet::SetBackground( const std::wstring &background )
	{
		MyBackgroundType = BackgroundType::NameLookup[ background ];
		return this;
	}

	void TileSet::MakeNew()
	{
		IsLoaded = false;

		MyTileSetInfo = std::make_shared<TileSetInfo>();

		CustomStartEnd = false;

		Pillars = std::make_shared<BlockGroup>();
		Platforms = std::make_shared<BlockGroup>();
		Ceilings = std::make_shared<BlockGroup>();
		StartBlock = std::make_shared<BlockGroup>();
		EndBlock = std::make_shared<BlockGroup>();

		FixedWidths = false;
		ProvidesTemplates = false;

		StandInType = TileSets::None;

		ObstacleUpgrades = std::vector<Upgrade>();

		FlexibleHeight = false;
		HasCeiling = false;

		Name = _T( "" );
		MyPath = _T( "" );
		Guid = 0;

		Tint = Vector4( 1 );

		ScreenshotString = _T( "" );

		MyBackgroundType = BackgroundType::Random;

		CoinScoreColor = Color( 220, 255, 255 );
	}

	void TileSet::Read( const std::wstring &path )
	{
		MyPath = path;
		_Start();

		// Find path
		Tools::UseInvariantCulture();
		std::shared_ptr<FileStream> stream = 0;
		std::wstring original_path = path;
		try
		{
			stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		}
		catch ( ... )
		{
			try
			{
				path = Path::Combine( Globals::ContentDirectory, original_path );
				stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
			}
			catch ( ... )
			{
				try
				{
					path = Path::Combine( Globals::ContentDirectory, Path::Combine( _T( "DynamicLoad" ), original_path ) );
					stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
				}
				catch ( ... )
				{
					Tools::Log( std::wstring::Format( _T( "Attempting to load a .tileset file. Path <{0}> not found." ) ) );
				}
			}
		}


		std::shared_ptr<StreamReader> reader = std::make_shared<StreamReader>( stream );

		std::wstring line;

		line = reader->ReadLine();
		while ( line != _T( "" ) )
		{
			std::vector<std::wstring> bits = Tools::GetBitsFromLine( line );

			if ( bits.size() > 1 )
			{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
				var first = bits[ 0 ];

				// Is it a pillar?
				if ( first->Contains( _T( "Pillar_" ) ) )
				{
					ParseBlock( bits, first, Pillars );
				}
				// Is it a platform?
				else if ( first->Contains( _T( "Platform_" ) ) )
				{
					ParseBlock( bits, first, Platforms );
				}
				// Is it a ceiling?
				else if ( first->Contains( _T( "Ceiling_" ) ) )
				{
					HasCeiling = true;
					std::shared_ptr<CloudberryKingdom::PieceQuad> pq = ParseBlock( bits, first, Ceilings );
					pq->Data.BottomFlush = true;
				}
				// Is it a start piece?
				if ( first->Contains( _T( "Start_" ) ) )
				{
					ParseBlock( bits, first, StartBlock );
				}
				// Is it an end piece?
				if ( first->Contains( _T( "End_" ) ) )
				{
					ParseBlock( bits, first, EndBlock );
				}
				// Is it a moving block?
				else if ( first->Contains( _T( "MovingBlock_" ) ) )
				{
					ParseBlock( bits, first, MyTileSetInfo->MovingBlocks->Group );
				}
				// Is it an elevator block?
				else if ( first->Contains( _T( "Elevator_" ) ) )
				{
					ParseBlock( bits, first, MyTileSetInfo->Elevators->Group );
				}
				// Is it a pendulum block?
				else if ( first->Contains( _T( "Pendulum_" ) ) )
				{
					ParseBlock( bits, first, MyTileSetInfo->Pendulums->Group );
				}
				// Is it a falling block?
				else if ( first->Contains( _T( "FallingBlock_" ) ) )
				{
					ParseBlock( bits, first, MyTileSetInfo->FallingBlocks->Group );
				}
				// Is it a bouncy block?
				else if ( first->Contains( _T( "BouncyBlock_" ) ) )
				{
					ParseBlock( bits, first, MyTileSetInfo->BouncyBlocks->Group );
				}
				else
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//					switch (first)
//ORIGINAL LINE: case "sprite_anim":
					if ( first == _T( "sprite_anim" ) )
					{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
						var dict = Tools::GetLocations( bits, _T( "name" ), _T( "file" ), _T( "size" ), _T( "frames" ), _T( "frame_length" ), _T( "reverse_at_end" ) );

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
						var name = bits[ dict[ _T( "name" ) ] + 1 ];
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
						var file = bits[ dict[ _T( "file" ) ] + 1 ];

						std::shared_ptr<AnimationData_Texture> sprite_anim = 0;
						if ( dict->ContainsKey( _T( "frames" ) ) )
						{
							int start_frame = int::Parse( bits[ dict[ _T( "frames" ) ] + 1 ] );
							int end_frame;
							if ( bits[ dict[ _T( "frames" ) ] + 2 ][ 0 ] == L't' )
								end_frame = int::Parse( bits[ dict[ _T( "frames" ) ] + 3 ] );
							else
								end_frame = int::Parse( bits[ dict[ _T( "frames" ) ] + 2 ] );
							sprite_anim = std::make_shared<AnimationData_Texture>( file, start_frame, end_frame );
						}

						if ( dict->ContainsKey( _T( "frame_length" ) ) )
						{
							int frame_length = int::Parse( bits[ dict[ _T( "frame_length" ) ] + 1 ] );
							sprite_anim->Anims[ 0 ].Speed = 1 / frame_length;
						}

						Tools::TextureWad->Add( sprite_anim, name );


					}
//ORIGINAL LINE: case "BackgroundFile":
					else if ( first == _T( "BackgroundFile" ) )
					{
						std::shared_ptr<BackgroundTemplate> template_Renamed;
						try
						{
							template_Renamed = BackgroundType::NameLookup[ bits[ 1 ] ];
						}
						catch ( ... )
						{
							template_Renamed = std::make_shared<BackgroundTemplate>();
							template_Renamed->Name = bits[ 1 ];
						}

						MyBackgroundType = template_Renamed;


					}
//ORIGINAL LINE: case "Name":
					else if ( first == _T( "Name" ) )
					{
						Name = bits[ 1 ];
					}
					else
					{
						Tools::ReadLineToObj( MyTileSetInfo, bits );
					}
			}

			line = reader->ReadLine();
		}

		reader->Close();
		stream->Close();

		_Finish();
	}

	void TileSet::_Finish()
	{
		// Sort widths
		Pillars->SortWidths();
		Platforms->SortWidths();
		Ceilings->SortWidths();
		StartBlock->SortWidths();
		EndBlock->SortWidths();

		if ( MyTileSetInfo->Pendulums->Group->Dict.empty() )
			MyTileSetInfo->Pendulums->Group = PieceQuad::ElevatorGroup;
		if ( MyTileSetInfo->Elevators->Group->Dict.empty() )
			MyTileSetInfo->Elevators->Group = PieceQuad::ElevatorGroup;
		if ( MyTileSetInfo->FallingBlocks->Group->Dict.empty() )
			MyTileSetInfo->FallingBlocks->Group = PieceQuad::FallGroup;
		if ( MyTileSetInfo->BouncyBlocks->Group->Dict.empty() )
			MyTileSetInfo->BouncyBlocks->Group = PieceQuad::BouncyGroup;
		if ( MyTileSetInfo->MovingBlocks->Group->Dict.empty() )
			MyTileSetInfo->MovingBlocks->Group = PieceQuad::MovingGroup;

		MyTileSetInfo->Pendulums->Group->SortWidths();
		MyTileSetInfo->Elevators->Group->SortWidths();
		MyTileSetInfo->FallingBlocks->Group->SortWidths();
		MyTileSetInfo->MovingBlocks->Group->SortWidths();
		MyTileSetInfo->BouncyBlocks->Group->SortWidths();
	}

	void TileSet::_Start()
	{
		IsLoaded = true;
		CustomStartEnd = true;

		MyTileSetInfo->AllowTopOnlyBlocks = false;

		FixedWidths = true;
		ProvidesTemplates = true;
		MyBackgroundType = BackgroundType::None;

		MyTileSetInfo->Pendulums->Group = std::make_shared<BlockGroup>();
		MyTileSetInfo->Elevators->Group = std::make_shared<BlockGroup>();
		MyTileSetInfo->FallingBlocks->Group = std::make_shared<BlockGroup>();
		MyTileSetInfo->BouncyBlocks->Group = std::make_shared<BlockGroup>();
		MyTileSetInfo->MovingBlocks->Group = std::make_shared<BlockGroup>();
	}

	std::shared_ptr<PieceQuad> TileSet::ParseBlock( std::vector<std::wstring> &bits, const std::wstring &first, const std::shared_ptr<BlockGroup> &group )
	{
		// Get the block width
		std::shared_ptr<std::wstring> num_str = first.substr( first.find( _T( "_" ) ) + 1 );
		int width = int::Parse( num_str );

		// Get the rest of the information
		std::shared_ptr<CloudberryKingdom::PieceQuad> piecequad = ParseBlockLine( width, bits );
		group->Add( width, piecequad );

		return piecequad;
	}

	std::shared_ptr<PieceQuad> TileSet::ParseBlockLine( int width, std::vector<std::wstring> &bits )
	{
		std::shared_ptr<PieceQuad> c = std::make_shared<PieceQuad>();
		c->Init( 0, Tools::BasicEffect );

		bool IsTile = Tools::BitsHasBit( bits, _T( "tile" ) );

		if ( IsTile )
		{
			c->Data.RepeatWidth = 2000;
			c->Data.RepeatHeight = 2000;
			c->Data.UV_Multiples = Vector2( 0, 0 );
			c->Center.U_Wrap = c->Center.V_Wrap = true;
		}
		else
		{
			c->Data.RepeatWidth = 2000;
			c->Data.RepeatHeight = 2000;
			c->Data.UV_Multiples = Vector2( 1, 0 );
			c->Center.U_Wrap = c->Center.V_Wrap = false;

			c->FixedHeight = 0; // Flag to tell ParseExtra to set the height properly
		}

		ParseExtraBlockInfo( c, width, bits );

		return c;
	}

	void TileSet::ParseExtraBlockInfo( const std::shared_ptr<PieceQuad> &c, int width, std::vector<std::wstring> &bits )
	{
		c->Center.SetTextureOrAnim( bits[ 1 ] );
		//c.Center.TextureName = bits[1];

		//int tex_width = c.Center.MyTexture.Width;
		//int tex_height = c.Center.MyTexture.Height;
		int tex_width = c->Center.getTexWidth();
		int tex_height = c->Center.getTexHeight();

		for ( int i = 2; i < bits.size(); i++ )
		{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//			switch (bits[i])
//ORIGINAL LINE: case "upside_down":
			if ( bits[ i ] == _T( "upside_down" ) )
			{
					c->Data.UpsideDown = true;
			}
//ORIGINAL LINE: case "mirror":
			else if ( bits[ i ] == _T( "mirror" ) )
			{
					c->Data.Mirror = true;
			}
//ORIGINAL LINE: case "box_height":
			else if ( bits[ i ] == _T( "box_height" ) )
			{
					c->BoxHeight = 2 * float::Parse( bits[ i + 1 ] );
			}
//ORIGINAL LINE: case "width":
			else if ( bits[ i ] == _T( "width" ) )
			{
					c->Data.RepeatWidth = 2 * float::Parse( bits[ i + 1 ] );
			}
//ORIGINAL LINE: case "height":
			else if ( bits[ i ] == _T( "height" ) )
			{
					c->Data.RepeatHeight = 2 * float::Parse( bits[ i + 1 ] );
			}
//ORIGINAL LINE: case "left":
			else if ( bits[ i ] == _T( "left" ) )
			{
					c->Data.Center_BL_Shift.X = float::Parse( bits[ i + 1 ] );
			}
//ORIGINAL LINE: case "right":
			else if ( bits[ i ] == _T( "right" ) )
			{
					c->Data.Center_TR_Shift.X = float::Parse( bits[ i + 1 ] );
			}
//ORIGINAL LINE: case "top":
			else if ( bits[ i ] == _T( "top" ) )
			{
					float shift = float::Parse( bits[ i + 1 ] );
					c->Data.Center_TR_Shift.Y = shift;
					c->Data.Center_BL_Shift.Y = shift;
			}
		}

		// Extend the quad down to properly scale quad
		if ( c->FixedHeight == 0 )
		{
			float sprite_width = 2 * width + c->Data.Center_TR_Shift.X - c->Data.Center_BL_Shift.X;
			c->FixedHeight = sprite_width * static_cast<float>( tex_height ) / static_cast<float>( tex_width );
		}
	}

	std::shared_ptr<PieceQuad> TileSet::GetPieceTemplate( const std::shared_ptr<BlockBase> &block, const std::shared_ptr<Rand> &rnd )
	{
		return GetPieceTemplate( block, rnd, 0 );
	}

	std::shared_ptr<PieceQuad> TileSet::GetPieceTemplate( const std::shared_ptr<BlockBase> &block, const std::shared_ptr<Rand> &rnd, const std::shared_ptr<BlockGroup> &group )
	{
		if ( group == 0 )
		{
			if ( block->getBlockCore()->Ceiling )
				group = Ceilings;
			else if ( block->getBlockCore()->EndPiece )
				group = EndBlock;
			else if ( block->getBlockCore()->StartPiece )
				group = StartBlock;
			else
			{
				if ( block->getBox()->TopOnly && block->getBlockCore()->UseTopOnlyTexture )
				{
					group = Platforms;
					if ( group->Widths.empty() )
						group = Pillars;
				}
				else
					group = Pillars;
			}
		}

		// Get the block's info
		std::shared_ptr<CloudberryKingdom::AABox> box = block->getBox();
		std::shared_ptr<CloudberryKingdom::BlockData> core = block->getBlockCore();

		// Get the width of the block (accounting for possible rotations for Meatboy levels)
		float width = 0;
		if ( core->MyOrientation == PieceQuad::Orientation_ROTATE_RIGHT || core->MyOrientation == PieceQuad::Orientation_ROTATE_LEFT )
			width = box->Current->Size.Y;
		else
			width = box->Current->Size.X;

		int int_width = group->SnapWidthUp( width - .1f );

		// Get the piecequad template
		try
		{
			return group->Choose( int_width, rnd );
		}
		catch ( ... )
		{
			Tools::Log( std::wstring::Format( _T( "Could not find {0} of width {1} for tileset {2}" ), _T( "block" ), width, Name ) );
			return 0;
		}
	}

	void TileSet::InitializeInstanceFields()
	{
		StandInType = TileSets::None;
		ObstacleUpgrades = std::vector<Upgrade>();
		Tint = Vector4( 1 );
		CoinScoreColor = Color( 220, 255, 255 );
	}
}
