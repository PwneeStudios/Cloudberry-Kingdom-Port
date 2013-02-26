#ifndef LEADERBOARD
#define LEADERBOARD

#include <global_header.h>
//#include <Game/Player/LeaderboardView.h>

namespace CloudberryKingdom
{

	typedef int OnlineGamer;

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

        LeaderboardItem( boost::shared_ptr<Gamer> Player, int Val, int Rank );

		void Draw( Vector2 Pos, bool Selected, float alpha );

    };

	struct Leaderboard
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



		static void WriteToLeaderboard(boost::shared_ptr<ScoreEntry> score);

		int GetLeaderboardId(int game_id);

		Leaderboard(int game_id);

		void SetType(LeaderboardType type);
		void OnInfo_TopScores(/*IAsyncResult ar*/);
		void OnInfo_MyScores(/*IAsyncResult ar*/);
		void OnInfo_FriendScores(/*IAsyncResult ar*/);
		void RequestMore(int RequestPage);
		void Update(LeaderboardType Type /*, IAsyncResult ar*/);


		static void Initialize();
		static void Shutdown();
	};

}


#endif	//#ifndef LEADERBOARD
