#include <global_header.h>

#include "Hacks/List.h"
#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"
#include "Game/Tilesets/Tilesets/CloudberryKingdom.TileSets.h"

namespace CloudberryKingdom
{

	boost::shared_ptr<TileSet> TileSets::Load_Cloud()
	{
		boost::shared_ptr<CloudberryKingdom::TileSet> t = GetOrMakeTileset( std::wstring( L"Cloud" ) );
		boost::shared_ptr<CloudberryKingdom::TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = std::wstring( L"cloud" );

	t->Pillars->Add( boost::make_shared<PieceQuad>( 50, std::wstring( L"pillar_cloud_50" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 100, std::wstring( L"pillar_cloud_100" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 150, std::wstring( L"pillar_cloud_150" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 250, std::wstring( L"pillar_cloud_250" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 300, std::wstring( L"pillar_cloud_300" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 600, std::wstring( L"pillar_cloud_600" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 1000, std::wstring( L"pillar_cloud_1000" ), -15.f, 15.f, 3.f ) );

	t->StartBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_cloud" ), -550.f, 135.f, 1450.f ) );
	t->EndBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_cloud" ), -15.f, 670.f, 1450.f ) );

	info->ShiftStartDoor = 30;
	info->ShiftStartBlock = Vector2( 120, 0 );

	sprite_anim( std::wstring( L"door_cloud" ), std::wstring( L"door_cloud" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"door_cloud" ) );
	info->Doors->Sprite->Size = Vector2( 275, -1 );
	info->Doors->Sprite->Offset = Vector2( -140, 7 );
	info->Doors->ShiftStart = Vector2( 0, 190 );

	info->Walls->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"pillar_cloud_1000" ) );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4573 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = TextureOrAnim::Get( std::wstring( L"Flow_cave_1" ) );
	info->LavaDrips->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Flow_cave_2" ) );
	info->LavaDrips->Line_Renamed->End2 = TextureOrAnim::Get( std::wstring( L"Flow_Cave_3" ) );

	info->Lasers->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Laser_Cloud" ) );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( std::wstring( L"fblock_cloud" ), std::wstring( L"fblock_cloud" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( boost::make_shared<PieceQuad>( 103, std::wstring( L"fblock_cloud" ), -3.f, 3.f, 2.f ) );

	sprite_anim( std::wstring( L"Bouncy_cloud" ), std::wstring( L"Bouncy_cloud" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( boost::make_shared<PieceQuad>( 124, std::wstring( L"bouncy_cloud" ), -6.f, 6.f, 13.f ) );

	sprite_anim( std::wstring( L"flame_cloud" ), std::wstring( L"firespinner_flame_cloud" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = TextureOrAnim::Get( std::wstring( L"flame_cloud" ) );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = TextureOrAnim::Get( std::wstring( L"firespinner_base_cloud" ) );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;

	info->GhostBlocks->Sprite = TextureOrAnim::Get( std::wstring( L"ghostblock_cloud" ) );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"movingblock_cloud_190" ), -4.f, 13.f, 10.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"movingblock_cloud_135" ), -4.f, 4.f, 10.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"movingblock_cloud_80" ), -1.f, 1.f, 2.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"movingblock_cloud_40" ), -1.f, 1.f, 2.f ) );

	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Cloud_40" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Cloud_80" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Cloud_135" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Cloud_190" ), -1.f, 1.f, 1.f ) );

	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Cloud_40" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Cloud_80" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Cloud_135" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Cloud_190" ), -1.f, 1.f, 1.f ) );

	sprite_anim( std::wstring( L"Serpent_Cloud" ), std::wstring( L"Serpent_Cloud" ), 1, 2, 8 );
	info->Serpents->Serpent_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Cloud" ) );
	sprite_anim( std::wstring( L"Serpent_Fish_Cloud" ), std::wstring( L"Serpent_Fish_Cloud" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Fish_Cloud" ) );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Spikes->Spike_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"spike_cloud" ) );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = TextureOrAnim::Get( std::wstring( L"spike_base_cloud_1" ) );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_spikey_cloud" ) );
	info->Boulders->Ball->Size = Vector2( 150, -1 );
	info->Boulders->Radius = 120;
	info->Boulders->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"cloud_chain" ) );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;

	info->Boulders->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Boulder_Cloud" ) );
	info->Boulders->Ball->Size = Vector2( 200, -1 );
	info->Boulders->Radius = 140;
	info->Boulders->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Rope_Cloud" ) );
	info->Boulders->Chain->RepeatWidth = 1900;
	info->Boulders->Chain->Width = 55;

	info->SpikeyGuys->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_spikey_cloud" ) );
	info->SpikeyGuys->Ball->Size = Vector2( 150, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 8 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 114;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"cloud_chain" ) );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyLines->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_Cloud" ) );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( std::wstring( L"blob_cloud" ), std::wstring( L"blob_cloud" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = TextureOrAnim::Get( std::wstring( L"blob_cloud" ) );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = TextureOrAnim::Get( std::wstring( L"BlobGoo5" ) );

	info->Clouds->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"cloud_cloud" ) );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 104 );

	info->Coins->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"coin_blue" ) );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;

		t->_Finish();

		return t;
	}

	boost::shared_ptr<TileSet> TileSets::Load_Castle()
	{
		boost::shared_ptr<TileSet> t = GetOrMakeTileset( std::wstring( L"Castle" ) );
		boost::shared_ptr<TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = std::wstring( L"castle" );

	t->HasCeiling = true;

	t->Pillars->Add( boost::make_shared<PieceQuad>( 50, std::wstring( L"pillar_castle_50" ), -15.f, 15.f, 1.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 100, std::wstring( L"pillar_castle_100" ), -15.f, 15.f, 1.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 150, std::wstring( L"pillar_castle_150" ), -15.f, 15.f, 1.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 250, std::wstring( L"pillar_castle_250" ), -15.f, 15.f, 1.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 300, std::wstring( L"pillar_castle_300" ), -15.f, 15.f, 1.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 600, std::wstring( L"pillar_castle_600" ), -15.f, 15.f, 1.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 1000, std::wstring( L"pillar_castle_1000" ), -15.f, 15.f, 1.f ) );

	t->Ceilings->Add( boost::make_shared<PieceQuad>( 50, std::wstring( L"pillar_castle_50" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 100, std::wstring( L"pillar_castle_100" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 150, std::wstring( L"pillar_castle_150" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 250, std::wstring( L"pillar_castle_250" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 300, std::wstring( L"pillar_castle_300" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 600, std::wstring( L"pillar_castle_600" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 1000, std::wstring( L"pillar_castle_1000" ), -20.f, 20.f, 0.f, true ) );

	//t.StartBlock.Add(new PieceQuad(400, "wall_castle", -670, 15, 1407));
	//t.EndBlock.Add(new PieceQuad(400, "wall_castle", -15, 670, 1407));
	t->StartBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_castle" ), -950.f, 15.f, 1670.f ) );
	t->EndBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_castle" ), -45.f, 920.f, 1670.f ) );

	info->ShiftStartDoor = 0;
	info->ShiftStartBlock = Vector2( 100, 0 );

	sprite_anim( std::wstring( L"door_castle" ), std::wstring( L"door_castle" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"door_castle" ) );
	info->Doors->Sprite->Size = Vector2( 450, 250 );
	info->Doors->Sprite->Offset = Vector2( -210, 35 );
	info->Doors->ShiftStart = Vector2( 0, 190 );
	info->Doors->SizePadding = Vector2( 10, 0 );

	info->Walls->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"pillar_castle_1000" ) );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4635 );
	info->Walls->Sprite->Size = Vector2( 1300, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4815 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = TextureOrAnim::Get( std::wstring( L"Flow_Castle_1" ) );
	info->LavaDrips->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Flow_Castle_2" ) );
	info->LavaDrips->Line_Renamed->End2 = TextureOrAnim::Get( std::wstring( L"Flow_Castle_3" ) );
	info->LavaDrips->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Flow_Icon_Castle" ) );

	info->Lasers->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Laser_Castle" ) );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );
	info->Lasers->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Icon_Laser" ) );

	sprite_anim( std::wstring( L"fblock_castle" ), std::wstring( L"fblock_castle" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( boost::make_shared<PieceQuad>( 103, std::wstring( L"fblock_castle" ), -3.f, 3.f, 2.f ) );
	info->FallingBlocks->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"fblock_castle" ) );
	info->FallingBlocks->Icon->Size = Vector2( 40, -1 );

	sprite_anim( std::wstring( L"Bouncy_castle" ), std::wstring( L"Bouncy_castle" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( boost::make_shared<PieceQuad>( 124, std::wstring( L"bouncy_castle" ), -6.f, 6.f, 13.f ) );
	info->BouncyBlocks->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Bouncy_Castle" ) );

	sprite_anim( std::wstring( L"flame_castle" ), std::wstring( L"firespinner_flame_castle_v1" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = TextureOrAnim::Get( std::wstring( L"flame_castle" ) );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = TextureOrAnim::Get( std::wstring( L"firespinner_base_castle_2" ) );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;
	info->Spinners->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Icon_FireSpinner" ) );

	info->GhostBlocks->Sprite = TextureOrAnim::Get( std::wstring( L"ghostblock_castle" ) );
	info->GhostBlocks->Shift = Vector2( 0, -15 );
	info->GhostBlocks->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Ghostblock_Castle" ) );
	info->GhostBlocks->Icon->Size = Vector2( 40, -1 );

	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"movingblock_castle_190" ), -1.f, 1.f, 25.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"movingblock_castle_135" ), -1.f, 1.f, 25.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"movingblock_castle_80" ), -1.f, 1.f, 5.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"movingblock_castle_40" ), -1.f, 1.f, 5.f ) );
	info->MovingBlocks->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"MovingBlock_Castle_40" ) );
	info->MovingBlocks->Icon->Size = Vector2( 40, -1 );
	info->MovingBlocks->Icon_Big = boost::make_shared<SpriteInfo>( boost::shared_ptr<TextureOrAnim>() );
	info->MovingBlocks->Icon_Big->Sprite = TextureOrAnim::Get( std::wstring( L"MovingBlock_Castle_135" ) );
	info->MovingBlocks->Icon_Big->Size = Vector2( 40, -1 );

	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Castle_40" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Castle_80" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Castle_135" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Castle_190" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Elevator_Castle_80" ) );

	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Castle_40" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Castle_80" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Castle_135" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Castle_190" ), -1.f, 1.f, 1.f ) );
	//info.Pendulums.Icon.Sprite = "Elevator_Castle_80";
	info->Pendulums->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Pendulum_Icon_Castle" ) );

	sprite_anim( std::wstring( L"Serpent_Castle" ), std::wstring( L"Serpent_Castle" ), 1, 2, 8 );
	//sprite_anim("Serpent_Castle", "SerpentHead_Castle", 1, 2, 8);
	info->Serpents->Serpent_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Castle" ) );
	sprite_anim( std::wstring( L"Serpent_Fish_Castle" ), std::wstring( L"Serpent_Fish_Castle" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Fish_Castle" ) );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );
	info->Serpents->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"SerpentHead_Castle_1" ) );

	info->Spikes->Spike_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"spike_castle" ) );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = TextureOrAnim::Get( std::wstring( L"spike_base_castle" ) );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;
	info->Spikes->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Spike_Castle" ) );
	info->Spikes->Icon->Size = Vector2( 25, -1 );

	info->Boulders->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_castle_v1" ) );
	info->Boulders->Ball->Size = Vector2( 150, -1 );
	info->Boulders->Radius = 106;
	info->Boulders->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_chain_castle" ) );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;
	info->Boulders->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_Castle_v1" ) );

	info->SpikeyGuys->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_buzzsaw_yellow_castle" ) );
	info->SpikeyGuys->Ball->Size = Vector2( 190, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 0 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->RotateSpeed = -.15f;
	info->SpikeyGuys->Radius = 130;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_chain_castle" ) );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;
	info->SpikeyGuys->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Buzzsaw_Yellow_Castle" ) );

	info->SpikeyLines->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_Castle_v2" ) );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;
	info->SpikeyLines->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_Castle_v2" ) );

	sprite_anim( std::wstring( L"blob_castle" ), std::wstring( L"blob_castle_v1" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = TextureOrAnim::Get( std::wstring( L"blob_castle" ) );
	info->Blobs->Body->Size = Vector2( 137, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = TextureOrAnim::Get( std::wstring( L"BlobGoo5" ) );
	info->Blobs->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Blob_Castle" ) );

	info->Clouds->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"cloud_castle" ) );
	info->Clouds->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Cloud_Castle" ) );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 355 );
	info->Fireballs->Icon->Sprite = TextureOrAnim::Get( std::wstring( L"Icon_Fireball" ) );

	info->Coins->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"coin_blue" ) );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = true;
	info->ObstacleCutoff = 70;

		t->_Finish();

		return t;
	}

	boost::shared_ptr<TileSet> TileSets::Load_Sea()
	{
		boost::shared_ptr<TileSet> t = GetOrMakeTileset( std::wstring( L"Sea" ) );
		boost::shared_ptr<TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = std::wstring( L"sea" );

	t->Pillars->Add( boost::make_shared<PieceQuad>( 50, std::wstring( L"pillar_sea_50" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 100, std::wstring( L"pillar_sea_100" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 150, std::wstring( L"pillar_sea_150" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 250, std::wstring( L"pillar_sea_250" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 300, std::wstring( L"pillar_sea_300" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 600, std::wstring( L"pillar_sea_600" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 1000, std::wstring( L"pillar_sea_1000" ), -15.f, 15.f, 3.f ) );

	t->StartBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_sea" ), -670.f, 15.f, 1420.f ) );
	t->EndBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_sea" ), -55.f, 630.f, 1420.f ) );

	info->ShiftStartDoor = -140;
	info->ShiftStartBlock = Vector2( 320, 0 );

	sprite_anim( std::wstring( L"door_sea" ), std::wstring( L"door_sea" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"door_sea" ) );
	info->Doors->Sprite->Size = Vector2( 270, -1 );
	info->Doors->Sprite->Offset = Vector2( -140, 38 );
	info->Doors->ShiftStart = Vector2( 0, 190 );

	info->Walls->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"pillar_sea_1000" ) );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4550 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = TextureOrAnim::Get( std::wstring( L"Flow_Sea_1" ) );
	info->LavaDrips->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Flow_Sea_2" ) );
	info->LavaDrips->Line_Renamed->End2 = TextureOrAnim::Get( std::wstring( L"Flow_Sea_3" ) );

	info->Lasers->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Laser_Sea" ) );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( std::wstring( L"fblock_sea" ), std::wstring( L"fblock_sea" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( boost::make_shared<PieceQuad>( 110, std::wstring( L"fblock_sea" ), -3.f, 3.f, 2.f ) );

	sprite_anim( std::wstring( L"Bouncy_sea" ), std::wstring( L"Bouncy_Cloud" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( boost::make_shared<PieceQuad>( 124, std::wstring( L"bouncy_sea" ), -6.f, 6.f, 13.f, true) );

	sprite_anim( std::wstring( L"flame_Sea" ), std::wstring( L"firespinner_flame_Sea" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = TextureOrAnim::Get( std::wstring( L"flame_Sea" ) );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = TextureOrAnim::Get( std::wstring( L"firespinner_gear_dkpurp" ) );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;

	info->GhostBlocks->Sprite = TextureOrAnim::Get( std::wstring( L"ghostblock_sea" ) );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"movingblock_sea_190" ), -1.f, 1.f, 12.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"movingblock_sea_135" ), -1.f, 1.f, 12.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"movingblock_sea_80" ), -1.f, 1.f, 4.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"movingblock_sea_40" ), -1.f, 1.f, 4.f ) );

	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Sea_40" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Sea_80" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Sea_135" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Sea_190" ), -1.f, 1.f, 1.f ) );

	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Sea_40" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Sea_80" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Sea_135" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Sea_190" ), -1.f, 1.f, 1.f ) );

	sprite_anim( std::wstring( L"Serpent_Sea" ), std::wstring( L"Serpent_Sea" ), 1, 2, 8 );
	info->Serpents->Serpent_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Sea" ) );
	sprite_anim( std::wstring( L"Serpent_Fish_Sea" ), std::wstring( L"Serpent_Fish_Sea" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Fish_Sea" ) );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Spikes->Spike_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Spike_Sea_2" ) );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = TextureOrAnim::Get( std::wstring( L"spike_base_sea_1" ) );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Size = Vector2( 170, -1 );
	info->Boulders->Radius = 120;
	info->Boulders->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Boulder_Cloud" ) );
	info->Boulders->Ball->Size = Vector2( 200, -1 );
	info->Boulders->Radius = 140;
	info->Boulders->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Rope_Cloud" ) );
	info->Boulders->Chain->RepeatWidth = 1900;
	info->Boulders->Chain->Width = 55;

	info->SpikeyGuys->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_Sea" ) );
	info->SpikeyGuys->Ball->Size = Vector2( 170, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 9 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 124;
	info->SpikeyGuys->RotateOffset = -1.95f;
	info->SpikeyGuys->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_chain_sea" ) );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyLines->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_Sea" ) );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( std::wstring( L"blob_sea" ), std::wstring( L"blob_sea" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = TextureOrAnim::Get( std::wstring( L"blob_sea" ) );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = TextureOrAnim::Get( std::wstring( L"BlobGoo5" ) );

	info->Clouds->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"cloud_sea" ) );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 132 );

	//info.Coins.Sprite.Sprite = "coin_blue";
	info->Coins->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"CoinShimmer" ) );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;
	info->ObstacleCutoff = 200;

		t->_Finish();

		return t;
	}

	boost::shared_ptr<TileSet> TileSets::Load_Hills()
	{
		boost::shared_ptr<TileSet> t = GetOrMakeTileset( std::wstring( L"Hills" ) );
		boost::shared_ptr<TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = std::wstring( L"hills" );

	t->Pillars->Add( boost::make_shared<PieceQuad>( 50, std::wstring( L"pillar_hills_50" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 100, std::wstring( L"pillar_hills_100" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 150, std::wstring( L"pillar_hills_150" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 250, std::wstring( L"pillar_hills_250" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 300, std::wstring( L"pillar_hills_300" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 600, std::wstring( L"pillar_hills_600" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 1000, std::wstring( L"pillar_hills_1000" ), -15.f, 15.f, 3.f ) );

	t->StartBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_hills" ), -880.f, 40.f, 1650.f ) );
	t->EndBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_hills" ), -40.f, 880.f, 1650.f ) );

	info->ShiftStartDoor = -140;
	info->ShiftStartBlock = Vector2( 200, 0 );

	sprite_anim( std::wstring( L"door_hills" ), std::wstring( L"door_hills" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"door_hills" ) );
	info->Doors->Sprite->Size = Vector2( 305, -1 );
	info->Doors->Sprite->Offset = Vector2( -140, 33 );
	info->Doors->ShiftStart = Vector2( 0, 190 );

	info->Walls->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"pillar_hills_1000" ) );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4615 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = TextureOrAnim::Get( std::wstring( L"Flow_cave_1" ) );
	info->LavaDrips->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Flow_cave_2" ) );
	info->LavaDrips->Line_Renamed->End2 = TextureOrAnim::Get( std::wstring( L"Flow_Cave_3" ) );

	info->Lasers->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Laser_Hills" ) );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( std::wstring( L"fblock_hills" ), std::wstring( L"fblock_hills" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( boost::make_shared<PieceQuad>( 110, std::wstring( L"fblock_hills" ), -3.f, 3.f, 2.f ) );

	sprite_anim( std::wstring( L"Bouncy_hills" ), std::wstring( L"Bouncy_hills" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( boost::make_shared<PieceQuad>( 124, std::wstring( L"bouncy_hills" ), -15.f, 15.f, 13.f ) );

	sprite_anim( std::wstring( L"flame_Hills" ), std::wstring( L"firespinner_flame_Hills" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = TextureOrAnim::Get( std::wstring( L"flame_Hills" ) );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = TextureOrAnim::Get( std::wstring( L"firespinner_base_hills" ) );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;

	info->GhostBlocks->Sprite = TextureOrAnim::Get( std::wstring( L"ghostblock_hills" ) );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"movingblock_hills_190" ), -1.f, 1.f, 7.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"movingblock_hills_135" ), -1.f, 1.f, 7.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"movingblock_hills_80" ), -1.f, 1.f, 3.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"movingblock_hills_40" ), -1.f, 1.f, 3.f ) );

	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Hills_40" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Hills_80" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Hills_135" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Hills_190" ), -1.f, 1.f, 1.f ) );

	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Hills_40" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Hills_80" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Hills_135" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Hills_190" ), -1.f, 1.f, 1.f ) );

	sprite_anim( std::wstring( L"Serpent_Hills" ), std::wstring( L"Serpent_Castle" ), 1, 2, 5 );
	info->Serpents->Serpent_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Hills" ) );
	sprite_anim( std::wstring( L"Serpent_Fish_Hills" ), std::wstring( L"Serpent_Fish_Castle" ), 1, 2, 8 );
	info->Serpents->Fish->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Fish_Hills" ) );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Spikes->Spike_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"spike_hills" ) );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = TextureOrAnim::Get( std::wstring( L"spike_base_hills_1" ) );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_boulder_hills" ) );
	info->Boulders->Ball->Size = Vector2( 200, -1 );
	info->Boulders->Radius = 140;
	info->Boulders->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_rope_hills" ) );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;

	info->SpikeyGuys->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_spikey_hills" ) );
	info->SpikeyGuys->Ball->Size = Vector2( 150, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 8 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 116;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_chain_hills" ) );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyLines->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_Hills" ) );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( std::wstring( L"blob_hills" ), std::wstring( L"blob_hills" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = TextureOrAnim::Get( std::wstring( L"blob_hills" ) );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = TextureOrAnim::Get( std::wstring( L"BlobGoo5" ) );

	info->Clouds->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"cloud_hills" ) );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 0 );

	info->Coins->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"coin_blue" ) );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;

		t->_Finish();

		return t;
	}

	boost::shared_ptr<TileSet> TileSets::Load_Forest()
	{
		boost::shared_ptr<TileSet> t = GetOrMakeTileset( std::wstring( L"Forest" ) );
		boost::shared_ptr<TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = std::wstring( L"forest" );

	t->Pillars->Add( boost::make_shared<PieceQuad>( 50, std::wstring( L"pillar_forest_50" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 100, std::wstring( L"pillar_forest_100" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 150, std::wstring( L"pillar_forest_150" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 250, std::wstring( L"pillar_forest_250" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 300, std::wstring( L"pillar_forest_300" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 600, std::wstring( L"pillar_forest_600" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 1000, std::wstring( L"pillar_forest_1000" ), -15.f, 15.f, 3.f ) );

	t->StartBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_forest" ), -670.f, 15.f, 1500.f ) );
	t->EndBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_forest" ), -15.f, 670.f, 1500.f ) );

	info->ShiftStartDoor = 25;
	info->ShiftStartBlock = Vector2( 50, 0 );

	sprite_anim( std::wstring( L"door_forest" ), std::wstring( L"door_forest" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"door_forest" ) );
	info->Doors->Sprite->Size = Vector2( 296, -1 );
	info->Doors->Sprite->Offset = Vector2( -140, 35 );
	info->Doors->ShiftStart = Vector2( 0, 190 );

	info->Walls->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"pillar_forest_1000" ) );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4650 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = TextureOrAnim::Get( std::wstring( L"Flow_Sea_1" ) );
	info->LavaDrips->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Flow_Sea_2" ) );
	info->LavaDrips->Line_Renamed->End2 = TextureOrAnim::Get( std::wstring( L"Flow_Sea_3" ) );

	info->Lasers->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Laser_Forest" ) );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( std::wstring( L"fblock_forest" ), std::wstring( L"fblock_forest" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( boost::make_shared<PieceQuad>( 103, std::wstring( L"fblock_forest" ), -3.f, 3.f, 2.f ) );

	sprite_anim( std::wstring( L"Bouncy_Forest" ), std::wstring( L"Bouncy_Forest" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( boost::make_shared<PieceQuad>( 124, std::wstring( L"bouncy_Forest" ), -6.f, 6.f, 13.f ) );

	sprite_anim( std::wstring( L"flame_forest" ), std::wstring( L"firespinner_flame_forest" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = TextureOrAnim::Get( std::wstring( L"flame_forest" ) );
	info->Spinners->Flame->Size = Vector2( 47, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->Base->Sprite = TextureOrAnim::Get( std::wstring( L"firespinner_base_forest_1" ) );
	info->Spinners->Base->Size = Vector2( 75, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -45 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 45;
	info->Spinners->TopOffset = -40;

	info->GhostBlocks->Sprite = TextureOrAnim::Get( std::wstring( L"ghostblock_forest_1" ) );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"movingblock_forest_190_v2" ), -1.f, 1.f, 1.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 150, std::wstring( L"movingblock_forest_150" ), -1.f, 1.f, 1.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"movingblock_forest_135_v2" ), -1.f, 1.f, 1.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"movingblock_forest_80_v2" ), -1.f, 1.f, 1.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"movingblock_forest_40_v2" ), -1.f, 1.f, 1.f ) );

	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Forest_40" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Forest_80" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Forest_135" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Forest_190" ), -1.f, 1.f, 1.f ) );

	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Forest_40" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Forest_80" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Forest_135" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Forest_190" ), -1.f, 1.f, 1.f ) );

	sprite_anim( std::wstring( L"Serpent_Forest" ), std::wstring( L"Serpent_Forest" ), 1, 2, 8 );
	info->Serpents->Serpent_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Forest" ) );
	sprite_anim( std::wstring( L"Serpent_Fish_Forest" ), std::wstring( L"Serpent_Fish_Forest" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Fish_Forest" ) );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Spikes->Spike_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"spike_forest" ) );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = TextureOrAnim::Get( std::wstring( L"spike_base_forest_1" ) );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_spikey_forest" ) );
	info->Boulders->Ball->Size = Vector2( 160, -1 );
	info->Boulders->Radius = 120;
	info->Boulders->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_chain_forest" ) );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;

	info->SpikeyGuys->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_spikey_forest" ) );
	info->SpikeyGuys->Ball->Size = Vector2( 150, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, -22 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 130;
	info->SpikeyGuys->RotateOffset = .05f;
	info->SpikeyGuys->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_chain_forest" ) );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyGuys->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_buzzsaw_forest" ) );
	info->SpikeyGuys->Ball->Size = Vector2( 230, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 0 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->RotateSpeed = -.15f;
	info->SpikeyGuys->Radius = 130;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_chain_forest" ) );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyLines->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_Forest" ) );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, -10 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( std::wstring( L"blob_forest" ), std::wstring( L"blob_forest" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = TextureOrAnim::Get( std::wstring( L"blob_forest" ) );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->GooSprite = TextureOrAnim::Get( std::wstring( L"BlobGoo3" ) );

	info->Clouds->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"cloud_forest" ) );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 192.5f );

	info->Coins->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"coin_blue" ) );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;
	info->ObstacleCutoff = 70;

		t->_Finish();

		return t;
	}

	boost::shared_ptr<TileSet> TileSets::Load_Cave()
	{
		boost::shared_ptr<TileSet> t = GetOrMakeTileset( std::wstring( L"Cave" ) );
		boost::shared_ptr<TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = std::wstring( L"cave" );

	t->HasCeiling = true;

	t->Pillars->Add( boost::make_shared<PieceQuad>( 50, std::wstring( L"pillar_cave_50" ), -15.f, 15.f, 3.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 100, std::wstring( L"pillar_cave_100" ), -15.f, 15.f, 12.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 150, std::wstring( L"pillar_cave_150" ), -15.f, 15.f, 0.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 250, std::wstring( L"pillar_cave_250" ), -15.f, 15.f, 0.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 300, std::wstring( L"pillar_cave_300" ), -15.f, 15.f, 0.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 600, std::wstring( L"pillar_cave_600" ), -15.f, 15.f, 0.f ) );
	t->Pillars->Add( boost::make_shared<PieceQuad>( 1000, std::wstring( L"pillar_cave_1000" ), -15.f, 15.f, 0.f ) );

	t->Ceilings->Add( boost::make_shared<PieceQuad>( 50, std::wstring( L"pillar_cave_50" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 100, std::wstring( L"pillar_cave_100" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 150, std::wstring( L"pillar_cave_150" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 250, std::wstring( L"pillar_cave_250" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 300, std::wstring( L"pillar_cave_300" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 600, std::wstring( L"pillar_cave_600" ), -20.f, 20.f, 0.f, true ) );
	t->Ceilings->Add( boost::make_shared<PieceQuad>( 1000, std::wstring( L"pillar_cave_1000" ), -20.f, 20.f, 0.f, true ) );

	//t.Pillars.Add(new PieceQuad(50, "pillar_cave_50_v3", -15, 15, 3));
	//t.Pillars.Add(new PieceQuad(100, "pillar_cave_100_v3", -15, 15, 12));
	//t.Pillars.Add(new PieceQuad(150, "pillar_cave_150_v3", -15, 15, 0));
	//t.Pillars.Add(new PieceQuad(250, "pillar_cave_250_v3", -15, 15, 0));
	//t.Pillars.Add(new PieceQuad(300, "pillar_cave_300_v3", -15, 15, 0));
	//t.Pillars.Add(new PieceQuad(600, "pillar_cave_600_v3", -15, 15, 0));
	//t.Pillars.Add(new PieceQuad(1000, "pillar_cave_1000_v3", -15, 15, 0));

	//t.Ceilings.Add(new PieceQuad(50, "pillar_cave_50_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(100, "pillar_cave_100_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(150, "pillar_cave_150_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(250, "pillar_cave_250_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(300, "pillar_cave_300_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(600, "pillar_cave_600_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(1000, "pillar_cave_1000_v3", -20, 20, 0, true));

	t->StartBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_cave" ), -650.f, 120.f, 1548.f ) );
	t->EndBlock->Add( boost::make_shared<PieceQuad>( 400, std::wstring( L"wall_cave" ), -34.f, 736.f, 1548.f ) );

	info->ShiftStartDoor = -180;
	info->ShiftStartBlock = Vector2( 300, 0 );

	sprite_anim( std::wstring( L"door_cave" ), std::wstring( L"door_cave" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"door_cave" ) );
	info->Doors->Sprite->Size = Vector2( 500, -1 );
	info->Doors->Sprite->Offset = Vector2( -250, 135 );
	info->Doors->ShiftStart = Vector2( 0, 190 );
	info->Doors->SizePadding = Vector2( 25, 0 );

	info->Walls->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"pillar_cave_1000" ) );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4550 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = TextureOrAnim::Get( std::wstring( L"Flow_cave_1" ) );
	info->LavaDrips->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Flow_cave_2" ) );
	info->LavaDrips->Line_Renamed->End2 = TextureOrAnim::Get( std::wstring( L"Flow_Cave_3" ) );

	info->Lasers->Line_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Laser_Cave" ) );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( std::wstring( L"fblock_cave" ), std::wstring( L"fblock_cave" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( boost::make_shared<PieceQuad>( 103, std::wstring( L"fblock_cave" ), -3.f, 3.f, 2.f ) );

	sprite_anim( std::wstring( L"Bouncy_Forest" ), std::wstring( L"Bouncy_Forest" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( boost::make_shared<PieceQuad>( 124, std::wstring( L"bouncy_Forest" ), -6.f, 6.f, 13.f ) );

	sprite_anim( std::wstring( L"Bouncy_cave" ), std::wstring( L"Bouncy_cave" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( boost::make_shared<PieceQuad>( 124, std::wstring( L"bouncy_cave" ), -6.f, 6.f, 13.f ) );

	sprite_anim( std::wstring( L"flame_cave" ), std::wstring( L"firespinner_flame_cloud" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = TextureOrAnim::Get( std::wstring( L"flame_cave" ) );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = TextureOrAnim::Get( std::wstring( L"firespinner_base_cloud" ) );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;

	info->GhostBlocks->Sprite = TextureOrAnim::Get( std::wstring( L"ghostblock_cave" ) );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"movingblock_cave_190" ), -1.f, 1.f, 7.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"movingblock_cave_135" ), -1.f, 1.f, 7.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"movingblock_cave_80" ), -1.f, 1.f, 3.f ) );
	info->MovingBlocks->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"movingblock_cave_40" ), -1.f, 1.f, 3.f ) );

	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Cave_40" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Cave_80" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Cave_135" ), -1.f, 1.f, 1.f ) );
	info->Elevators->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Cave_190" ), -1.f, 1.f, 1.f ) );
	//info.Elevators.Group.Add(40, "Cave_40_v2", -1, 1, 1));
	//info.Elevators.Group.Add(80, "Cave_80_v2", -1, 1, 1));
	//info.Elevators.Group.Add(135, "Cave_135_v2", -1, 1, 1));
	//info.Elevators.Group.Add(190, "Cave_190_v2", -1, 1, 1));

	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 40, std::wstring( L"Elevator_Cave_40" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 80, std::wstring( L"Elevator_Cave_80" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 135, std::wstring( L"Elevator_Cave_135" ), -1.f, 1.f, 1.f ) );
	info->Pendulums->Group->Add( boost::make_shared<PieceQuad>( 190, std::wstring( L"Elevator_Cave_190" ), -1.f, 1.f, 1.f ) );

	sprite_anim( std::wstring( L"Serpent_Cave" ), std::wstring( L"Serpent_Cloud" ), 1, 2, 8 );
	info->Serpents->Serpent_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Cave" ) );
	sprite_anim( std::wstring( L"Serpent_Fish_Cave" ), std::wstring( L"Serpent_Fish_Cloud" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_Fish_Cave" ) );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Serpents->Serpent_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"Serpent_cave" ) );

	info->Spikes->Spike_Renamed->Sprite = TextureOrAnim::Get( std::wstring( L"spike_cave" ) );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = TextureOrAnim::Get( std::wstring( L"spike_base_cave_1" ) );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_spikey_cave" ) );
	info->Boulders->Ball->Size = Vector2( 150, -1 );
	info->Boulders->Radius = 120;
	info->Boulders->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_chain_cave" ) );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;

	info->Boulders->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Boulder_Cloud" ) );
	info->Boulders->Ball->Size = Vector2( 200, -1 );
	info->Boulders->Radius = 140;
	info->Boulders->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Rope_Cave" ) );
	info->Boulders->Chain->RepeatWidth = 1900;
	info->Boulders->Chain->Width = 55;

	info->SpikeyGuys->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"floater_spikey_cave" ) );
	info->SpikeyGuys->Ball->Size = Vector2( 150, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 8 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 116;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = TextureOrAnim::Get( std::wstring( L"floater_chain_cave" ) );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	//info.Orbs.Ball.Sprite = "Floater_Boulder_Cloud";
	//info.Orbs.Ball.Size = new Vector2(200, -1);
	//info.Orbs.Radius = 140;

	info->SpikeyLines->Ball->Sprite = TextureOrAnim::Get( std::wstring( L"Floater_Spikey_Cave" ) );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( std::wstring( L"blob_cave" ), std::wstring( L"blob_cave" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = TextureOrAnim::Get( std::wstring( L"blob_cave" ) );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = TextureOrAnim::Get( std::wstring( L"BlobGoo5" ) );

	info->Clouds->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"cloud_cave" ) );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 104 );

	info->Coins->Sprite->Sprite = TextureOrAnim::Get( std::wstring( L"coin_blue" ) );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;
	info->ObstacleCutoff = 40;

		t->_Finish();

		return t;
	}

	boost::shared_ptr<TileSet> TileSets::None, TileSets::Random;
	boost::shared_ptr<TileSet> TileSets::DefaultTileSet;
	std::vector<boost::shared_ptr<TileSet> > TileSets::TileList;
	std::map<int, boost::shared_ptr<TileSet> > TileSets::GuidLookup;
	std::map<std::wstring, boost::shared_ptr<TileSet> > TileSets::NameLookup, TileSets::PathLookup;

	void TileSets::AddTileSet( const boost::shared_ptr<TileSet> &tileset )
	{
		TileList.push_back( tileset );

		// FIXME: These used to be AddOrOverwrite.

		// Add the tileset to the Guid lookup
		GuidLookup[ tileset->Guid ] = tileset;
		//GuidLookup.AddOrOverwrite( tileset->Guid, tileset );

		// Add the tileset to the Name lookup
		NameLookup[ tileset->Name ] = tileset;
		//NameLookup.AddOrOverwrite( tileset->Name, tileset );

		// Add the tileset to the Path lookup
		if ( tileset->MyPath.length() > 0 )
		{
			PathLookup[ tileset->MyPath ] = tileset;
			//PathLookup.AddOrOverwrite( tileset->MyPath, tileset );
		}
	}

	void TileSets::LoadCode()
	{
		AddTileSet( Load_Sea()->SetBackground(std::wstring( L"sea" ))->SetNameInGame(Localization::Words_SEA) );
		AddTileSet( Load_Sea()->SetBackground(std::wstring( L"sea_rain" ))->SetName(std::wstring( L"sea_rain" ))->SetNameInGame(Localization::Words_SEA) );
		AddTileSet( Load_Hills()->SetBackground(std::wstring( L"hills" ))->SetNameInGame(Localization::Words_HILLS) );
		AddTileSet( Load_Hills()->SetBackground(std::wstring( L"hills_rain" ))->SetName(std::wstring( L"hills_rain" ))->SetNameInGame(Localization::Words_HILLS) );
		AddTileSet( Load_Forest()->SetBackground(std::wstring( L"forest" ))->SetNameInGame(Localization::Words_FOREST) );
		AddTileSet( Load_Forest()->SetBackground(std::wstring( L"forest_snow" ))->SetName(std::wstring( L"forest_snow" ))->SetNameInGame(Localization::Words_FOREST) );
		AddTileSet( Load_Cloud()->SetBackground(std::wstring( L"cloud" ))->SetNameInGame(Localization::Words_CLOUD) );
		AddTileSet( Load_Cloud()->SetBackground(std::wstring( L"cloud_rain" ))->SetName(std::wstring( L"cloud_rain" ))->SetNameInGame(Localization::Words_CLOUD) );
		AddTileSet( Load_Cave()->SetBackground(std::wstring( L"cave" ))->SetNameInGame(Localization::Words_CAVE) );
		AddTileSet( Load_Castle()->SetBackground(std::wstring( L"castle" ))->SetNameInGame(Localization::Words_CASTLE) );
	}

	void TileSets::LoadTileSet( const std::wstring &path )
	{
		boost::shared_ptr<CloudberryKingdom::TileSet> tileset = GetOrMakeTileset( path );

		tileset->Read( path );
		AddTileSet( tileset );
	}

	boost::shared_ptr<TileSet> TileSets::GetOrMakeTileset( const std::wstring &path )
	{
		boost::shared_ptr<TileSet> tileset;
		if ( PathLookup.find( path ) != PathLookup.end() )
		{
			tileset = PathLookup[ path ];
			tileset->MakeNew();
		}
		else
		{
			tileset = boost::make_shared<TileSet>();

			// Add the tileset to Freeplay
			CustomLevel_GUI::FreeplayTilesets.push_back( tileset );
		}

		return tileset;
	}

	void TileSets::sprite_anim( const std::wstring &name, const std::wstring &texture_root, int start_frame, int end_frame, int frame_length )
	{
		sprite_anim( name, texture_root, start_frame, end_frame, frame_length, false );
	}

	void TileSets::sprite_anim( const std::wstring &name, const std::wstring &texture_root, int start_frame, int end_frame, int frame_length, bool reverse_at_end )
	{
		boost::shared_ptr<AnimationData_Texture> sprite_anim = 0;

		sprite_anim = boost::make_shared<AnimationData_Texture>( texture_root, start_frame, end_frame );

		// Set speed based on how long each frame is.
		sprite_anim->Anims[ 0 ].Speed = 1.f / frame_length;

		// Add new sprite animation to the texture wad.
		Tools::TextureWad->Add( sprite_anim, name );
	}

	void TileSets::Init()
	{
		boost::shared_ptr<TileSet> info;

		// None
		DefaultTileSet = None = info = boost::make_shared<TileSet>();
		info->Name = std::wstring( L"None" );
		info->NameInGame = Localization::Words_NONE;
		info->Guid = 5551;
		AddTileSet( info );
		info->MyBackgroundType = BackgroundType::None;
		info->ScreenshotString = std::wstring( L"Screenshot_Random" );
		info->HasCeiling = true;
		info->FlexibleHeight = false;
		Upgrade tempVector[] = { Upgrade_BOUNCY_BLOCK, Upgrade_FLY_BLOB, Upgrade_MOVING_BLOCK, Upgrade_SPIKE };
		AddRange<Upgrade>( info->ObstacleUpgrades, VecFromArray( tempVector ) );

		// Random
		Random = info = boost::make_shared<TileSet>();
		info->Name = std::wstring( L"Random" );
		info->NameInGame = Localization::Words_RANDOM;
		info->Guid = 5552;
		AddTileSet( info );
		info->MyBackgroundType = BackgroundType::Random;
		info->ScreenshotString = std::wstring( L"Screenshot_Random" );
		Upgrade tempVector2[] = { Upgrade_BOUNCY_BLOCK, Upgrade_FLY_BLOB, Upgrade_MOVING_BLOCK, Upgrade_FIREBALL, Upgrade_PINKY };
		AddRange( info->ObstacleUpgrades, VecFromArray( tempVector2 ) );

		// Sprite effects
		LoadSpriteEffects();

		// New tile sets
		TileSets::LoadCode();

		// Freeplay tilesets
		boost::shared_ptr<TileSet>  tempVector3[] = {
			TileSets::Random,
			TileSet::Get( std::wstring( L"sea" ) ),
			TileSet::Get( std::wstring( L"hills" ) ),
			TileSet::Get( std::wstring( L"forest" ) ),
			TileSet::Get( std::wstring( L"cloud" ) ),
			TileSet::Get( std::wstring( L"cave" ) ),
			TileSet::Get( std::wstring( L"castle" ) )
		};
		CustomLevel_GUI::FreeplayTilesets = VecFromArray( tempVector3 );
	}

	void TileSets::LoadSpriteEffects()
	{
		sprite_anim( std::wstring( L"CoinShimmer" ), std::wstring( L"Coin" ), 0, 49, 1 );

		sprite_anim( std::wstring( L"BlobExplosion_v2" ), std::wstring( L"BlobExplosion_v02" ), 0, 29, 1 );
		sprite_anim( std::wstring( L"BobExplosion_v1" ), std::wstring( L"BobExplosion_v01" ), 0, 54, 1 );
		sprite_anim( std::wstring( L"CoinCollect_v1" ), std::wstring( L"CoinCollect_v01" ), 0, 32, 1 );
		sprite_anim( std::wstring( L"CoinCollect_v2" ), std::wstring( L"CoinCollect_v02" ), 0, 26, 1 );
		sprite_anim( std::wstring( L"CoinCollect_Sparkes_v3" ), std::wstring( L"CoinCollect_Sparkles_v03" ), 0, 26, 1 );
		sprite_anim( std::wstring( L"CoinCollect_Star_v3" ), std::wstring( L"CoinCollect_Star_v03" ), 0, 17, 1 );
		sprite_anim( std::wstring( L"CoinCollect_v4" ), std::wstring( L"CoinCollect_v04" ), 0, 26, 1 );
	}
}
