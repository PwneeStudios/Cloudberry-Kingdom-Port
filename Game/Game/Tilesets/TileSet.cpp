#include <global_header.h>

#include "Game/Tilesets/Tilesets/CloudberryKingdom.TileSets.h"
#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"

#include "Hacks/List.h"
#include "Hacks/Dict.h"
#include "Hacks/String.h"
#include "Hacks/Parse.h"

#include "Hacks/NET/FileStream.h"

namespace CloudberryKingdom
{

	void TileInfoBase::InitializeInstanceFields()
	{
		Icon = boost::make_shared<SpriteInfo>( boost::shared_ptr<TextureOrAnim>(), Vector2( 50, -1 ) );
		Icon_Big = 0;
	}

	boost::shared_ptr<TileInfoBase> TileSet::UpgradeToInfo( Upgrade upgrade, const boost::shared_ptr<TileSet> &tile )
	{
		boost::shared_ptr<TileSetInfo> info = tile->MyTileSetInfo;

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

	/*TileSet::operator boost::shared_ptr<TileSet> ( const std::wstring &name )
	{
		return TileSets::NameLookup[ name ];
	}*/

	boost::shared_ptr<TileSet> TileSet::Get( const std::wstring &name )
	{
		return TileSets::NameLookup[ name ];
	}

	TileSet::TileSet()
	{
		InitializeInstanceFields();
		MakeNew();
	}

	boost::shared_ptr<TileSet> TileSet::SetName( const std::wstring &Name )
	{
		this->Name = Name;
		return shared_from_this();
	}

	boost::shared_ptr<TileSet> TileSet::SetNameInGame( Localization::Words Name )
	{
		this->NameInGame = Name;
		return shared_from_this();
	}

	boost::shared_ptr<TileSet> TileSet::SetBackground( const std::wstring &background )
	{
		MyBackgroundType = BackgroundType::NameLookup[ background ];
		return shared_from_this();
	}

	void TileSet::MakeNew()
	{
		IsLoaded = false;

		MyTileSetInfo = boost::make_shared<TileSetInfo>();

		CustomStartEnd = false;

		Pillars = boost::make_shared<BlockGroup>();
		Platforms = boost::make_shared<BlockGroup>();
		Ceilings = boost::make_shared<BlockGroup>();
		StartBlock = boost::make_shared<BlockGroup>();
		EndBlock = boost::make_shared<BlockGroup>();

		FixedWidths = false;
		ProvidesTemplates = false;

		StandInType = TileSets::None;

		ObstacleUpgrades = std::vector<Upgrade>();

		FlexibleHeight = false;
		HasCeiling = false;

		Name = std::wstring( L"" );
		MyPath = std::wstring( L"" );
		Guid = 0;

		Tint = Vector4( 1 );

		ScreenshotString = std::wstring( L"" );

		MyBackgroundType = BackgroundType::Random;

		CoinScoreColor = Color( static_cast<unsigned char>( 220 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
	}

	void TileSet::Read( const std::wstring &path )
	{
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

		MyTileSetInfo->Pendulums->Group = boost::make_shared<BlockGroup>();
		MyTileSetInfo->Elevators->Group = boost::make_shared<BlockGroup>();
		MyTileSetInfo->FallingBlocks->Group = boost::make_shared<BlockGroup>();
		MyTileSetInfo->BouncyBlocks->Group = boost::make_shared<BlockGroup>();
		MyTileSetInfo->MovingBlocks->Group = boost::make_shared<BlockGroup>();
	}

	boost::shared_ptr<PieceQuad> TileSet::ParseBlock( std::vector<std::wstring> &bits, const std::wstring &first, const boost::shared_ptr<BlockGroup> &group )
	{
		// Get the block width
		std::wstring num_str = first.substr( first.find( std::wstring( L"_" ) ) + 1 );
		int width = 0; ParseInt( num_str, width );

		// Get the rest of the information
		boost::shared_ptr<CloudberryKingdom::PieceQuad> piecequad = ParseBlockLine( width, bits );
		group->Add( width, piecequad );

		return piecequad;
	}

	boost::shared_ptr<PieceQuad> TileSet::ParseBlockLine( int width, std::vector<std::wstring> &bits )
	{
		boost::shared_ptr<PieceQuad> c = boost::make_shared<PieceQuad>();
		c->Init( 0, Tools::BasicEffect );

		bool IsTile = Tools::BitsHasBit( bits, std::wstring( L"tile" ) );

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

	void TileSet::ParseExtraBlockInfo( const boost::shared_ptr<PieceQuad> &c, int width, std::vector<std::wstring> &bits )
	{
		c->Center.SetTextureOrAnim( bits[ 1 ] );
		//c.Center.TextureName = bits[1];

		//int tex_width = c.Center.MyTexture.Width;
		//int tex_height = c.Center.MyTexture.Height;
		int tex_width = c->Center.getTexWidth();
		int tex_height = c->Center.getTexHeight();

		for ( size_t i = 2; i < bits.size(); i++ )
		{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//			switch (bits[i])
//ORIGINAL LINE: case "upside_down":
			if ( bits[ i ] == std::wstring( L"upside_down" ) )
			{
					c->Data.UpsideDown = true;
			}
//ORIGINAL LINE: case "mirror":
			else if ( bits[ i ] == std::wstring( L"mirror" ) )
			{
					c->Data.Mirror = true;
			}
//ORIGINAL LINE: case "box_height":
			else if ( bits[ i ] == std::wstring( L"box_height" ) )
			{
					c->BoxHeight = 0; ParseFloat( bits[ i + 1 ], c->BoxHeight );
					c->BoxHeight = 2 * c->BoxHeight;
			}
//ORIGINAL LINE: case "width":
			else if ( bits[ i ] == std::wstring( L"width" ) )
			{
					c->Data.RepeatWidth = 0; ParseFloat( bits[ i + 1 ], c->Data.RepeatWidth );
					c->Data.RepeatWidth = 2 * c->Data.RepeatWidth;
			}
//ORIGINAL LINE: case "height":
			else if ( bits[ i ] == std::wstring( L"height" ) )
			{
					c->Data.RepeatHeight = 0; ParseFloat( bits[ i + 1 ], c->Data.RepeatHeight );
					c->Data.RepeatHeight = 2 * c->Data.RepeatHeight;
			}
//ORIGINAL LINE: case "left":
			else if ( bits[ i ] == std::wstring( L"left" ) )
			{
					c->Data.Center_BL_Shift.X = 0; ParseFloat( bits[ i + 1 ], c->Data.Center_BL_Shift.X );
			}
//ORIGINAL LINE: case "right":
			else if ( bits[ i ] == std::wstring( L"right" ) )
			{
					c->Data.Center_TR_Shift.X = 0; ParseFloat( bits[ i + 1 ], c->Data.Center_TR_Shift.X );
			}
//ORIGINAL LINE: case "top":
			else if ( bits[ i ] == std::wstring( L"top" ) )
			{
					float shift = 0; ParseFloat( bits[ i + 1 ], shift );
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

	boost::shared_ptr<PieceQuad> TileSet::GetPieceTemplate( const boost::shared_ptr<BlockBase> &block, const boost::shared_ptr<Rand> &rnd )
	{
		return GetPieceTemplate( block, rnd, 0 );
	}

	boost::shared_ptr<PieceQuad> TileSet::GetPieceTemplate( const boost::shared_ptr<BlockBase> &block, const boost::shared_ptr<Rand> &rnd, boost::shared_ptr<BlockGroup> group )
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
		boost::shared_ptr<CloudberryKingdom::AABox> box = block->getBox();
		boost::shared_ptr<CloudberryKingdom::BlockData> core = block->getBlockCore();

		// Get the width of the block (accounting for possible rotations for Meatboy levels)
		float width = 0;
		if ( core->MyOrientation == PieceQuad::Orientation_ROTATE_RIGHT || core->MyOrientation == PieceQuad::Orientation_ROTATE_LEFT )
			width = box->Current->Size.Y;
		else
			width = box->Current->Size.X;

		int int_width = group->SnapWidthUp( width - .1f );

		// Get the piecequad template
		if ( Contains( group->Dict, int_width ) )
		{
			return group->Choose( int_width, rnd );
		}
		else
		{
			Tools::Log( Format( _T( "Could not find %ls of width %f for tileset %ls" ), std::wstring( L"block" ), width, Name.c_str() ) );
			return 0;
		}
	}

	void TileSet::InitializeInstanceFields()
	{
		StandInType = TileSets::None;
		ObstacleUpgrades = std::vector<Upgrade>();
		Tint = Vector4( 1 );
		CoinScoreColor = Color( static_cast<unsigned char>( 220 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
	}
}
