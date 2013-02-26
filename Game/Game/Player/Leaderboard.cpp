#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include "Leaderboard.h"

namespace CloudberryKingdom
{


    OnlineGamer Leaderboard::LeaderboardGamer;
    std::vector<OnlineGamer> Leaderboard::LeaderboardFriends;

	const int Leaderboard::EntriesPerPage = 20;

    ScoreEntry Leaderboard::ScoreToWrite;

	bool Leaderboard::WritingInProgress = false;





	void Leaderboard::WriteToLeaderboard( boost::shared_ptr<ScoreEntry> score )
	{
		if ( !CloudberryKingdomGame::OnlineFunctionalityAvailable() ) return;

        if ( WritingInProgress) return;

		// Modify the score entry's id
		boost::shared_ptr<ScoreEntry> copy = boost::make_shared<ScoreEntry>( score->GamerTag_Renamed, score->GameId, score->Value, score->Score, score->Level_Renamed, score->Attempts, score->Time, score->Date );
		copy->GameId += Challenge::LevelMask;
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
            case 10002: key = 29; break;
            case 10003: key = 30; break;
                
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
		Updated = true;
		TotalSize = 10000;
		StartIndex = 1;
    }

    void Leaderboard::SetType( LeaderboardType type)
    {
        MySortType = type;

		// FIXME: if in process of getting something, don't do anything
        //if (result != null) return;

        switch (MySortType)
        {
		case LeaderboardType_TopScores:
            //result = LeaderboardReader.BeginRead(Identity, 0, EntriesPerPage, OnInfo_TopScores, null);
            break;

        case LeaderboardType_MyScores:
            //result = LeaderboardReader.BeginRead(Identity, LeaderboardGamer, EntriesPerPage, OnInfo_MyScores, null);
            break;

        case LeaderboardType_FriendsScores:
            if ( FriendItems.size() == 0)
            {
                //result = LeaderboardReader.BeginRead(Identity, LeaderboardFriends, LeaderboardGamer, 100, OnInfo_FriendScores, null);
            }
            break;
        }
    }

    void Leaderboard::OnInfo_TopScores(/*IAsyncResult ar*/)
    {
        //Update(LeaderboardType.TopScores, ar);
    }

    void Leaderboard::OnInfo_MyScores(/*IAsyncResult ar*/)
    {
        //Update(LeaderboardType.MyScores, ar);
    }

    void Leaderboard::OnInfo_FriendScores(/*IAsyncResult ar*/)
    {
        //Update(LeaderboardType.FriendsScores, ar);
    }

    void Leaderboard::RequestMore( int RequestPage )
    {
		// Should return early if already trying to get info (if an async request is in progress)
        //if (MoreRequested || result != null) return;
		if ( MoreRequested ) return;

        this->MoreRequested = true;
        this->RequestPage = RequestPage;

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
        {
            int gamer_rank = -1;
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

        if ( Player.Id > 0 )
        {
            this->GamerTag = Localization::WordString( Localization::Words_Loading ) + L"...";
            this->Val = L"...";

			scale = 1;
        }
        else
        {
            this->GamerTag = Player.GamerTag();
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