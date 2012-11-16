#ifndef LOCALIZATION
#define LOCALIZATION

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Content
			{
				class ContentManager;
			}
		}
	}
}




















namespace CloudberryKingdom
{
	class Localization
	{
	public:
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

	public:
		class LanguageInfo
		{
		public:
			Language MyLanguage;
			std::wstring MyDirectory;

			LanguageInfo( Language MyLanguage, const std::wstring &MyDirectory );
		};

	public:
		class SubtitleAction
		{
		public:
			enum ActionType
			{
				ActionType_SHOW,
				ActionType_HIDE
			};
			/// <summary>
			/// The time the action happens, in seconds.
			/// </summary>
		public:
			float Time;

			ActionType MyAction;

			std::shared_ptr<EzTexture> MyTexture;

			SubtitleAction( ActionType MyAction, float Time, const std::shared_ptr<EzTexture> &MyTexture );
		};

	public:
		enum Words
		{
			Words_IDENTIFIER,
			Words_PRESS_START,
			Words_PRESS_ANY_KEY,
			Words_THE_ARCADE,
			Words_STORY_MODE,
			Words_FREE_PLAY,
			Words_OPTIONS,
			Words_EXIT,
			Words_EXIT_GAME,
			Words_YES,
			Words_NO,
			Words_LANGUAGE,
			Words_SOUND_VOLUME,
			Words_MUSIC_VOLUME,
			Words_CONTROLS,
			Words_EDIT_CONTROLS,
			Words_RESOLUTION,
			Words_FULL_SCREEN,
			Words_WINDOW_BORDER,
			Words_ON,
			Words_OFF,
			Words_QUICK_SPAWN,
			Words_POWER_UP_MENU,
			Words_LEFT,
			Words_RIGHT,
			Words_UP,
			Words_DOWN,
			Words_REPLAY_PREV,
			Words_REPLAY_NEXT,
			Words_REPLAY_TOGGLE,
			Words_TOGGLE_SLOW_MO,
			Words_ACCEPT,
			Words_BACK,
			Words_MENU,
			Words_RESET,
			Words_PRESS_TO_JOIN,
			Words_CUSTOM,
			Words_RANDOM,
			Words_DONE,
			Words_COLOR,
			Words_BEARD,
			Words_HAT,
			Words_CAPE,
			Words_LINING,
			Words_USE,
			Words_CANCEL,
			Words_WHITE,
			Words_SILVER,
			Words_GRAY,
			Words_BLACK,
			Words_CYAN,
			Words_BLUE,
			Words_TEAL,
			Words_INDIGO,
			Words_PURPLE,
			Words_BROWN,
			Words_RED,
			Words_HOT_PINK,
			Words_ORANGE,
			Words_GOLD,
			Words_YELLOW,
			Words_GREEN,
			Words_LIME_GREEN,
			Words_FOREST_GREEN,
			Words_NINJA,
			Words_BRIGHT_WHITE,
			Words_CLEAR,
			Words_RUGGED,
			Words_MANHATTAN,
			Words_LUMBERJACK,
			Words_GOATEE,
			Words_VANDYKE,
			Words_NONE,
			Words_VIKING,
			Words_FEDORA,
			Words_AFRO,
			Words_HALO,
			Words_FIREHEAD,
			Words_HORNS,
			Words_BUBBLE,
			Words_TOP_HAT,
			Words_KNIGHT_HELMET,
			Words_MUSHROOM_HAT,
			Words_OM_NOM_NOM,
			Words_BRAIN_HAT,
			Words_GOSU,
			Words_ROBIN_HOOD,
			Words_REGGAE,
			Words_PUMPKIN,
			Words_PIRATE_HAT,
			Words_HARD_HAT,
			Words_FOUR_EYES,
			Words_BUNNY_EARS,
			Words_ANTLERS,
			Words_ARROW_THROUGH_HEAD,
			Words_BROWN_BAG,
			Words_TRAFFIC_CONE,
			Words_POPE_HAT,
			Words_RICE_HAT,
			Words_SANTA_CLAUS,
			Words_SOMBRERO,
			Words_TIKI_MASK,
			Words_WIZARD,
			Words_LOCATION,
			Words_GAME,
			Words_CLASSIC_GAME,
			Words_WALL_LEVEL,
			Words_BUNGEE,
			Words_HERO,
			Words_DIFFICULTY,
			Words_TRAINING,
			Words_UNPLEASANT,
			Words_ABUSIVE,
			Words_HARDCORE,
			Words_MASOCHISTIC,
			Words_LENGTH,
			Words_CHECKPOINTS,
			Words_START,
			Words_CONTINUE,
			Words_LOAD_LEVEL,
			Words_HERO_FACTORY,
			Words_BASE,
			Words_JUMP,
			Words_SHAPE,
			Words_PLAY,
			Words_TEST,
			Words_PASSIVE,
			Words_AGGRESSIVE,
			Words_NEXT,
			Words_JUMP_DIFFICULTY,
			Words_LEVEL_SPEED,
			Words_CEILINGS,
			Words_MOVING_BLOCKS,
			Words_GHOST_BLOCKS,
			Words_FALLING_BLOCKS,
			Words_ELEVATORS,
			Words_CLOUDS,
			Words_BOUNCY_BLOCKS,
			Words_PENDULUMS,
			Words_FLYING_BLOBS,
			Words_FIRESPINNERS,
			Words_BOULDERS,
			Words_SPIKEY_GUYS,
			Words_LASERS,
			Words_SPIKES,
			Words_SLUDGE,
			Words_SERPENT,
			Words_SPIKEY_LINES,
			Words_FIREBALLS,
			Words_ACCELERATION,
			Words_MAX_VELOCITY,
			Words_SIZE,
			Words_GRAVITY,
			Words_MAX_FALL_SPEED,
			Words_FRICTION,
			Words_JUMP_LENGTH,
			Words_JUMP_ACC,
			Words_NUM_JUMPS,
			Words_DOUBLE_JUMP_LENGTH,
			Words_DOUBLE_JUMP_ACCEL,
			Words_JETPACK_ACC,
			Words_JETPACK_FUEL,
			Words_PHASED_SIZE,
			Words_PHASED_GRAVITY,
			Words_PHASE_PERIOD,
			Words_CLASSIC_HERO,
			Words_JETMAN,
			Words_DOUBLE_JUMP,
			Words_TINY_BOB,
			Words_WHEELIE,
			Words_SPACESHIP,
			Words_HERO_IN_ABOX,
			Words_BOUNCY,
			Words_ROCKETBOX,
			Words_FAT_BOB,
			Words_PHASE_BOB,
			Words_VIRIDIAN,
			Words_TIME_MASTER,
			Words_MEATBOY,
			Words_JETPACK_WHEELIE,
			Words_FACTORY,
			Words_SEA,
			Words_HILLS,
			Words_FOREST,
			Words_CLOUD,
			Words_CAVE,
			Words_CASTLE,
			Words_THE_BEGINNING,
			Words_THE_NEXT_NINETY_NINE,
			Words_AGAUNTLET_OF_DOOM,
			Words_ALMOST_HERO,
			Words_THE_MASOCHIST,
			Words_ESCALATION,
			Words_TIME_CRISIS,
			Words_HERO_RUSH,
			Words_HYBRID_RUSH,
			Words_HIGH_SCORE,
			Words_BEST_LEVEL,
			Words_LEADERBOARD,
			Words_SCORE,
			Words_LEVEL,
			Words_READY,
			Words_GO,
			Words_GET_TO_THE_EXIT,
			Words_SECONDS_ON_THE_CLOCK,
			Words_COINS_ADD_SECONDS,
			Words_GET_AHIGH_SCORE,
			Words_PERFECT,
			Words_EXTRA_LIFE,
			Words_PRESS,
			Words_RESUME,
			Words_STATISTICS,
			Words_SAVE_LOAD,
			Words_REMOVE_ME,
			Words_EXIT_LEVEL,
			Words_RANDOM_SEED,
			Words_SAVE_SEED,
			Words_LOAD_SEED,
			Words_COPY_TO_CLIPBOARD,
			Words_LOAD_FROM_CLIPBOARD,
			Words_REMOVE_PLAYER_QUESTION,
			Words_EXIT_LEVEL_QUESTION,
			Words_SAVE_RANDOM_SEED_AS,
			Words_SAVED_SEEDS,
			Words_LOAD_THE_FOLLOWING_SEED_QUESTION,
			Words_SEED_SAVED_SUCCESSFULLY,
			Words_HOORAY,
			Words_NO_NAME_GIVEN,
			Words_OH,
			Words_LEVELS_BEAT,
			Words_JUMPS,
			Words_COINS,
			Words_GRABBED,
			Words_COINS_OUT_OF,
			Words_PERCENT,
			Words_AVERAGE_LIFE,
			Words_DEATHS,
			Words_FIREBALL,
			Words_FIRESPINNER,
			Words_BOULDER,
			Words_SPIKEY_GUY,
			Words_SPIKE,
			Words_FALLING,
			Words_LAVA,
			Words_BLOB,
			Words_LASER,
			Words_FALLING_SPIKEY,
			Words_TIME_LIMIT,
			Words_LEFT_BEHIND,
			Words_OTHER,
			Words_TOTAL,
			Words_GAME_OVER,
			Words_NEW_HIGH_SCORE,
			Words_PLAY_AGAIN,
			Words_HIGH_SCORES,
			Words_LOCAL,
			Words_GLOBAL,
			Words_WATCH_COMPUTER,
			Words_SHOW_PATH,
			Words_ACTIVATE_SLOW_MO,
			Words_PAUSED,
			Words_SPEED,
			Words_STEP,
			Words_LEVEL_CLEARED,
			Words_KEEP_SETTINGS,
			Words_WATCH_REPLAY,
			Words_BACK_TO_FREEPLAY,
			Words_PAUSE,
			Words_SINGLE,
			Words_PREVIOUS,
			Words_ALL,
			Words_END,
			Words_LOADING,
			Words_HERO_UNLOCKED,
			Words_NEW_HERO_UNLOCKED,
			Words_BUY,
			Words_HATS_FOR_SALE,
			Words_BANK,
			Words_ACHIEVEMENT,
			Words_ACHIEVEMENT_UNLOCKED,
			Words_DELETE_SEEDS,
			Words_DELETE_SEEDS_PLURAL,
			Words_MULTIPLIER_INCREASED,
			Words_JUMP_HIGHER_NOTE,
			Words_RESPAWN_NOTE_GAMEPAD,
			Words_RESPAWN_NOTE_KEYBOARD,
			Words_POWERUP_NOTE
		};

	private:
		static std::unordered_map<Language, std::unordered_map<Words, std::wstring> > Text;

		static void ReadTranslationGrid( const std::wstring &path );

	public:
		static std::wstring WordString( Words Word );

		static std::wstring WordToTextureName( Words Word );

		static std::wstring WordMarkup( Words Word );

		static std::wstring WordMarkup( Words Word, int Size );

		static const int NumLanguages = 10;
		static std::unordered_map<Language, LanguageInfo*> Languages;

	private:
		static std::shared_ptr<ContentManager> Content;

	public:
		static std::shared_ptr<LanguageInfo> CurrentLanguage;

		static void SetLanguage( Language SelectedLanguage );

	private:
		static void Initialize();

		static void ReadSubtitleInfo( const std::wstring &VideoName );

	public:
		static std::vector<SubtitleAction*> GetSubtitles( const std::wstring &VideoName );

	private:
		static std::vector<SubtitleAction*> Subtitles;

		static void ReadSubtitles( const std::wstring &path );
	};
}


#endif	//#ifndef LOCALIZATION
