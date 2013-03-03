#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include "Leaderboard.h"
#include <Utility/Log.h>

#ifdef PS3
#include <np.h>
#include <sys/ppu_thread.h>
#include <Utility/NetworkPS3.h>
#endif

namespace CloudberryKingdom
{


    OnlineGamer Leaderboard::LeaderboardGamer;
    std::vector<OnlineGamer> Leaderboard::LeaderboardFriends;

	const int Leaderboard::EntriesPerPage = 20;

    ScoreEntry Leaderboard::ScoreToWrite;

	bool Leaderboard::WritingInProgress = false;

#ifdef PS3
	inline INT64 PackBoardAndScore( int board, int score )
	{
		return ( static_cast< INT64 >( board ) << 32 ) | score;
	}

	inline void UnpackBoardAndScore( INT64 packed, int &board, int &score )
	{
		score = packed & 0xffffffff;
		board = packed >> 32; 
	}

	static void WriteToLeaderboardThread( INT64 context )
	{
		int contextId;
		if( !GetNPScoreContext( contextId ) )
		{
			Leaderboard::WritingInProgress = false;
			sys_ppu_thread_exit( 0 );
			return;
		}

		int ret = sceNpScoreCreateTransactionCtx( contextId );
		if( ret < 0 )
		{
			LOG.Write( "Failed to create score transaction: 0x%x\n", ret );
			Leaderboard::WritingInProgress = false;
			sys_ppu_thread_exit( 0 );
			return;
		}
		int transactionId = ret;

		SceNpScoreRankNumber rank;
		
		int board;
		int score;
		UnpackBoardAndScore( context, board, score );
		ret = sceNpScoreRecordScore( transactionId, board, score, NULL, NULL, &rank, NULL );
		if( ret < 0 )
			LOG.Write( "Failed to record score: 0x%x\n", ret );

		sceNpScoreDestroyTransactionCtx( transactionId );

		Leaderboard::WritingInProgress = false;

		sys_ppu_thread_exit( 0 );
	}
#endif

	void Leaderboard::WriteToLeaderboard( boost::shared_ptr<ScoreEntry> score )
	{
		if ( !CloudberryKingdomGame::OnlineFunctionalityAvailable() ) return;

        if ( WritingInProgress ) return;

		// Modify the score entry's id
		boost::shared_ptr<ScoreEntry> copy = boost::make_shared<ScoreEntry>( score->GamerTag_Renamed, score->GameId, score->Value, score->Score, score->Level_Renamed, score->Attempts, score->Time, score->Date );
		copy->GameId += Challenge::LevelMask;

#if PS3
		int contextId;
		if( !GetNPScoreContext( contextId ) )
			return;

		WritingInProgress = true;

		sys_ppu_thread_t tid;
		int ret = sys_ppu_thread_create( &tid, WriteToLeaderboardThread,
			PackBoardAndScore( GetLeaderboardId( copy->GameId ), copy->Value ),
			1001, 16 * 1024, 0, "WriteToLeaderboardThread" );
		if( ret != 0 )
			LOG.Write( "Failed to start WriteToLeaderboardThread: 0x%x\n", ret );
#endif
	}

    int Leaderboard::GetLeaderboardId(int game_id)
    {
        int key;
        switch ( game_id )
        {
            case 7777: key = 0; break;
            case 9999: key = 1; break;
            case 10000: key = 2; break;
            case 10100: key = 3; break;
            case 11500: key = 4; break;
            case 10200: key = 5; break;
            case 10400: key = 6; break;
            case 10500: key = 7; break;
            case 11000: key = 8; break;
            case 10300: key = 9; break;
            case 11100: key = 10; break;
            case 10900: key = 11; break;
            case 11200: key = 12; break;
            case 11300: key = 13; break;
            case 11400: key = 14; break;
            case 10001: key = 15; break;
            case 10101: key = 16; break;
            case 11501: key = 17; break;
            case 10201: key = 18; break;
            case 10401: key = 19; break;
            case 10501: key = 20; break;
            case 11001: key = 21; break;
            case 10301: key = 22; break;
            case 11101: key = 23; break;
            case 10901: key = 24; break;
            case 11201: key = 25; break;
            case 11301: key = 26; break;
            case 11401: key = 27; break;
            case 10002: key = 28; break;
            case 10003: key = 29; break;
                
			default: key = 1; break;
        }

		return key;
    }

    Leaderboard::Leaderboard(int game_id)
    {
		WritingInProgress = false;
		MySortType = static_cast< LeaderboardType >( 0 );
        RequestPage = 0;

        Items.clear();
        FriendItems.clear();

        MyId = GetLeaderboardId(game_id);

		MoreRequested = false;
		Updated = false;
		TotalSize = 10000;
		StartIndex = 1;
    }

    void Leaderboard::SetType( LeaderboardType type)
    {
        MySortType = type;

		if( MoreRequested )
			return;

		// FIXME: if in process of getting something, don't do anything
        //if (result != null) return;

        switch (MySortType)
        {
		case LeaderboardType_TopScores:
            //result = LeaderboardReader.BeginRead(Identity, 0, EntriesPerPage, OnInfo_TopScores, null);
			RequestMore( 1 );
            break;

        case LeaderboardType_MyScores:
            //result = LeaderboardReader.BeginRead(Identity, LeaderboardGamer, EntriesPerPage, OnInfo_MyScores, null);
			RequestMore( 1 );
            break;

        case LeaderboardType_FriendsScores:
            if ( FriendItems.size() == 0)
            {
				RequestMore( 1 );
                //result = LeaderboardReader.BeginRead(Identity, LeaderboardFriends, LeaderboardGamer, 100, OnInfo_FriendScores, null);
            }
            break;
        }
    }

    void Leaderboard::OnInfo_TopScores(/*IAsyncResult ar*/)
    {
        Update( LeaderboardType_TopScores );
    }

    void Leaderboard::OnInfo_MyScores(/*IAsyncResult ar*/)
    {
        Update( LeaderboardType_MyScores );
    }

    void Leaderboard::OnInfo_FriendScores(/*IAsyncResult ar*/)
    {
        Update( LeaderboardType_FriendsScores );
    }

	void Leaderboard::OnInfo_Fail()
	{
		MoreRequested = false;
		TotalSize = 0;
		Updated = true;
	}

#ifdef PS3
	// Parameters passed to the thread.
	static boost::shared_ptr< Leaderboard > CurrentLeaderboard;
	static int StartingRank;
	static LeaderboardType CurrentLeaderboardType;
	// We could potentially get up to 100 scores when requesting friend scores.
	// Add one more to get your own score as well.
	static SceNpScoreRankData Ranks[ 101/*Leaderboard::EntriesPerPage*/ ];
	static int NumRanks;
	static int MaxRanks;

	// Sony says there is a maximum of 100 friends.
	static SceNpId FriendIds[ 100 ];
	static SceNpScorePlayerRankData FriendRanks[ 100 ];

	// Get our own NP id.  Implemented in CorePS3.cpp
	extern void GetMyNpId( SceNpId &id );

	inline bool RankComparer( const SceNpScoreRankData &a, const SceNpScoreRankData &b )
	{
		return a.rank < b.rank;
	}

	static void RequestLeaderboardThread( INT64 context )
	{
		int contextId;
		if( !GetNPScoreContext( contextId ) )
		{
			CurrentLeaderboard->OnInfo_Fail();
			CurrentLeaderboard = NULL;
			sys_ppu_thread_exit( 0 );
			return;
		}

		int ret = sceNpScoreCreateTransactionCtx( contextId );
		if( ret < 0 )
		{
			LOG.Write( "Failed to create score transaction: 0x%x\n", ret );
			CurrentLeaderboard->OnInfo_Fail();
			CurrentLeaderboard = NULL;
			sys_ppu_thread_exit( 0 );
			return;
		}
		int transactionId = ret;

		CellRtcTick lastSortDate;
		SceNpScoreRankNumber totalRecord;

		// If this is a friend request, get all the friends.
		if( CurrentLeaderboardType == LeaderboardType_FriendsScores )
		{
			uint32_t friendCount = 0;
			ret = sceNpBasicGetFriendListEntryCount( &friendCount );
			if( ret < 0 )
				LOG.Write( "Couldn't get friend list count: 0x%x\n", ret );

			// Just in case limits change later.
			if( friendCount > 100 )
				friendCount = 100;

			for( uint32_t i = 0; i < friendCount; ++i )
			{
				ret = sceNpBasicGetFriendListEntry( i, &FriendIds[ i ] );
				if( ret < 0 )
					LOG.Write( "Couldn't get friend %d: 0x%x\n", i, ret );
			}

			// Add us to the list.
			ret = sceNpManagerGetNpId( &FriendIds[ friendCount ] );
			if( ret == 0 )
				++friendCount;
			else
				LOG.Write( "Failed to get our own NpId: 0x%x\n", ret );

			if( friendCount > 0 )
			{
				ret = sceNpScoreGetRankingByNpId( transactionId, CurrentLeaderboard->MyId,
					FriendIds, friendCount * sizeof( SceNpId ), FriendRanks, friendCount * sizeof( SceNpScorePlayerRankData ),
					NULL, 0, NULL, 0, friendCount, &lastSortDate, &totalRecord, NULL );
				MaxRanks = totalRecord;

				if( ret >= 0 )
				{
					int j = 0;

					for( int i = 0; i < friendCount; ++i )
					{
						if( FriendRanks[ i ].hasData )
							Ranks[ j++ ] = FriendRanks[ i ].rankData;
					}

					NumRanks = j;

					// Sort the ranks.
					std::sort( Ranks, Ranks + NumRanks, RankComparer );
				}
			}
		}
		else
		{
			ret = sceNpScoreGetRankingByRange( transactionId,
				CurrentLeaderboard->MyId, StartingRank, Ranks,
				Leaderboard::EntriesPerPage * sizeof( SceNpScoreRankData ), NULL, 0, NULL, 0, Leaderboard::EntriesPerPage,
				&lastSortDate, &totalRecord, NULL );
			MaxRanks = totalRecord;
			NumRanks = ret;
		}

		if( ret == SCE_NP_COMMUNITY_SERVER_ERROR_GAME_RANKING_NOT_FOUND )
		{
			NumRanks = 0;
			LOG.Write( "No more scores!\n" );
			CurrentLeaderboard->OnInfo_Fail();
		}
		else
		{
			if( ret < 0 )
			{
				LOG.Write( "Failed to request scores: 0x%x\n", ret );
				NumRanks = 0;
				CurrentLeaderboard->OnInfo_Fail();
			}
			else
			{
				// Update current leaderboard.
				switch( CurrentLeaderboardType )
				{
				case LeaderboardType_FriendsScores:
					CurrentLeaderboard->OnInfo_FriendScores();
					break;
				case LeaderboardType_TopScores:
					CurrentLeaderboard->OnInfo_TopScores();
					break;
				case LeaderboardType_MyScores:
					CurrentLeaderboard->OnInfo_MyScores();
					break;
				}
			}
		}

		sceNpScoreDestroyTransactionCtx( transactionId );
		CurrentLeaderboard = NULL;

		sys_ppu_thread_exit( 0 );
	}
#endif

    void Leaderboard::RequestMore( int RequestPage )
    {
#if PS3
		// Should return early if already trying to get info (if an async request is in progress)
		if ( MoreRequested || CurrentLeaderboard != NULL ) return;

        this->MoreRequested = true;
        this->RequestPage = RequestPage;

		int contextId;
		if( !GetNPScoreContext( contextId ) )
		{
			this->MoreRequested = false;
			return;
		}

		CurrentLeaderboard = shared_from_this();
		StartingRank = RequestPage;
		CurrentLeaderboardType = MySortType;

		sys_ppu_thread_t tid;
		int ret = sys_ppu_thread_create( &tid, RequestLeaderboardThread,
			0, 1001, 16 * 1024, 0, "RequestLeaderboardThread" );
		if( ret != 0 )
			LOG.Write( "Failed to start RequestLeaderboardThread: 0x%x\n", ret );
#endif

		//result = LeaderboardReader.BeginRead(Identity, RequestPage, EntriesPerPage, OnInfo_TopScores, null);
    }

    void Leaderboard::Update( LeaderboardType Type /*, IAsyncResult ar*/ )
    {
		// If no async request was in progress, return early
		//if (reader == null) { result = null; return; }

        // Get the total size of the leaderboard
		//TotalSize = reader.TotalLeaderboardSize;


		// FIXME put a lock on the dictionary of items
        //lock (Items)
		ItemMutex.Lock();
        {
            int gamer_rank = -1;
#ifdef PS3
			TotalSize = MaxRanks;
			/*if( NumRanks == 0 )
				TotalSize = Items.size();*/

			for( int i = 0; i < NumRanks; ++i )
			{
				int rank = Ranks[ i ].rank;
				int value = Ranks[ i ].scoreValue;
				std::wstring name = Utf8ToWstring( Ranks[ i ].onlineName.data );

				OnlineGamer gamer;
				gamer.Id = rank;
				gamer.GamerTag = name;

				LeaderboardItem item( gamer, value, rank );

				if( Type == LeaderboardType_FriendsScores )
				{
					if( rank > 0 && value > 0 )
						FriendItems.push_back( item );
				}
				else
					Items[ rank ] = item;
			}
#endif
            // Loop over all items returned by the async call and add them to the dictionary
			//foreach (LeaderboardEntry entry in reader.Entries)
            //{
            //    int rank = entry.GetRank();
            //    int val = (int)entry.Rating;
            //    Gamer gamer = entry.Gamer;
            //    var item = new LeaderboardItem(gamer, val, rank);

            //    if (Type == LeaderboardType.FriendsScores)
            //    {
            //        if (rank > 0 && val > 0)
            //            FriendItems.Add(item);
            //    }
            //    else
            //    {
            //        Items.AddOrOverwrite(rank, item);
            //    }

            //    if (gamer_rank == -1 || gamer.Gamertag == LeaderboardGamer.Gamertag)
            //        gamer_rank = rank;
            //}

            MoreRequested = false;

            Updated = true;

			// This should signify that an async call is no longer in process
            //result = null;

            switch (Type)
            {
				case LeaderboardType_TopScores:
                    StartIndex = 1;
                    break;
				case LeaderboardType_MyScores:
                    StartIndex = gamer_rank;
                    break;
				case LeaderboardType_FriendsScores: 
                    StartIndex = 1;
                    TotalSize = FriendItems.size();
                    break;
                
				default: break;
            }
        }
		ItemMutex.Unlock();
    }

	void LeaderboardItem::StaticIntialize()
	{
		DefaultItem = boost::make_shared<LeaderboardItem>( OnlineGamer(), 0, 0 );
	}

    boost::shared_ptr<LeaderboardItem> LeaderboardItem::DefaultItem;

    LeaderboardItem::LeaderboardItem()
	{
	}

    LeaderboardItem::LeaderboardItem( OnlineGamer Player, int Val, int Rank )
    {
        this->Player = Player;
        this->Rank = ToString( Rank );

        if ( Player.Id < 0 )
        {
            this->GamerTag = Localization::WordString( Localization::Words_Loading ) + L"...";
            this->Val = L"...";

			scale = 1;
        }
        else
        {
            this->GamerTag = Player.GamerTag;
            this->Val = ToString( Val );

            float width = Tools::QDrawer->MeasureString( Resources::Font_Grobold42->HFont, GamerTag ).X;
            if ( width > 850.0f )
                scale = 850.0f / width;
            else
                scale = 1;
        }
    }

    void LeaderboardItem::Draw( Vector2 Pos, bool Selected, float alpha, float Offset_GamerTag, float Offset_Val, float ItemShift )
    {
        Vector4 color = ColorHelper::Gray(.9f );
        Vector4 ocolor = Color::Black.ToVector4();

        if ( Selected )
        {
            //ocolor = Color( 191, 191, 191 ).ToVector4();
            //color = Color( 175, 8, 64 ).ToVector4();

            color = Color::LimeGreen.ToVector4();
            ocolor = bColor( 0, 0, 0 ).ToVector4();
        }
            
        color *= alpha;

        Vector2 GamerTag_Offset = .1f * Vector2( Offset_GamerTag, -( 1.0f - scale ) * 1000.0f );
        Vector2 Val_Offset = .1f * Vector2( Offset_Val, 0 );
        Vector2 Size = .1f * Vector2( ItemShift );

        if ( Selected )
        {
            Tools::QDrawer->DrawString( Resources::Font_Grobold42->HOutlineFont, Rank, Pos, ocolor, Size );
            Tools::QDrawer->DrawString( Resources::Font_Grobold42->HOutlineFont, GamerTag, Pos + GamerTag_Offset, ocolor, scale * Size );
            Tools::QDrawer->DrawString( Resources::Font_Grobold42->HOutlineFont, Val, Pos + Val_Offset, ocolor, Size );
        }

        Tools::QDrawer->DrawString( Resources::Font_Grobold42->HFont, Rank, Pos, color, Size );
        Tools::QDrawer->DrawString( Resources::Font_Grobold42->HFont, GamerTag, Pos + GamerTag_Offset, color, scale * Size );
        Tools::QDrawer->DrawString( Resources::Font_Grobold42->HFont, Val, Pos + Val_Offset, color, Size );
    }
}