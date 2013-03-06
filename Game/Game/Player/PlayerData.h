#ifndef PLAYERDATA
#define PLAYERDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	
	struct PlayerData : public SaveLoad
	{

		virtual ~PlayerData()
		{
#ifdef BOOST_BIN
			OnDestructor( "PlayerData" );
#endif
		}


		boost::shared_ptr<SavedSeeds> MySavedSeeds;

		PlayerIndex MyPlayerIndex;
		bool Exists, IsAlive;

		boost::shared_ptr<Set<int> > Purchases;
//C# TO C++ CONVERTER NOTE: The variable Awardments was renamed since it is named the same as a user-defined type:
		boost::shared_ptr<Set<int> > Awardments_Renamed;

		std::map<int, boost::shared_ptr<ScoreEntry> > HighScores;

		int CampaignLevel, CampaignCoins, CampaignIndex;

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

		boost::shared_ptr<PlayerStats> LifetimeStats, GameStats, LevelStats, TempStats;
		boost::shared_ptr<PlayerStats> CampaignStats;

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)
		boost::shared_ptr<Gamer> _MyGamer;
		const boost::shared_ptr<Gamer> &getMyGamer() const;
#endif

		PlayerData();

		#pragma region WriteRead
	
		virtual void Serialize( const boost::shared_ptr<BinaryWriter> &writer );

		virtual void FailLoad();

		virtual void Deserialize( std::vector<unsigned char> Data );
		void ProcessChunk( boost::shared_ptr<Chunk> chunk );
		#pragma endregion

		int LastPlayerLevelUpload;
	
		int GetTotalLevel();
        int GetTotalCampaignLevel();
        int GetTotalCampaignIndex();
		int GetTotalArcadeLevel();

		int GetHighScore( int GameId );

		void AddHighScore( const boost::shared_ptr<ScoreEntry> &score );

		const boost::shared_ptr<PlayerStats> &getStats() const;
		boost::shared_ptr<PlayerStats> GetStats( StatGroup group );

		boost::shared_ptr<PlayerStats> GetSummedStats( StatGroup group );

	
//ORIGINAL LINE: PlayerStats SumStats(params StatGroup[] group)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		boost::shared_ptr<PlayerStats> SumStats( const std::vector<StatGroup> &group );

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
		boost::shared_ptr<Gamer> CheckForMatchingGamer();
#endif
		/// <summary>
		/// Gets the color that the player's name should be drawn with.
		/// </summary>
		Vector4 GetTextColor();

		/// <summary>
		/// Sets the color of text to match the color of the player.
		/// </summary>
		void SetNameText( const boost::shared_ptr<EzText> &text );

		std::wstring GetName();

		void Init( int Index );

		void Init();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef PLAYERDATA
