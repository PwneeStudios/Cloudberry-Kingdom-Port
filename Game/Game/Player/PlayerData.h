#ifndef PLAYERDATA
#define PLAYERDATA

#include "../Game/Tools/EzStorage.h"
#include "Awardments/Awardment.h"
#include "ColorScheme.h"
#include "Stats.h"
#include <string>
#include <unordered_map>

namespace CloudberryKingdom
{
	class SavedSeeds;
}

namespace CloudberryKingdom
{
	class Set;
}

namespace CloudberryKingdom
{
	class ScoreEntry;
}

namespace CloudberryKingdom
{
	class PlayerStats;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace GamerServices
			{
				class Gamer;
			}
		}
	}
}

namespace CloudberryKingdom
{
	class EzText;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)
using namespace Microsoft::Xna::Framework::GamerServices;
#endif




namespace CloudberryKingdom
{
	class PlayerData : public SaveLoad
	{
	public:
		std::shared_ptr<SavedSeeds> MySavedSeeds;

		PlayerIndex MyPlayerIndex;
		bool Exists, IsAlive;

		std::shared_ptr<Set<int> > Purchases;
//C# TO C++ CONVERTER NOTE: The variable Awardments was renamed since it is named the same as a user-defined type:
		std::shared_ptr<Set<int> > Awardments_Renamed;

		std::unordered_map<int, ScoreEntry*> HighScores;

		int CampaignLevel, CampaignCoins;

		int MyIndex;

	private:
		int RandomNameIndex;

		/// <summary>
		/// If this player data is or was associated with a gamer tag, this is the name of the gamer tag.
		/// </summary>
	public:
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
	protected:
		virtual void Serialize( const std::shared_ptr<BinaryWriter> &writer );

		virtual void FailLoad();

		virtual void Deserialize( std::vector<unsigned char> Data );
		#pragma endregion

	public:
		int GetHighScore( int GameId );

		void AddHighScore( const std::shared_ptr<ScoreEntry> &score );

		const std::shared_ptr<PlayerStats> &getStats() const;
		std::shared_ptr<PlayerStats> GetStats( StatGroup group );

		std::shared_ptr<PlayerStats> GetSummedStats( StatGroup group );

	private:
//ORIGINAL LINE: PlayerStats SumStats(params StatGroup[] group)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		std::shared_ptr<PlayerStats> SumStats( ... );

		/// <summary>
		/// Get the the players current score for the game,
		/// adding up the current level's score with the current game score.
		/// </summary>
	public:
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

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PLAYERDATA
