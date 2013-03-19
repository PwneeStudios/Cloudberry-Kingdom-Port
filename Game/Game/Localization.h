#ifndef LOCALIZATION
#define LOCALIZATION

#include <global_header.h>

#include "Hacks/XNA/ContentManager.h"

namespace CloudberryKingdom
{

	struct Localization
	{
	
		enum Language
		{
			Language_ENGLISH,
			Language_JAPANESE,
			Language_GERMAN,
			Language_PORTUGUESE,
			Language_ITALIAN,
			Language_FRENCH,
			Language_SPANISH,
			Language_RUSSIAN,
			Language_KOREAN,
			Language_CHINESE
		};

	
		enum Words
		{
Words_Identifier,
Words_PressStart,
Words_PressAnyKey,
Words_TheArcade,
Words_StoryMode,
Words_FreePlay,
Words_Options,
Words_Exit,
Words_ExitGame,
Words_Yes,
Words_No,
Words_Language,
Words_SoundVolume,
Words_MusicVolume,
Words_Controls,
Words_EditControls,
Words_Resolution,
Words_FullScreen,
Words_WindowBorder,
Words_On,
Words_Off,
Words_QuickSpawn,
Words_PowerUpMenu,
Words_Left,
Words_Right,
Words_Up,
Words_Down,
Words_ReplayPrev,
Words_ReplayNext,
Words_ReplayToggle,
Words_ToggleSlowMo,
Words_Accept,
Words_Back,
Words_Menu,
Words_Reset,
Words_PressToJoin,
Words_Custom,
Words_Random,
Words_Done,
Words_Color,
Words_Beard,
Words_Hat,
Words_Cape,
Words_Lining,
Words_Use,
Words_Cancel,
Words_White,
Words_Silver,
Words_Gray,
Words_Black,
Words_Cyan,
Words_Blue,
Words_Teal,
Words_Indigo,
Words_Purple,
Words_Brown,
Words_Red,
Words_HotPink,
Words_Orange,
Words_Gold,
Words_Yellow,
Words_Green,
Words_LimeGreen,
Words_ForestGreen,
Words_Ninja,
Words_BrightWhite,
Words_Clear,
Words_Rugged,
Words_Manhattan,
Words_Lumberjack,
Words_Goatee,
Words_Vandyke,
Words_None,
Words_Viking,
Words_Fedora,
Words_Afro,
Words_Halo,
Words_Firehead,
Words_Horns,
Words_Bubble,
Words_TopHat,
Words_KnightHelmet,
Words_OmNomNom,
Words_BrainHat,
Words_Gosu,
Words_RobinHood,
Words_Reggae,
Words_Pumpkin,
Words_PirateHat,
Words_HardHat,
Words_FourEyes,
Words_BunnyEars,
Words_Antlers,
Words_ArrowThroughHead,
Words_BrownBag,
Words_TrafficCone,
Words_PopeHat,
Words_RiceHat,
Words_SantaClaus,
Words_Sombrero,
Words_TikiMask,
Words_Wizard,
Words_Location,
Words_Game,
Words_ClassicGame,
Words_Bungee,
Words_WallLevel,
Words_Hero,
Words_Factory,
Words_Difficulty,
Words_Training,
Words_Unpleasant,
Words_Abusive,
Words_Hardcore,
Words_Masochistic,
Words_Length,
Words_Checkpoints,
Words_Start,
Words_Continue,
Words_LoadLevel,
Words_HeroFactory,
Words_Base,
Words_Jump,
Words_Shape,
Words_Play,
Words_Test,
Words_Passive,
Words_Aggressive,
Words_Next,
Words_JumpDifficulty,
Words_LevelSpeed,
Words_Ceilings,
Words_MovingBlocks,
Words_GhostBlocks,
Words_FallingBlocks,
Words_Elevators,
Words_Clouds,
Words_BouncyBlocks,
Words_Pendulums,
Words_FlyingBlobs,
Words_Firespinners,
Words_Boulders,
Words_SpikeyGuys,
Words_Lasers,
Words_Spikes,
Words_Sludge,
Words_Serpent,
Words_SpikeyLines,
Words_Fireballs,
Words_Acceleration,
Words_MaxVelocity,
Words_Size,
Words_Gravity,
Words_MaxFallSpeed,
Words_Friction,
Words_JumpLength,
Words_JumpAcc,
Words_NumJumps,
Words_DoubleJumpLength,
Words_DoubleJumpAccel,
Words_JetpackAcc,
Words_JetpackFuel,
Words_PhasedSize,
Words_PhasedGravity,
Words_PhasePeriod,
Words_ClassicHero,
Words_Jetman,
Words_DoubleJump,
Words_TinyBob,
Words_Wheelie,
Words_Spaceship,
Words_HeroInABox,
Words_Bouncy,
Words_Rocketbox,
Words_FatBob,
Words_PhaseBob,
Words_Viridian,
Words_TimeMaster,
Words_Meatboy,
Words_JetpackWheelie,
Words_TinyDoubleJump,
Words_BoxJetpack,
Words_DoubleJumpWheelie,
Words_FatBouncy,
Words_TinyBox,
Words_PhasingJetpack,
Words_BouncyJetpack,
Words_FatDoubleJump,
Words_Sea,
Words_Hills,
Words_Forest,
Words_Cloud,
Words_Cave,
Words_Castle,
Words_TheBeginning,
Words_TheNextNinetyNine,
Words_AGauntletOfDoom,
Words_AlmostHero,
Words_TheMasochist,
Words_Escalation,
Words_TimeCrisis,
Words_HeroRush,
Words_HybridRush,
Words_HighScore,
Words_BestLevel,
Words_Leaderboard,
Words_Score,
Words_Level,
Words_Ready,
Words_Go,
Words_GetToTheExit,
Words_SecondsOnTheClock,
Words_CoinsAddSeconds,
Words_GetAHighScore,
Words_Perfect,
Words_ExtraLife,
Words_Press,
Words_Resume,
Words_Statistics,
Words_SaveLoad,
Words_RemoveMe,
Words_ExitLevel,
Words_RandomSeed,
Words_SaveSeed,
Words_LoadSeed,
Words_CopyToClipboard,
Words_LoadFromClipboard,
Words_RemovePlayerQuestion,
Words_ExitLevelQuestion,
Words_SaveRandomSeedAs,
Words_SavedSeeds,
Words_LoadTheFollowingSeedQuestion,
Words_SeedSavedSuccessfully,
Words_Hooray,
Words_NoNameGiven,
Words_Oh,
Words_LevelsBeat,
Words_Jumps,
Words_Coins,
Words_Grabbed,
Words_CoinsOutOf,
Words_Percent,
Words_Blobs,
Words_AverageLife,
Words_Deaths,
Words_Fireball,
Words_Firespinner,
Words_Boulder,
Words_SpikeyGuy,
Words_Spike,
Words_Falling,
Words_Lava,
Words_Blob,
Words_Laser,
Words_FallingSpikey,
Words_TimeLimit,
Words_LeftBehind,
Words_Other,
Words_Total,
Words_GameOver,
Words_NewHighScore,
Words_PlayAgain,
Words_HighScores,
Words_Local,
Words_Global,
Words_WatchComputer,
Words_ShowPath,
Words_ActivateSlowMo,
Words_Paused,
Words_Speed,
Words_Step,
Words_LevelCleared,
Words_KeepSettings,
Words_WatchReplay,
Words_BackToFreeplay,
Words_Pause,
Words_Single,
Words_Previous,
Words_All,
Words_End,
Words_Loading,
Words_HeroUnlocked,
Words_NewHeroUnlocked,
Words_AwardTitle_Campaign1,
Words_AwardText_Campaign1,
Words_AwardTitle_ArcadeHighScore,
Words_AwardText_ArcadeHighScore,
Words_AwardTitle_Bungee,
Words_AwardText_Bungee,
Words_AwardTitle_ArcadeHighScore2,
Words_AwardText_ArcadeHighScore2,
Words_AwardTitle_Die,
Words_AwardText_Die,
Words_AwardTitle_Campaign3,
Words_AwardText_Campaign3,
Words_AwardTitle_Invisible,
Words_AwardText_Invisible,
Words_AwardTitle_Hats,
Words_AwardText_Hats,
Words_AwardTitle_Campaign2,
Words_AwardText_Campaign2,
Words_AwardTitle_UnlockAllArcade,
Words_AwardText_UnlockAllArcade,
Words_AwardTitle_NoDeath,
Words_AwardText_NoDeath,
Words_AwardTitle_Save,
Words_AwardText_Save,
Words_AwardTitle_Obstacles,
Words_AwardText_Obstacles,
Words_AwardTitle_Buy,
Words_AwardText_Buy,
Words_AwardTitle_Campaign4,
Words_AwardText_Campaign4,
Words_AwardTitle_BuyHat,
Words_AwardText_BuyHat,
Words_AwardTitle_HeroRush2Level,
Words_AwardText_HeroRush2Level,
Words_AwardTitle_Replay,
Words_AwardText_Replay,
Words_Buy,
Words_Bank,
Words_Achievement,
Words_AchievementUnlocked,
Words_DeleteSeeds,
Words_DeleteSeedsPlural,
Words_MultiplierIncreased,
Words_JumpHigherNote,
Words_RespawnNoteGamepad,
Words_RespawnNoteKeyboard,
Words_PowerupNote,
Words_Trophy,
Words_TrophyEarned,
Words_Awardment,
Words_Required,
Words_FriendsScores,
Words_TopScores,
Words_MyScores,
Words_SortByLevel,
Words_SortByScore,
Words_ViewGamerCard,
Words_UnlockFullGame,
Words_NotRanked,
Words_NotRankedFriends,
Words_TotalArcade,
Words_Select,
Words_SignIn,
Words_Chapter,
Words_Chapter1,
Words_Chapter2,
Words_Chapter3,
Words_Chapter4,
Words_Chapter5,
Words_Chapter6,
Words_Credits,
Words_PlayerLevel,
Words_Delete,
Words_UpSell_Campaign,
Words_UpSell_Hero,
Words_UpSell_SaveLoad,
Words_UpSell_FreePlay,
Words_UpSell_Exit,
Words_Err_Ok,
Words_Err_YesSelectNewDevice,
Words_Err_NoContinueWithoutDevice,
Words_Err_ReselectStorageDevice,
Words_Err_StorageDeviceRequired,
Words_Err_ForceDisconnectedReselectionMessage,
Words_Err_PromptForDisconnectedMessage,
Words_Err_ForceCancelledReselectionMessage,
Words_Err_PromptForCancelledMessage,
Words_Options_Xbox,
Words_Err_MustBeSignedInToLive,
Words_Err_MustBeSignedInToLiveToPlay,
Words_Err_MustBeSignedInToLive_Header,
Words_Err_MustBeSignedIn,
Words_Err_MustBeSignedInToPlay,
Words_Err_MustBeSignedIn_Header,
Words_Err_QuitForSure,
Words_Err_CorruptLoadHeader,
Words_Err_CorruptLoad,
Words_Err_MustBeSignedInToLiveForLeaderboards,
Words_Err_NoSaveDevice,
Words_Err_ControllerNotConnected,
Words_Achievements,
Words_Leaderboards,
Words_ResumeGame,
Words_PlayGame,

Words_Err_PS3_CorruptLoad,
Words_Err_PS3_NoGamePadDetected,
Words_Err_PS3_PsnRequired_AskToSignIn,
Words_Err_PS3_PsnRequired_WillUploadLater,
Words_Err_PS3_NotEnoughSpace,
Words_Err_PS3_SaveDataNotUsed,
Words_Err_PS3_PsnLoggedOut,
Words_Err_PS3_NotEnoughSpaceForTrophy,
Words_ViewProfile_PS3,
Words_OnlinePermission_PS3,
Words_NotRanked_PS3,
Words_FriendsScores_PS3,
Words_PressStart_PS3,

Words_PressStart_WiiU,
Words_PressToJoin_WiiU,
Words_Press_WiiU,
Words_Press_PS3,

Words_EnumLength
		};

	
		static std::map<Language, std::map<Words, std::wstring> > Text;

		static void ReadTranslationGrid( const std::wstring &path );

	
		static std::wstring LanguageName( Language language );

		static std::wstring WordString( Words Word );

		static std::wstring WordToTextureName( Words Word );

		static std::wstring WordMarkup( Words Word );

		static std::wstring WordMarkup( Words Word, int Size );

		static const int NumLanguages;
		static std::map<Language, boost::shared_ptr<LanguageInfo> > Languages;

	
		static boost::shared_ptr<ContentManager> Content;

	
		static boost::shared_ptr<LanguageInfo> CurrentLanguage;
		static boost::shared_ptr<Texture2D> FontTexture;

		static void LoadFont();

		static void SetLanguage( Language SelectedLanguage );

	
		static void Initialize();

		static float ParseTime( const std::wstring &s );

		static void ReadSubtitleInfo( const std::wstring &VideoName );

	
		static std::vector<boost::shared_ptr<SubtitleAction> > GetSubtitles( const std::wstring &VideoName );

	
		static std::vector<boost::shared_ptr<SubtitleAction> > Subtitles;

		static void ReadSubtitles( const std::wstring &path );
	};

	struct LanguageInfo
	{

	
		Localization::Language MyLanguage;
		std::wstring MyDirectory;
		std::wstring FontSuffix;

		LanguageInfo( Localization::Language MyLanguage, const std::wstring &MyDirectory, const std::wstring &FontSuffix );

	};

	struct SubtitleAction
	{

	
		enum ActionType
		{
			ActionType_SHOW,
			ActionType_HIDE
		};
		/// <summary>
		/// The time the action happens, in seconds.
		/// </summary>
	
		float Time;

		ActionType MyAction;

		std::wstring Text;

		SubtitleAction( ActionType MyAction, float Time, const std::wstring &Text );
		
	};

}


#endif	//#ifndef LOCALIZATION
