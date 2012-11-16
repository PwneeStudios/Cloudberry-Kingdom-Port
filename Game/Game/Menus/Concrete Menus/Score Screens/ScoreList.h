#ifndef SCORELIST
#define SCORELIST

#include "ScoreEntry.h"
#include "../Game/Localization.h"
#include <string>
#include <vector>
#include <tchar.h>
#include "stringconverter.h"

namespace CloudberryKingdom
{
	class ScoreEntry;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	class ScoreList
	{
	public:
		int Capacity;

		ScoreEntry::Format MyFormat;

		Localization::Words GetHeader();

		std::wstring GetPrefix();

		std::vector<ScoreEntry*> Scores;

		ScoreList();
		ScoreList( int DefaultValue );
		ScoreList( int Capacity, int DefaultValue );

		int DefaultValue;
	private:
		void Init( int Capacity, int DefaultValue );

		/// <summary>
		/// Whether the given score qualifies for the high score list
		/// </summary>
	public:
		bool Qualifies( const std::shared_ptr<ScoreEntry> &Entry );

		/// <summary>
		/// Get the value of the bottom score
		/// </summary>
		const int &getBottom() const;

		std::wstring ScoreString( const std::shared_ptr<ScoreEntry> &score, int Length );

		void Add( const std::shared_ptr<ScoreEntry> &score );

		/// <summary>
		/// Remove excess entries, if the list is over capacity.
		/// </summary>
	private:
		void TrimExcess();

		static int ScoreCompare( const std::shared_ptr<ScoreEntry> &score1, const std::shared_ptr<ScoreEntry> &score2 );

		/// <summary>
		/// Sort the list by value.
		/// </summary>
		void Sort();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SCORELIST
