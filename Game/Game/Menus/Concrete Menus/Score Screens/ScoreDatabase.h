#ifndef SCOREDATABASE
#define SCOREDATABASE

#include <global_header.h>

namespace CloudberryKingdom
{
	class ScoreEntry;
}

namespace CloudberryKingdom
{
	class ScoreList;
}




namespace CloudberryKingdom
{
	class ScoreDatabase : public SaveLoad
	{
	private:
		static std::shared_ptr<ScoreDatabase> Instance;

	public:
		static int MostRecentScoreDate;
		static int CurrentDate();

		static int Capacity;

	private:
		static std::unordered_map<int, std::vector<ScoreEntry*> > Games;

	public:
		static void Initialize();

		#pragma region SaveLoad
	protected:
		virtual void Serialize( const std::shared_ptr<BinaryWriter> &writer );
		virtual void FailLoad();
		virtual void Deserialize( std::vector<unsigned char> Data );
		#pragma endregion

	public:
		static void EnsureList( int Game );

		static std::shared_ptr<ScoreList> GetList( int Game );

		/// <summary>
		/// Whether the given score qualifies for the high score list
		/// </summary>
		static bool Qualifies( int Game, int Score );

		/// <summary>
		/// Return the score with the smallest value.
		/// </summary>
	private:
		static std::shared_ptr<ScoreEntry> Max( std::vector<ScoreEntry*> &Scores );

	public:
		static std::shared_ptr<ScoreEntry> Max( int GameId );

		/// <summary>
		/// Return the score with the smallest value.
		/// </summary>
		static std::shared_ptr<ScoreEntry> Min( std::vector<ScoreEntry*> &Scores );

		static std::shared_ptr<ScoreEntry> Min( int GameId );

		static void Add( const std::shared_ptr<ScoreEntry> &score );

		/// <summary>
		/// Remove excess entries, if the list is over capacity.
		/// </summary>
	private:
		static void TrimExcess( std::vector<ScoreEntry*> &Scores );

		static int ScoreCompare( const std::shared_ptr<ScoreEntry> &score1, const std::shared_ptr<ScoreEntry> &score2 );

		/// <summary>
		/// Sort the list by value.
		/// </summary>
		static void Sort( std::vector<ScoreEntry*> &Scores );
	};
}


#endif	//#ifndef SCOREDATABASE
