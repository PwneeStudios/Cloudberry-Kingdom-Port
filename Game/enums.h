#ifndef _ENUMS_H_
#define _ENUMS_H_

enum AnimQueueEntryType
{
	AnimQueueEntryType_PLAY,
	AnimQueueEntryType_PLAY_UNTIL,
	AnimQueueEntryType_TRANSFER
};

enum ObjectDrawOrder
{
	ObjectDrawOrder_WITH_OUTLINE,
	ObjectDrawOrder_BEFORE_OUTLINE,
	ObjectDrawOrder_AFTER_OUTLINE,
	ObjectDrawOrder_ALL,
	ObjectDrawOrder_NONE
};

enum ChangeMode
{
	ChangeMode_SINGLE_FRAME,
	ChangeMode_SINGLE_ANIM,
	ChangeMode_ALL
};

enum ControllerButtons
{
	ControllerButtons_A,
	ControllerButtons_B,
	ControllerButtons_X,
	ControllerButtons_Y,
	ControllerButtons_RS,
	ControllerButtons_LS,
	ControllerButtons_RT,
	ControllerButtons_LT,
	ControllerButtons_RJ,
	ControllerButtons_RJBUTTON,
	ControllerButtons_LJ,
	ControllerButtons_LJBUTTON,
	ControllerButtons_DPAD,
	ControllerButtons_START,
	ControllerButtons_BACK,
	ControllerButtons_LEFT,
	ControllerButtons_RIGHT,
	ControllerButtons_UP,
	ControllerButtons_DOWN,
	ControllerButtons_ENTER,
	ControllerButtons_NONE,
	ControllerButtons_LENGTH
};

enum MashType
{
	MashType_HOLD,
	MashType_TAP,
	MashType_ALTERNATE,
	MashType_HOLD_DIR
};

enum LerpStyle
{
	LerpStyle_LINEAR,
	LerpStyle_SMALL_OVERSHOOT,
	LerpStyle_DECAY_PLUS_SMALL_OVERSHOOT,
	LerpStyle_DECAY_NO_OVERSHOOT,
	LerpStyle_SIGMOID
};

enum Side
{
	Side_RIGHT,
	Side_LEFT,
	Side_TOP,
	Side_BOTTOM
};

enum ColType
{
	ColType_NO_COL,
	ColType_LEFT,
	ColType_RIGHT,
	ColType_TOP,
	ColType_BOTTOM
};

enum DifficultyParam
{
	DifficultyParam_BIG_BOX_X,
	DifficultyParam_BIG_BOX_Y,
	DifficultyParam_GENERAL_MIN_DIST,
	DifficultyParam_MIN_BOX_SIZE_X,
	DifficultyParam_MIN_BOX_SIZE_Y,
	DifficultyParam_MAX_BOX_SIZE_X,
	DifficultyParam_MAX_BOX_SIZE_Y,

	DifficultyParam_LONG_JUMP_START,
	DifficultyParam_MIN_FALL,
	DifficultyParam_MAX_FALL,
	DifficultyParam_MIN_DROP,
	DifficultyParam_MAX_DROP,
	DifficultyParam_TIME_TO_BOB_TARGET_SWITCH,
	DifficultyParam_JUMPING_SPEED_RETARD_FACTOR,
	DifficultyParam_RETARD_JUMP_LENGTH,
	DifficultyParam_DISTANCE_PAST,
	DifficultyParam_DISTANCE_PAST_NO_JUMP,
	DifficultyParam_EDGE_JUMP_DURATION,
	DifficultyParam_NO_EDGE_JUMP_DURATION,
	DifficultyParam_EDGE_SAFETY, // How close to the edge of a block the computer can land on
	DifficultyParam_APEX_WAIT, // How long after the apex of a jump should we wait before potentially landing on something?
	DifficultyParam_FILL_SPARSITY,
	DifficultyParam_LENGTH
};

enum BehaviorParam
{
	BehaviorParam_FALL_LENGTH_BASE,
	BehaviorParam_FALL_LENGTH_ADD,
	BehaviorParam_BACK_LENGTH_BASE,
	BehaviorParam_BACK_LENGTH_ADD,
	BehaviorParam_FORWARD_LENGTH_BASE,
	BehaviorParam_FORWARD_LENGTH_ADD,
	BehaviorParam_MOVE_WEIGHT,
	BehaviorParam_SIT_WEIGHT,
	BehaviorParam_MOVE_LENGTH_BASE,
	BehaviorParam_MOVE_LENGTH_ADD,
	BehaviorParam_SIT_LENGTH_BASE,
	BehaviorParam_SIT_LENGTH_ADD,
	BehaviorParam_JUMP_WEIGHT,
	BehaviorParam_NO_JUMP_WEIGHT,
	BehaviorParam_JUMP_LENGTH_BASE,
	BehaviorParam_JUMP_LENGTH_ADD,
	BehaviorParam_NO_JUMP_LENGTH_BASE,
	BehaviorParam_NO_JUMP_LENGTH_ADD,
	BehaviorParam_MOVE_TYPE_PERIOD,
	BehaviorParam_MOVE_TYPE_INNER_PERIOD
};

enum LevelGeometry
{
	LevelGeometry_RIGHT,
	LevelGeometry_UP,
	LevelGeometry_ONE_SCREEN,
	LevelGeometry_DOWN,
	LevelGeometry_BIG
};

enum LevelZoom
{
	LevelZoom_NORMAL,
	LevelZoom_BIG
};

enum ReplayGUIType
{
	ReplayGUIType_REPLAY,
	ReplayGUIType_COMPUTER
};

enum IconType
{
	IconType_NUMBER,
	IconType_BOSS,
	IconType_OBSTACLE,
	IconType_HERO,
	IconType_PLACE,
	IconType_BUNGEE
};

enum BouncyBlockState
{
	BouncyBlockState_REGULAR,
	BouncyBlockState_SUPER_STIFF
};

enum FallingBlockState
{
	FallingBlockState_REGULAR,
	FallingBlockState_TOUCHED,
	FallingBlockState_FALLING,
	FallingBlockState_ANGRY
};

enum GhostBlockState
{
	GhostBlockState_PHASED_IN,
	GhostBlockState_PHASED_OUT
};

enum MovingBlockMoveType
{
	MovingBlockMoveType_LINE,
	MovingBlockMoveType_CIRCLE,
	MovingBlockMoveType_FIGURE_EIGHT
};

enum PendulumMoveType
{
	PendulumMoveType_LINE,
	PendulumMoveType_SQUARE
};

enum StatGroup
{
	StatGroup_LIFETIME,
	StatGroup_GAME,
	StatGroup_LEVEL,
	StatGroup_TEMP,
	StatGroup_CAMPAIGN
};

enum ObjectType
{
	ObjectType_UNDEFINED,
	ObjectType_COIN,
	ObjectType_CHECKPOINT,
	ObjectType_BERRY_BUBBLE,
	ObjectType_FLYING_BLOB,
	ObjectType_BLOCK_EMITTER,
	ObjectType_SPIKE,
	ObjectType_FIREBALL,
	ObjectType_FIRE_SPINNER,
	ObjectType_BOULDER,
	ObjectType_LASER,
	ObjectType_NORMAL_BLOCK,
	ObjectType_FALLING_BLOCK,
	ObjectType_LAVA_BLOCK,
	ObjectType_MOVING_PLATFORM,
	ObjectType_MOVING_BLOCK,
	ObjectType_GHOST_BLOCK,
	ObjectType_CLOUD,
	ObjectType_BOUNCY_BLOCK,
	ObjectType_SPIKEY_GUY,
	ObjectType_SPIKEY_LINE,
	ObjectType_PENDULUM,
	ObjectType_SERPENT,
	ObjectType_LAVA_DRIP,
	ObjectType_FIRESNAKE,
	ObjectType_CONVEYOR_BLOCK,
	ObjectType_DOOR,
	ObjectType_WALL,
	ObjectType_ZONE_TRIGGER,
	ObjectType_CAMERA_ZONE,
	ObjectType_LENGTH
};

// Would be nice to get rid of this, and just rely on ...__AutoGen.instances, and have dictionaries with instances as keys
enum Upgrade
{
	Upgrade_FIREBALL,
	Upgrade_FIRESNAKE,
	Upgrade___UNUSED__1,
	Upgrade_SPIKE,
	Upgrade_FALLING_BLOCK,
	Upgrade_FLY_BLOB,
	Upgrade_FIRE_SPINNER,
	Upgrade_MOVING_BLOCK,
	Upgrade_ELEVATOR,
	Upgrade_SPIKEY_GUY,
	Upgrade_PINKY,
	Upgrade_SPIKEY_LINE,
	Upgrade_LASER,
	Upgrade_GHOST_BLOCK,
	Upgrade_BOUNCY_BLOCK,
	Upgrade_CLOUD,
	Upgrade_CONVEYOR,
	Upgrade_PENDULUM,
	Upgrade_SERPENT,
	Upgrade_LAVA_DRIP,
	Upgrade_GENERAL,
	Upgrade_SPEED,
	Upgrade_JUMP,
	Upgrade_CEILING,
	Upgrade_LENGTH
};

enum LadderType
{
	LadderType_NONE,
	LadderType_FINAL_PLAT,
	LadderType_FINAL_BOUNCY,
	LadderType_SIMPLE,
	LadderType_SIMPLE2,
	LadderType_DOUBLE,
	LadderType_SIMPLE_MOVING,
	LadderType_DOUBLE_MOVING,
	LadderType_MAKE_PLAT
};

enum BoxStyle
{
	BoxStyle_TOP_ONLY,
	BoxStyle_FULL_BOX
};

enum TimeTypes
{
	TimeTypes_UNSET,
	TimeTypes_REGULAR,
	TimeTypes_X_SYNC
};

enum Hero_BaseType
{
	Hero_BaseType_CLASSIC,
	Hero_BaseType_BOX,
	Hero_BaseType_WHEEL,
	Hero_BaseType_BOUNCY,
	Hero_BaseType_SPACESHIP,
	Hero_BaseType_MEAT,
	Hero_BaseType_ROCKET_BOX,
	Hero_BaseType_LENGTH
};

enum Hero_Shape
{
	Hero_Shape_CLASSIC,
	Hero_Shape_SMALL,
	Hero_Shape_OSCILLATE,
	Hero_Shape_BIG,
	Hero_Shape_LENGTH
};

enum Hero_MoveMod
{
	Hero_MoveMod_CLASSIC,
	Hero_MoveMod_DOUBLE,
	Hero_MoveMod_JETPACK,
	Hero_MoveMod_INVERT,
	Hero_MoveMod_LENGTH
};

enum Hero_Special
{
	Hero_Special_CLASSIC,
	Hero_Special_TIME,
	Hero_Special_LENGTH
};

enum CapeType
{
	CapeType_NORMAL,
	CapeType_SMALL,
	CapeType_NONE
};

enum BobDeathType
{
	BobDeathType_NONE,
	BobDeathType_FIREBALL,
	BobDeathType_FIRESNAKE,
	BobDeathType_FIRE_SPINNER,
	BobDeathType_BOULDER,
	BobDeathType_SPIKEY_GUY,
	BobDeathType_SPIKE,
	BobDeathType_FALL,
	BobDeathType_LAVA,
	BobDeathType_BLOB,
	BobDeathType_LASER,
	BobDeathType_LAVA_FLOW,
	BobDeathType_FALLING_SPIKE,
	BobDeathType_UNNAMED1,
	BobDeathType_UNNAMED2,
	BobDeathType_UNNAMED3,
	BobDeathType_UNNAMED4,
	BobDeathType_UNNAMED5,
	BobDeathType_UNNAMED6,
	BobDeathType_UNNAMED7,
	BobDeathType_UNNAMED8,
	BobDeathType_UNNAMED9,
	BobDeathType_UNNAMED10,
	BobDeathType_UNNAMED11,
	BobDeathType_UNNAMED12,
	BobDeathType_UNNAMED13,
	BobDeathType_UNNAMED14,
	BobDeathType_UNNAMED15,
	BobDeathType_UNNAMED16,
	BobDeathType_UNNAMED17,
	BobDeathType_UNNAMED18,
	BobDeathType_UNNAMED19,
	BobDeathType_UNNAMED20,
	BobDeathType_UNNAMED21,
	BobDeathType_UNNAMED22,
	BobDeathType_UNNAMED23,
	BobDeathType_UNNAMED24,
	BobDeathType_UNNAMED25,
	BobDeathType_UNNAMED26,
	BobDeathType_UNNAMED27,
	BobDeathType_UNNAMED28,
	BobDeathType_UNNAMED29,
	BobDeathType_UNNAMED30,
	BobDeathType_TIME,
	BobDeathType_LEFT_BEHIND,
	BobDeathType_OTHER,
	BobDeathType_TOTAL,
	BobDeathType_LENGTH
};

enum Camera_PhsxType
{
	Camera_PhsxType_FIXED,
	Camera_PhsxType_SIDE_LEVEL_RIGHT,
	Camera_PhsxType_SIDE_LEVEL_UP,
	Camera_PhsxType_SIDE_LEVEL_DOWN,
	Camera_PhsxType_CENTER,
	Camera_PhsxType_SIDE_LEVEL_UP_RELAXED,
	Camera_PhsxType_WORLD_MAP
};

enum GfxRasterizerState
{
	GfxRasterizerState_CullNone,
	GfxRasterizerState_CullCounterClockwise
};

enum GfxBlendState
{
	GfxBlendState_AlphaBlend,
	GfxBlendState_Additive
};

enum GfxDepthStencilState
{
	GfxDepthStencilState_None,
	GfxDepthStencilState_DepthRead
};

enum GfxTextureAddressMode
{
	GfxTextureAddressMode_Wrap,
	GfxTextureAddressMode_Clamp
};

enum GfxPrimitiveType
{
	GfxPrimitiveType_TriangleList
};

enum GfxSamplerState
{
	GfxSamplerState_LinearClamp
};

enum SpriteSortMode
{
	SpriteSortMode_Immediate
};

enum MediaState
{
	MediaState_Paused,
	MediaState_Playing
};

enum SpriteEffects
{
	SpriteEffects_None
};

#include <Input/InputEnums.h>

#endif
