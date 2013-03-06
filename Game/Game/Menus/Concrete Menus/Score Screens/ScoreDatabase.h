#ifndef SCOREDATABASE
#define SCOREDATABASE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ScoreDatabase : public SaveLoad
	{

		virtual ~ScoreDatabase() { }
	
		static void InitializeStatics();

	
		static boost::shared_ptr<ScoreDatabase> Instance;

	
		static int MostRecentScoreDate;
		static int CurrentDate();

		static int Capacity;

	
		static std::map<int, std::vector<boost::shared_ptr<ScoreEntry> > > Games;

	
		static void Initialize();

		#pragma region SaveLoad
	
		virtual void Serialize( const boost::shared_ptr<BinaryWriter> &writer );
		virtual void FailLoad();
		virtual void Deserialize( std::vector<unsigned char> Data );
		static void ProcessChunk( boost::shared_ptr<Chunk> chunk );
		#pragma endregion

	
		static void EnsureList( int Game );

		static boost::shared_ptr<ScoreList> GetList( int Game );

		/// <summary>
		/// Whether the given score qualifies for the high score list
		/// </summary>
		static bool Qualifies( int Game, int Score );

		/// <summary>
		/// Return the score with the smallest value.
		/// </summary>
	
		static boost::shared_ptr<ScoreEntry> Max( std::vector<boost::shared_ptr<ScoreEntry> > &Scores );

	
		static boost::shared_ptr<ScoreEntry> Max( int GameId );

		/// <summary>
		/// Return the score with the smallest value.
		/// </summary>
		static boost::shared_ptr<ScoreEntry> Min( std::vector<boost::shared_ptr<ScoreEntry> > &Scores );

		static boost::shared_ptr<ScoreEntry> Min( int GameId );

		static void Add( const boost::shared_ptr<ScoreEntry> &score );

		/// <summary>
		/// Remove excess entries, if the list is over capacity.
		/// </summary>
	
		static void TrimExcess( std::vector<boost::shared_ptr<ScoreEntry> > &Scores );

		static int ScoreCompare( const boost::shared_ptr<ScoreEntry> &score1, const boost::shared_ptr<ScoreEntry> &score2 );

		static bool ScoreCompareStrictWeak( const boost::shared_ptr<ScoreEntry> &score1, const boost::shared_ptr<ScoreEntry> &score2 );

		/// <summary>
		/// Sort the list by value.
		/// </summary>
		static void Sort( std::vector<boost::shared_ptr<ScoreEntry> > &Scores );
	};
}


#endif	//#ifndef SCOREDATABASE
