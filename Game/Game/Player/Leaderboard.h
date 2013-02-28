#ifndef LEADERBOARD
#define LEADERBOARD

#include <global_header.h>
//#include <Game/Player/LeaderboardView.h>

#include <Utility/Mutex.h>

namespace CloudberryKingdom
{

	struct OnlineGamer
	{
		int Id;
		std::wstring GamerTag;

		OnlineGamer()
		{
			Id = -232323;
		}
	};

    enum LeaderboardType { LeaderboardType_FriendsScores, LeaderboardType_TopScores, LeaderboardType_MyScores, LeaderboardType_Length };
    enum LeaderboardSortType { LeaderboardSortType_Score, LeaderboardSortType_Level, LeaderboardSortType_Length };
    enum Message { Message_None, Message_Loading, Message_NoOne, Message_NotRanked, Message_NotRankedFriends, Message_Length };

	struct LeaderboardItem
    {

        OnlineGamer Player;
        std::wstring GamerTag;
        std::wstring Val;
        std::wstring Rank;
		float scale;

		static void StaticIntialize();
        static boost::shared_ptr<LeaderboardItem> DefaultItem;

		LeaderboardItem();
        LeaderboardItem( OnlineGamer Gamer, int Val, int Rank );

		void Draw( Vector2 Pos, bool Selected, float alpha, float Offset_GamerTag, float Offset_Val, float ItemShift );
    };

	struct Leaderboard : boost::enable_shared_from_this<Leaderboard>
	{

        static OnlineGamer LeaderboardGamer;
        static std::vector<OnlineGamer> LeaderboardFriends;

		const static int EntriesPerPage;

        static ScoreEntry ScoreToWrite;

		static bool WritingInProgress;

		int MyId;

		LeaderboardType MySortType;

        bool MoreRequested;
        int RequestPage;

        bool Updated;
        int StartIndex;
        int TotalSize;

        std::map<int, LeaderboardItem> Items;
        std::vector<LeaderboardItem> FriendItems;

		Mutex ItemMutex;



		static void WriteToLeaderboard(boost::shared_ptr<ScoreEntry> score);

		static int GetLeaderboardId(int game_id);

		Leaderboard(int game_id);

		void SetType(LeaderboardType type);
		void OnInfo_TopScores(/*IAsyncResult ar*/);
		void OnInfo_MyScores(/*IAsyncResult ar*/);
		void OnInfo_FriendScores(/*IAsyncResult ar*/);
		void OnInfo_Fail();
		void RequestMore(int RequestPage);
		void Update(LeaderboardType Type /*, IAsyncResult ar*/);

	};

}


#endif	//#ifndef LEADERBOARD
