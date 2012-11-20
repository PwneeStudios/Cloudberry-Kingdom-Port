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
	ControllerButtons_NONE
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

#endif
