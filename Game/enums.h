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

enum Keys
{
    // Summary:
    //     Reserved
	Keys_None = 0,
    //
    // Summary:
    //     BACKSPACE key
	Keys_Back = 8,
    //
    // Summary:
    //     TAB key
	Keys_Tab = 9,
    //
    // Summary:
    //     ENTER key
	Keys_Enter = 13,
    //
    // Summary:
    //     PAUSE key
	Keys_Pause = 19,
    //
    // Summary:
    //     CAPS LOCK key
	Keys_CapsLock = 20,
    //
    // Summary:
    //     Kana key on Japanese keyboards
	Keys_Kana = 21,
    //
    // Summary:
    //     Kanji key on Japanese keyboards
	Keys_Kanji = 25,
    //
    // Summary:
    //     ESC key
	Keys_Escape = 27,
    //
    // Summary:
    //     IME Convert key
	Keys_ImeConvert = 28,
    //
    // Summary:
    //     IME NoConvert key
	Keys_ImeNoConvert = 29,
    //
    // Summary:
    //     SPACEBAR
	Keys_Space = 32,
    //
    // Summary:
    //     PAGE UP key
	Keys_PageUp = 33,
    //
    // Summary:
    //     PAGE DOWN key
	Keys_PageDown = 34,
    //
    // Summary:
    //     END key
	Keys_End = 35,
    //
    // Summary:
    //     HOME key
	Keys_Home = 36,
    //
    // Summary:
    //     LEFT ARROW key
	Keys_Left = 37,
    //
    // Summary:
    //     UP ARROW key
	Keys_Up = 38,
    //
    // Summary:
    //     RIGHT ARROW key
	Keys_Right = 39,
    //
    // Summary:
    //     DOWN ARROW key
	Keys_Down = 40,
    //
    // Summary:
    //     SELECT key
	Keys_Select = 41,
    //
    // Summary:
    //     PRINT key
	Keys_Print = 42,
    //
    // Summary:
    //     EXECUTE key
	Keys_Execute = 43,
    //
    // Summary:
    //     PRINT SCREEN key
	Keys_PrintScreen = 44,
    //
    // Summary:
    //     INS key
	Keys_Insert = 45,
    //
    // Summary:
    //     DEL key
	Keys_Delete = 46,
    //
    // Summary:
    //     HELP key
	Keys_Help = 47,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D0 = 48,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D1 = 49,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D2 = 50,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D3 = 51,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D4 = 52,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D5 = 53,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D6 = 54,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D7 = 55,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D8 = 56,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_D9 = 57,
    //
    // Summary:
    //     A key
	Keys_A = 65,
    //
    // Summary:
    //     B key
	Keys_B = 66,
    //
    // Summary:
    //     C key
	Keys_C = 67,
    //
    // Summary:
    //     D key
	Keys_D = 68,
    //
    // Summary:
    //     E key
	Keys_E = 69,
    //
    // Summary:
    //     F key
	Keys_F = 70,
    //
    // Summary:
    //     G key
	Keys_G = 71,
    //
    // Summary:
    //     H key
	Keys_H = 72,
    //
    // Summary:
    //     I key
	Keys_I = 73,
    //
    // Summary:
    //     J key
	Keys_J = 74,
    //
    // Summary:
    //     K key
	Keys_K = 75,
    //
    // Summary:
    //     L key
	Keys_L = 76,
    //
    // Summary:
    //     M key
	Keys_M = 77,
    //
    // Summary:
    //     N key
	Keys_N = 78,
    //
    // Summary:
    //     O key
	Keys_O = 79,
    //
    // Summary:
    //     P key
	Keys_P = 80,
    //
    // Summary:
    //     Q key
	Keys_Q = 81,
    //
    // Summary:
    //     R key
	Keys_R = 82,
    //
    // Summary:
    //     S key
	Keys_S = 83,
    //
    // Summary:
    //     T key
	Keys_T = 84,
    //
    // Summary:
    //     U key
	Keys_U = 85,
    //
    // Summary:
    //     V key
	Keys_V = 86,
    //
    // Summary:
    //     W key
	Keys_W = 87,
    //
    // Summary:
    //     X key
	Keys_X = 88,
    //
    // Summary:
    //     Y key
	Keys_Y = 89,
    //
    // Summary:
    //     Z key
	Keys_Z = 90,
    //
    // Summary:
    //     Left Windows key
	Keys_LeftWindows = 91,
    //
    // Summary:
    //     Right Windows key
	Keys_RightWindows = 92,
    //
    // Summary:
    //     Applications key
	Keys_Apps = 93,
    //
    // Summary:
    //     Computer Sleep key
	Keys_Sleep = 95,
    //
    // Summary:
    //     Numeric keypad 0 key
	Keys_NumPad0 = 96,
    //
    // Summary:
    //     Numeric keypad 1 key
	Keys_NumPad1 = 97,
    //
    // Summary:
    //     Numeric keypad 2 key
	Keys_NumPad2 = 98,
    //
    // Summary:
    //     Numeric keypad 3 key
	Keys_NumPad3 = 99,
    //
    // Summary:
    //     Numeric keypad 4 key
	Keys_NumPad4 = 100,
    //
    // Summary:
    //     Numeric keypad 5 key
	Keys_NumPad5 = 101,
    //
    // Summary:
    //     Numeric keypad 6 key
	Keys_NumPad6 = 102,
    //
    // Summary:
    //     Numeric keypad 7 key
	Keys_NumPad7 = 103,
    //
    // Summary:
    //     Numeric keypad 8 key
	Keys_NumPad8 = 104,
    //
    // Summary:
    //     Numeric keypad 9 key
	Keys_NumPad9 = 105,
    //
    // Summary:
    //     Multiply key
	Keys_Multiply = 106,
    //
    // Summary:
    //     Add key
	Keys_Add = 107,
    //
    // Summary:
    //     Separator key
	Keys_Separator = 108,
    //
    // Summary:
    //     Subtract key
	Keys_Subtract = 109,
    //
    // Summary:
    //     Decimal key
	Keys_Decimal = 110,
    //
    // Summary:
    //     Divide key
	Keys_Divide = 111,
    //
    // Summary:
    //     F1 key
	Keys_F1 = 112,
    //
    // Summary:
    //     F2 key
	Keys_F2 = 113,
    //
    // Summary:
    //     F3 key
	Keys_F3 = 114,
    //
    // Summary:
    //     F4 key
	Keys_F4 = 115,
    //
    // Summary:
    //     F5 key
	Keys_F5 = 116,
    //
    // Summary:
    //     F6 key
	Keys_F6 = 117,
    //
    // Summary:
    //     F7 key
	Keys_F7 = 118,
    //
    // Summary:
    //     F8 key
	Keys_F8 = 119,
    //
    // Summary:
    //     F9 key
	Keys_F9 = 120,
    //
    // Summary:
    //     F10 key
	Keys_F10 = 121,
    //
    // Summary:
    //     F11 key
	Keys_F11 = 122,
    //
    // Summary:
    //     F12 key
	Keys_F12 = 123,
    //
    // Summary:
    //     F13 key
	Keys_F13 = 124,
    //
    // Summary:
    //     F14 key
	Keys_F14 = 125,
    //
    // Summary:
    //     F15 key
	Keys_F15 = 126,
    //
    // Summary:
    //     F16 key
	Keys_F16 = 127,
    //
    // Summary:
    //     F17 key
	Keys_F17 = 128,
    //
    // Summary:
    //     F18 key
	Keys_F18 = 129,
    //
    // Summary:
    //     F19 key
	Keys_F19 = 130,
    //
    // Summary:
    //     F20 key
	Keys_F20 = 131,
    //
    // Summary:
    //     F21 key
	Keys_F21 = 132,
    //
    // Summary:
    //     F22 key
	Keys_F22 = 133,
    //
    // Summary:
    //     F23 key
	Keys_F23 = 134,
    //
    // Summary:
    //     F24 key
	Keys_F24 = 135,
    //
    // Summary:
    //     NUM LOCK key
	Keys_NumLock = 144,
    //
    // Summary:
    //     SCROLL LOCK key
	Keys_Scroll = 145,
    //
    // Summary:
    //     Left SHIFT key
	Keys_LeftShift = 160,
    //
    // Summary:
    //     Right SHIFT key
	Keys_RightShift = 161,
    //
    // Summary:
    //     Left CONTROL key
	Keys_LeftControl = 162,
    //
    // Summary:
    //     Right CONTROL key
	Keys_RightControl = 163,
    //
    // Summary:
    //     Left ALT key
	Keys_LeftAlt = 164,
    //
    // Summary:
    //     Right ALT key
	Keys_RightAlt = 165,
    //
    // Summary:
    //     Windows 2000/XP: Browser Back key
	Keys_BrowserBack = 166,
    //
    // Summary:
    //     Windows 2000/XP: Browser Forward key
	Keys_BrowserForward = 167,
    //
    // Summary:
    //     Windows 2000/XP: Browser Refresh key
	Keys_BrowserRefresh = 168,
    //
    // Summary:
    //     Windows 2000/XP: Browser Stop key
	Keys_BrowserStop = 169,
    //
    // Summary:
    //     Windows 2000/XP: Browser Search key
	Keys_BrowserSearch = 170,
    //
    // Summary:
    //     Windows 2000/XP: Browser Favorites key
	Keys_BrowserFavorites = 171,
    //
    // Summary:
    //     Windows 2000/XP: Browser Start and Home key
	Keys_BrowserHome = 172,
    //
    // Summary:
    //     Windows 2000/XP: Volume Mute key
	Keys_VolumeMute = 173,
    //
    // Summary:
    //     Windows 2000/XP: Volume Down key
	Keys_VolumeDown = 174,
    //
    // Summary:
    //     Windows 2000/XP: Volume Up key
	Keys_VolumeUp = 175,
    //
    // Summary:
    //     Windows 2000/XP: Next Track key
	Keys_MediaNextTrack = 176,
    //
    // Summary:
    //     Windows 2000/XP: Previous Track key
	Keys_MediaPreviousTrack = 177,
    //
    // Summary:
    //     Windows 2000/XP: Stop Media key
	Keys_MediaStop = 178,
    //
    // Summary:
    //     Windows 2000/XP: Play/Pause Media key
	Keys_MediaPlayPause = 179,
    //
    // Summary:
    //     Windows 2000/XP: Start Mail key
	Keys_LaunchMail = 180,
    //
    // Summary:
    //     Windows 2000/XP: Select Media key
	Keys_SelectMedia = 181,
    //
    // Summary:
    //     Windows 2000/XP: Start Application 1 key
	Keys_LaunchApplication1 = 182,
    //
    // Summary:
    //     Windows 2000/XP: Start Application 2 key
	Keys_LaunchApplication2 = 183,
    //
    // Summary:
    //     Windows 2000/XP: The OEM Semicolon key on a US standard keyboard
	Keys_OemSemicolon = 186,
    //
    // Summary:
    //     Windows 2000/XP: For any country/region, the '+' key
	Keys_OemPlus = 187,
    //
    // Summary:
    //     Windows 2000/XP: For any country/region, the ',' key
	Keys_OemComma = 188,
    //
    // Summary:
    //     Windows 2000/XP: For any country/region, the '-' key
	Keys_OemMinus = 189,
    //
    // Summary:
    //     Windows 2000/XP: For any country/region, the '.' key
	Keys_OemPeriod = 190,
    //
    // Summary:
    //     Windows 2000/XP: The OEM question mark key on a US standard keyboard
	Keys_OemQuestion = 191,
    //
    // Summary:
    //     Windows 2000/XP: The OEM tilde key on a US standard keyboard
	Keys_OemTilde = 192,
    //
    // Summary:
    //     Green ChatPad key
	Keys_ChatPadGreen = 202,
    //
    // Summary:
    //     Orange ChatPad key
	Keys_ChatPadOrange = 203,
    //
    // Summary:
    //     Windows 2000/XP: The OEM open bracket key on a US standard keyboard
	Keys_OemOpenBrackets = 219,
    //
    // Summary:
    //     Windows 2000/XP: The OEM pipe key on a US standard keyboard
	Keys_OemPipe = 220,
    //
    // Summary:
    //     Windows 2000/XP: The OEM close bracket key on a US standard keyboard
	Keys_OemCloseBrackets = 221,
    //
    // Summary:
    //     Windows 2000/XP: The OEM singled/double quote key on a US standard keyboard
	Keys_OemQuotes = 222,
    //
    // Summary:
    //     Used for miscellaneous characters; it can vary by keyboard.
	Keys_Oem8 = 223,
    //
    // Summary:
    //     Windows 2000/XP: The OEM angle bracket or backslash key on the RT 102 key
    //     keyboard
	Keys_OemBackslash = 226,
    //
    // Summary:
    //     Windows 95/98/Me, Windows NT 4.0, Windows 2000/XP: IME PROCESS key
	Keys_ProcessKey = 229,
    //
    // Summary:
    //     OEM Copy key
	Keys_OemCopy = 242,
    //
    // Summary:
    //     OEM Auto key
	Keys_OemAuto = 243,
    //
    // Summary:
    //     OEM Enlarge Window key
	Keys_OemEnlW = 244,
    //
    // Summary:
    //     Attn key
	Keys_Attn = 246,
    //
    // Summary:
    //     CrSel key
	Keys_Crsel = 247,
    //
    // Summary:
    //     ExSel key
	Keys_Exsel = 248,
    //
    // Summary:
    //     Erase EOF key
	Keys_EraseEof = 249,
    //
    // Summary:
    //     Play key
	Keys_Play = 250,
    //
    // Summary:
    //     Zoom key
	Keys_Zoom = 251,
    //
    // Summary:
    //     PA1 key
	Keys_Pa1 = 253,
    //
    // Summary:
    //     CLEAR key
	Keys_OemClear = 254
};

enum PlayerIndex
{
    PlayerIndex_One = 0,
    PlayerIndex_Two = 1,
    PlayerIndex_Three = 2,
    PlayerIndex_Four = 3
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
	GfxBlendState_AlphaBlend
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

enum ButtonState
{
	ButtonState_Pressed,
	ButtonState_Released
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

#endif
