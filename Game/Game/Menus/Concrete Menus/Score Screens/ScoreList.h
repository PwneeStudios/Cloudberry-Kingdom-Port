#ifndef SCORELIST
#define SCORELIST

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ScoreList
	{
	
		int Capacity;

		ScoreEntry::Format MyFormat;

		Localization::Words GetHeader();

		std::wstring GetPrefix();

		std::vector<std::shared_ptr<ScoreEntry> > Scores;

		ScoreList();
		ScoreList( int DefaultValue );
		ScoreList( int Capacity, int DefaultValue );

		int DefaultValue;
	
		void Init( int Capacity, int DefaultValue );

		/// <summary>
		/// Whether the given score qualifies for the high score list
		/// </summary>
	
		bool Qualifies( const std::shared_ptr<ScoreEntry> &Entry );

		/// <summary>
		/// Get the value of the bottom score
		/// </summary>
		const int getBottom() const;

		std::wstring ScoreString( const std::shared_ptr<ScoreEntry> &score, int Length );

		void Add( const std::shared_ptr<ScoreEntry> &score );

		/// <summary>
		/// Remove excess entries, if the list is over capacity.
		/// </summary>
	
		void TrimExcess();

		static int ScoreCompare( const std::shared_ptr<ScoreEntry> &score1, const std::shared_ptr<ScoreEntry> &score2 );

		/// <summary>
		/// Sort the list by value.
		/// </summary>
		void Sort();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SCORELIST
