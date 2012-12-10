#ifndef PLAYERDATA
#define PLAYERDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct PlayerData : public SaveLoad
	{
	
		std::shared_ptr<SavedSeeds> MySavedSeeds;

		PlayerIndex MyPlayerIndex;
		bool Exists, IsAlive;

		std::shared_ptr<Set<int> > Purchases;
//C# TO C++ CONVERTER NOTE: The variable Awardments was renamed since it is named the same as a user-defined type:
		std::shared_ptr<Set<int> > Awardments_Renamed;

		std::map<int, std::shared_ptr<ScoreEntry> > HighScores;

		int CampaignLevel, CampaignCoins;

		int MyIndex;

	
		int RandomNameIndex;

		/// <summary>
		/// If this player data is or was associated with a gamer tag, this is the name of the gamer tag.
		/// </summary>
	
		std::wstring StoredName;

		/// <summary>
		/// If true the player used a keyboard instead of a gamepad for the last movement input.
		/// </summary>
		bool KeyboardUsedLast;

//C# TO C++ CONVERTER NOTE: The variable ColorScheme was renamed since it is named the same as a user-defined type:
		ColorScheme ColorScheme_Renamed;
		ColorScheme CustomColorScheme;
		int ColorSchemeIndex;

		std::shared_ptr<PlayerStats> LifetimeStats, GameStats, LevelStats, TempStats;
		std::shared_ptr<PlayerStats> CampaignStats;

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)
		std::shared_ptr<Gamer> _MyGamer;
		const std::shared_ptr<Gamer> &getMyGamer() const;
#endif

		PlayerData();

		#pragma region WriteRead
	
		virtual void Serialize( const std::shared_ptr<BinaryWriter> &writer );

		virtual void FailLoad();

		virtual void Deserialize( std::vector<unsigned char> Data );
		#pragma endregion

	
		int GetHighScore( int GameId );

		void AddHighScore( const std::shared_ptr<ScoreEntry> &score );

		const std::shared_ptr<PlayerStats> &getStats() const;
		std::shared_ptr<PlayerStats> GetStats( StatGroup group );

		std::shared_ptr<PlayerStats> GetSummedStats( StatGroup group );

	
//ORIGINAL LINE: PlayerStats SumStats(params StatGroup[] group)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		std::shared_ptr<PlayerStats> SumStats( const std::vector<StatGroup> &group );

		/// <summary>
		/// Get the the players current score for the game,
		/// adding up the current level's score with the current game score.
		/// </summary>
	
		int GetGameScore();

		/// <summary>
		/// Returns the total coins gotten in a level
		/// </summary>
		int GetLevelCoins();

		int RunningCampaignScore();

		int Bank();

#if defined(XBOX) || defined(XBOX_SIGNIN)
		std::shared_ptr<Gamer> CheckForMatchingGamer();
#endif
		/// <summary>
		/// Gets the color that the player's name should be drawn with.
		/// </summary>
		Vector4 GetTextColor();

		/// <summary>
		/// Sets the color of text to match the color of the player.
		/// </summary>
		void SetNameText( const std::shared_ptr<EzText> &text );

		std::wstring GetName();

		void Init( int Index );

		void Init();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PLAYERDATA
