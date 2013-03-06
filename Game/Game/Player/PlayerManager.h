#ifndef PLAYERMANAGER
#define PLAYERMANAGER

#include <global_header.h>

namespace CloudberryKingdom
{

	struct PlayerIntLambda : public LambdaFunc_1<boost::shared_ptr<PlayerData> , int>
	{
	
		PlayerIntLambda();

		int Apply( const boost::shared_ptr<PlayerData> &p );

	};

	struct UserPowers
	{
		/// <summary>
		/// Whether the user can skip the beginning of the screen saver.
		/// </summary>
	
		static bool CanSkipScreensaver;

		/// <summary>
		/// Whether the user can skip a movie.
		/// </summary>
		static Set<std::wstring> WatchedVideo;

		/// <summary>
		/// Set the value of a variable and make sure the variable is persisted to disk.
		/// </summary>
		static void Set( bool &variable, bool value );

		static void SetToSave();
	};

	struct _SavePlayerData : public SaveLoad
	{

		virtual ~_SavePlayerData()
		{
#ifdef BOOST_BIN
			OnDestructor( "_SavePlayerData" );
#endif
		}

	
		_SavePlayerData();

		/// <summary>
		/// When true the user has specified a preference for resolution (and fullscreen-ness)
		/// </summary>
		bool ResolutionPreferenceSet;

	
		virtual void Serialize( const boost::shared_ptr<BinaryWriter> &writer );

		virtual void Deserialize( std::vector<unsigned char> Data );

		static void ProcessChunk( boost::shared_ptr<Chunk> chunk );
	
		void InitializeInstanceFields();
	};

	struct RezData
	{
	
		bool Custom, Fullscreen;
		int Width, Height;

		RezData() : Custom( false ), Fullscreen( false ), Width( 0 ), Height( 0 ) { }
	};

	struct PlayerManager
	{

	
		static void InitializeStatics();

	
		struct SaveRezAndKeysLambda : public Lambda_1<boost::shared_ptr<BinaryWriter> >
		{
		
			SaveRezAndKeysLambda();

			void Apply( const boost::shared_ptr<BinaryWriter> &writer );
		};

	
		struct LoadRezAndKeysLambda : public Lambda_1<std::vector<unsigned char> >
		{
		
			LoadRezAndKeysLambda();

			void Apply( const std::vector<unsigned char> &Data );
		};

		struct LoadRezAndKeysFailLambda : public Lambda
		{
		
			LoadRezAndKeysFailLambda();

			void Apply();
		};
	
		struct GetGroupGamerTagNameLength : public LambdaFunc_1<boost::shared_ptr<StringBuilder>, float>
		{
		
			float Apply( const boost::shared_ptr<StringBuilder> &name );
		};

	
		struct AnyAwardmentLambda : public LambdaFunc_1<boost::shared_ptr<PlayerData> , bool>
		{
		
			boost::shared_ptr<Awardment> award;
		
			AnyAwardmentLambda( const boost::shared_ptr<Awardment> &award );

			bool Apply( const boost::shared_ptr<PlayerData> &player );
		};

	
		struct AnyBoughtLambda : public LambdaFunc_1<boost::shared_ptr<PlayerData> , bool>
		{
		
			boost::shared_ptr<Buyable> item;
		
			AnyBoughtLambda( const boost::shared_ptr<Buyable> &item );

			bool Apply( const boost::shared_ptr<PlayerData> &player );
		};

	
		struct BankLambda : public PlayerIntLambda
		{
		
			int Apply( const boost::shared_ptr<PlayerData> &p );

		};

	
		struct NotAllAwardedLambda : public LambdaFunc_1<boost::shared_ptr<PlayerData> , bool>
		{
		
			boost::shared_ptr<Awardment> award;
		
			NotAllAwardedLambda( const boost::shared_ptr<Awardment> &award );

			bool Apply( const boost::shared_ptr<PlayerData> &player );
		};

	
#if defined(XBOX) || defined(XBOX_SIGNIN)
		struct ExistingPlayerFindLambda : public LambdaFunc_1<boost::shared_ptr<PlayerData> , bool>
		{
		
			ExistingPlayerFindLambda();

			bool Apply( const boost::shared_ptr<PlayerData> &player );
		};
#endif

#if defined(PC_VERSION) || defined(WINDOWS)
#endif
#if defined(PC_VERSION)
	
		static void SaveRezAndKeys();

	
		static void _SaveRezAndKeys( const boost::shared_ptr<BinaryWriter> &writer );

		static RezData d;
	
		static RezData LoadRezAndKeys();

	
		static void _LoadRezAndKeys( std::vector<unsigned char> Data );
        static void _Fail();
#endif
	
		static bool PartiallyInvisible, TotallyInvisible;

	
		static int _CoinsSpent;
	
		const static int &getCoinsSpent();
		static void setCoinsSpent( const int &value );

		static boost::shared_ptr<_SavePlayerData> SavePlayerData;
#if defined(PC_VERSION)
	
		static std::wstring _DefaultName;
	
		const static std::wstring &getDefaultName();
		static void setDefaultName( const std::wstring &value );
#endif

		static void UploadCampaignLevels();
		static void UploadPlayerLevels();

		static void CleanTempStats();

		static void AbsorbTempStats();

		static void AbsorbLevelStats();

		static void AbsorbGameStats();

		// Random names
		static std::vector<std::wstring> RandomNames;

		static int FirstPlayer;
		static bool HaveFirstPlayer;
		static int GetFirstPlayer();

		static int NumPlayers;
		static std::vector<boost::shared_ptr<PlayerData> > Players;

	
		static int length( std::vector<boost::shared_ptr<StringBuilder> > &names );

		/// <summary>
		/// Return a string representing the names of all players playing
		/// </summary>
		/// <returns></returns>
	
		static std::wstring GetGroupGamerTag( int MaxLength );

		static int MaxPlayerHighScore( int GameId );


		static int MaxPlayerTotalArcadeLevel();
		static int MinPlayerTotalCampaignLevel();
		static int MinPlayerTotalCampaignIndex();
		static int MaxPlayerTotalLevel();

		/// <summary>
		/// Returns true if any of the current players has been awarded the specified awardment.
		/// </summary>
		static bool Awarded( const boost::shared_ptr<Awardment> &award );

		/// <summary>
		/// Returns true if any of the current players has been bought the specified hat.
		/// </summary>
		static bool Bought( const boost::shared_ptr<Buyable> &item );

		/// <summary>
		/// Returns true if any of the current players has been bought the specified hat, or it's free.
		/// </summary>
		static bool BoughtOrFree( const boost::shared_ptr<Buyable> &item );

		/// <summary>
		/// The combined bank accounts of all current players.
		/// </summary>
		static int CombinedBank();

		static void DeductCost( int Cost );

		static void GiveBoughtItem( const boost::shared_ptr<Buyable> &buyable );

		/// <summary>
		/// Returns true if any of the current players has NOT been awarded the specified awardment.
		/// </summary>
		static bool NotAllAwarded( const boost::shared_ptr<Awardment> &award );

		/// <summary>
		/// Returns the sum of all player's current game score.
		/// </summary>
		static int GetGameScore();

		/// <summary>
		/// Returns the sum of all player's current game score.
		/// </summary>
		static int GetGameScore_WithTemporary();

		static int PlayerSum( const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<PlayerData> , int> > &f );

		static int PlayerMax( const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<PlayerData> , int> > &f );

		/// <summary>
		/// Returns the total coins gotten in a level by all players.
		/// </summary>
		static int GetLevelCoins();

		/// <summary>
		/// A list of all players that exist and are logged in.
		/// </summary>
		const static std::vector<boost::shared_ptr<PlayerData> > getLoggedInPlayers();

#if defined(XBOX) || defined(XBOX_SIGNIN)
#endif
		/// <summary>
		/// A list of all players currently existing.
		/// </summary>
		const static std::vector<boost::shared_ptr<PlayerData> > getExistingPlayers();
		static std::vector<boost::shared_ptr<PlayerData> > _ExistingPlayers;

		/// <summary>
		/// A list of all players currently alive.
		/// </summary>
		const static std::vector<boost::shared_ptr<PlayerData> > &getAlivePlayers();
		static std::vector<boost::shared_ptr<PlayerData> > _AlivePlayers;


		static int NumAlivePlayers();
		static int NumExistingPlayers();

#if defined(PC_VERSION)
		const static boost::shared_ptr<PlayerData> &getPlayer();
#endif

		static boost::shared_ptr<PlayerData> Get( int i );
		static boost::shared_ptr<PlayerData> Get( PlayerIndex Index );
		static boost::shared_ptr<PlayerData> Get( const boost::shared_ptr<Bob> &bob );

		static int Score_Blobs, Score_Coins, Score_Attempts, Score_Time;
		static void CalcScore( StatGroup group );

		static bool Showed_ShouldCheckOutWorlds;
		static int Showed_ShouldLeaveLevel, Showed_ShouldWatchComputer;


		static int GetNumPlayers();

		/// <summary>
		/// Whether all the players are dead.
		/// </summary>
		static bool AllDead();

		/// <summary>
		/// Whether all the players are off the screen
		/// </summary>
		static bool AllOffscreen();

		static bool IsAlive( PlayerIndex PIndex );

		static int GetIndexFromPlayerIndex( PlayerIndex PIndex );

		static void KillPlayer( PlayerIndex PIndex );

		static void ReviveBob( const boost::shared_ptr<Bob> &bob );

		static void RevivePlayer( PlayerIndex PIndex );

		static void Init();
	};
}


#endif	//#ifndef PLAYERMANAGER
