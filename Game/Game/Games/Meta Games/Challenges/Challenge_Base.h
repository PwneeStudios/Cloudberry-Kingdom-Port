#ifndef CHALLENGE_BASE
#define CHALLENGE_BASE

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class StringWorldGameData;
}

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}


namespace CloudberryKingdom
{
	class AftermathData
	{
	public:
		bool Success;
		bool EarlyExit;
		bool Retry;

	private:
		void InitializeInstanceFields();

public:
		AftermathData()
		{
			InitializeInstanceFields();
		}
	};

	class Challenge
	{
	protected:
		class ShowEndScreenProxy : public Lambda
		{
		private:
			std::shared_ptr<Challenge> challenge;

		public:
			ShowEndScreenProxy( const std::shared_ptr<Challenge> &challenge );

			void Apply();
		};

	public:
		static std::shared_ptr<BobPhsx> ChosenHero;
	private:
		static const int LevelMask = 10000;

	public:
		std::vector<int> StartLevels;

		Localization::Words Name, MenuName;

		int GameId_Score, GameId_Level;
	protected:
		int GameTypeId;

	public:
		int SetGameId();

	protected:
		const std::shared_ptr<StringWorldGameData> &getStringWorld() const;

		/// <summary>
		/// Get the top score that anyone on this machine has ever gotten.
		/// </summary>
	public:
		int TopScore();

		/// <summary>
		/// Get the highest level that anyone on this machine has ever gotten.
		/// </summary>
		int TopLevel();

		/// <summary>
		/// Get the top score that anyone playing has ever gotten.
		/// </summary>
		int TopPlayerScore();

		/// <summary>
		/// Get the highest level that anyone playing has ever gotten.
		/// </summary>
		int TopPlayerLevel();

	protected:
		virtual void ShowEndScreen();

		/// <summary>
		/// If true then this meta-game is not part of the campaign.
		/// </summary>
	public:
		bool NonCampaign;
		virtual void Start( int Difficulty );

		/// <summary>
		/// The difficulty selected for this challenge.
		/// </summary>
		int DifficultySelected;

		/// <summary>
		/// Called immediately after the end of the challenge.
		/// </summary>
		void Aftermath();

	protected:
		virtual void SetGameParent( const std::shared_ptr<GameData> &game );

	public:
		virtual std::shared_ptr<LevelSeedData> GetSeed( int Index ) = 0;

	private:
		void InitializeInstanceFields();

public:
		Challenge()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef CHALLENGE_BASE
