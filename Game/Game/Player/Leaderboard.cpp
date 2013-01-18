#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	void Leaderboard::WriteToLeaderboard(boost::shared_ptr<ScoreEntry> score)
	{
		if (CloudberryKingdomGame::getIsDemo()) return;
	}

}