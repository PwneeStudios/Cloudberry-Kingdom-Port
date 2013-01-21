#ifndef LEADERBOARD
#define LEADERBOARD

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Leaderboard
	{

		static void WriteToLeaderboard(boost::shared_ptr<ScoreEntry> score);

	};

}


#endif	//#ifndef LEADERBOARD
