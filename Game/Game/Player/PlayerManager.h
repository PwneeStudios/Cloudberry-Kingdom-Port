#ifndef PLAYERMANAGER
#define PLAYERMANAGER

#include <global_header.h>

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class Awardment;
}

namespace CloudberryKingdom
{
	class Buyable;
}

namespace CloudberryKingdom
{
	class LambdaFunc_1;
}

namespace CloudberryKingdom
{
	class Bob;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Input;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;


#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)
using namespace Microsoft::Xna::Framework::GamerServices;
#endif



namespace CloudberryKingdom
{
	class PlayerIntLambda : public LambdaFunc_1<PlayerData*, int>
	{
	public:
		PlayerIntLambda();

		virtual int Apply( const std::shared_ptr<PlayerData> &p );
	};

	class UserPowers
	{
		/// <summary>
		/// Whether the user can skip the beginning of the screen saver.
		/// </summary>
	public:
		static bool CanSkipScreensaver;

		/// <summary>
		/// Whether the user can skip a movie.
		/// </summary>
		static std::shared_ptr<CloudberryKingdom::Set<std::wstring> > WatchedVideo;

		/// <summary>
		/// Set the value of a variable and make sure the variable is persisted to disk.
		/// </summary>
		static void Set( bool &variable, bool value );

		static void SetToSave();
	};

	class _SavePlayerData : public SaveLoad
	{
	public:
		_SavePlayerData();

		/// <summary>
		/// When true the user has specified a preference for resolution (and fullscreen-ness)
		/// </summary>
		bool ResolutionPreferenceSet;

	protected:
		virtual void Serialize( const std::shared_ptr<BinaryWriter> &writer );

		virtual void Deserialize( std::vector<unsigned char> Data );

	private:
		void InitializeInstanceFields();
	};

	class PlayerManager
	{
	public:
		class RezData
		{
		public:
			bool Custom, Fullscreen;
			int Width, Height;
		};
	private:
		class SaveRezAndKeysLambda : public Lambda_1<BinaryWriter*>
		{
		public:
			SaveRezAndKeysLambda();

			void Apply( const std::shared_ptr<BinaryWriter> &writer );
		};

	private:
		class LoadRezAndKeysLambda : public Lambda_1<std::vector<unsigned char> >
		{
		public:
			LoadRezAndKeysLambda();

			void Apply( std::vector<unsigned char> Data );
		};

	private:
		class GetGroupGamerTagNameLength : public LambdaFunc_1<StringBuilder*, float>
		{
		public:
			float Apply( const std::shared_ptr<StringBuilder> &name );
		};

	private:
		class AnyAwardmentLambda : public LambdaFunc_1<PlayerData*, bool>
		{
		private:
			std::shared_ptr<Awardment> award;
		public:
			AnyAwardmentLambda( const std::shared_ptr<Awardment> &award );

			bool Apply( const std::shared_ptr<PlayerData> &player );
		};

	private:
		class AnyBoughtLambda : public LambdaFunc_1<PlayerData*, bool>
		{
		private:
			std::shared_ptr<Buyable> item;
		public:
			AnyBoughtLambda( const std::shared_ptr<Buyable> &item );

			bool Apply( const std::shared_ptr<PlayerData> &player );
		};

	private:
		class BankLambda : public PlayerIntLambda
		{
		public:
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	private:
		class NotAllAwardedLambda : public LambdaFunc_1<PlayerData*, bool>
		{
		private:
			std::shared_ptr<Awardment> award;
		public:
			NotAllAwardedLambda( const std::shared_ptr<Awardment> &award );

			bool Apply( const std::shared_ptr<PlayerData> &player );
		};

	private:
		class ExistingPlayerFindLambda : public LambdaFunc_1<PlayerData*, bool>
		{
		public:
			ExistingPlayerFindLambda();

			bool Apply( const std::shared_ptr<PlayerData> &player );
		};
#if defined(PC_VERSION) || defined(WINDOWS)
#endif
#if defined(PC_VERSION)
	public:
		static void SaveRezAndKeys();

	private:
		static void _SaveRezAndKeys( const std::shared_ptr<BinaryWriter> &writer );

		static RezData d;
	public:
		static RezData LoadRezAndKeys();

	private:
		static void _LoadRezAndKeys( std::vector<unsigned char> Data );
#endif
	public:
		static bool PartiallyInvisible, TotallyInvisible;

	private:
		static int _CoinsSpent;
	public:
		const static int &getCoinsSpent() const;
		static void setCoinsSpent( const int &value );

		static std::shared_ptr<_SavePlayerData> SavePlayerData;
#if defined(PC_VERSION)
	private:
		static std::wstring _DefaultName;
	public:
		const static std::wstring &getDefaultName() const;
		static void setDefaultName( const std::wstring &value );
#endif

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
		static std::vector<PlayerData*> Players;

	private:
		static int length( std::vector<StringBuilder*> &names );

		/// <summary>
		/// Return a string representing the names of all players playing
		/// </summary>
		/// <returns></returns>
	public:
		static std::wstring GetGroupGamerTag( int MaxLength );

		static int MaxPlayerHighScore( int GameId );

		/// <summary>
		/// Returns true if any of the current players has been awarded the specified awardment.
		/// </summary>
		static bool Awarded( const std::shared_ptr<Awardment> &award );

		/// <summary>
		/// Returns true if any of the current players has been bought the specified hat.
		/// </summary>
		static bool Bought( const std::shared_ptr<Buyable> &item );

		/// <summary>
		/// Returns true if any of the current players has been bought the specified hat, or it's free.
		/// </summary>
		static bool BoughtOrFree( const std::shared_ptr<Buyable> &item );

		/// <summary>
		/// The combined bank accounts of all current players.
		/// </summary>
		static int CombinedBank();

		static void DeductCost( int Cost );

		static void GiveBoughtItem( const std::shared_ptr<Buyable> &buyable );

		/// <summary>
		/// Returns true if any of the current players has NOT been awarded the specified awardment.
		/// </summary>
		static bool NotAllAwarded( const std::shared_ptr<Awardment> &award );

		/// <summary>
		/// Returns the sum of all player's current game score.
		/// </summary>
		static int GetGameScore();

		/// <summary>
		/// Returns the sum of all player's current game score.
		/// </summary>
		static int GetGameScore_WithTemporary();

		static int PlayerSum( const std::shared_ptr<LambdaFunc_1<PlayerData*, int> > &f );

		static int PlayerMax( const std::shared_ptr<LambdaFunc_1<PlayerData*, int> > &f );

		/// <summary>
		/// Returns the total coins gotten in a level by all players.
		/// </summary>
		static int GetLevelCoins();

		/// <summary>
		/// A list of all players that exist and are logged in.
		/// </summary>
		const static std::vector<PlayerData*> &getLoggedInPlayers() const;

#if defined(XBOX) || defined(XBOX_SIGNIN)
#endif
		/// <summary>
		/// A list of all players currently existing.
		/// </summary>
		const static std::vector<PlayerData*> &getExistingPlayers() const;
		static std::vector<PlayerData*> _ExistingPlayers;

		/// <summary>
		/// A list of all players currently alive.
		/// </summary>
		const static std::vector<PlayerData*> &getAlivePlayers() const;
		static std::vector<PlayerData*> _AlivePlayers;

#if defined(PC_VERSION)
		const static std::shared_ptr<PlayerData> &getPlayer() const;
#endif

		static std::shared_ptr<PlayerData> Get( int i );
		static std::shared_ptr<PlayerData> Get( PlayerIndex Index );
		static std::shared_ptr<PlayerData> Get( const std::shared_ptr<Bob> &bob );

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

		static void ReviveBob( const std::shared_ptr<Bob> &bob );

		static void RevivePlayer( PlayerIndex PIndex );

		static void Init();
	};
}


#endif	//#ifndef PLAYERMANAGER
