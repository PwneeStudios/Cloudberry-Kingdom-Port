#include <global_header.h>

#include "Hacks/List.h"
#include <Core\Tools\Set.h>

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

namespace CloudberryKingdom
{

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))
	const boost::shared_ptr<Gamer> &PlayerData::getMyGamer() const
	{
		return CheckForMatchingGamer();
	}
#endif

	PlayerData::PlayerData() :
		MyPlayerIndex( PlayerIndex_One ),
		Exists( false ),
		IsAlive( false ),
		CampaignLevel( 0 ),
		CampaignCoins( 0 ),
		CampaignIndex( 0 ),
		MyIndex( 0 ),
		RandomNameIndex( 0 ),
		KeyboardUsedLast( 0 ),
		ColorSchemeIndex( 0 )
	{
		InitializeInstanceFields();
		AlwaysSave = true;
		FailLoad();
	}

	void PlayerData::Serialize( const boost::shared_ptr<BinaryWriter> &writer )
	{
		// Color scheme
		CustomColorScheme.WriteChunk_0( writer );
		Chunk::WriteSingle( writer, 1, ColorSchemeIndex );

		// High Scores
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::map<int, boost::shared_ptr<ScoreEntry> >::const_iterator HighScore = HighScores.begin(); HighScore != HighScores.end(); ++HighScore )
			HighScore->second->WriteChunk_1000( writer );

		// Awardments
		for ( std::map<int, bool>::const_iterator guid = Awardments_Renamed->dict.begin(); guid != Awardments_Renamed->dict.end(); ++guid )
			Chunk::WriteSingle( writer, 2, ColorSchemeIndex );

		// Purchases
		for ( std::map<int, bool>::const_iterator guid = Purchases->dict.begin(); guid != Purchases->dict.end(); ++guid )
			Chunk::WriteSingle( writer, 3, ColorSchemeIndex );

		// Stats
		LifetimeStats->WriteChunk_4( writer );

		// Save seed
		MySavedSeeds->WriteChunk_5( writer );

		// Campaign (Chunks 100 and up)
		Chunk::WriteSingle( writer, 100, CampaignCoins );
		Chunk::WriteSingle( writer, 101, CampaignLevel );
		Chunk::WriteSingle( writer, 102, CampaignIndex );
	}

	void PlayerData::FailLoad()
	{
		MySavedSeeds = boost::make_shared<SavedSeeds>();
		HighScores = std::map<int, boost::shared_ptr<ScoreEntry> >();
		Purchases = boost::make_shared<Set<int> >();
		Awardments_Renamed = boost::make_shared<Set<int> >();
	}

	void PlayerData::Deserialize( std::vector<unsigned char> Data )
	{
		boost::shared_ptr<Chunks> chunks = Chunks::Get( Data );
		chunks->StartGettingChunks();
		while( chunks->HasChunk() )
		{
			boost::shared_ptr<Chunk> chunk = chunks->GetChunk();

			switch ( chunk->Type )
			{
				// Color scheme
				case 0:
					CustomColorScheme.ReadChunk_0( chunk );
					ColorScheme_Renamed = CustomColorScheme;
					break;

				case 1:
					chunk->ReadSingle( ColorSchemeIndex );

					if ( ColorSchemeIndex == Unset::Int )
						ColorSchemeIndex = 0;
					if ( ColorSchemeIndex >= 0 )
						ColorScheme_Renamed = ColorSchemeManager::ColorSchemes[ ColorSchemeIndex ];

					break;

				// High Scores
				case 1000:
					{
						boost::shared_ptr<ScoreEntry> score = boost::make_shared<ScoreEntry>();
						score->ReadChunk_1000( chunk );
						AddHighScore( score );
					}
					break;

				// Awardments
				case 2:
					Awardments_Renamed->Add( chunk->ReadInt() );
					break;

				// Purchases
				case 3:
					Purchases->Add( chunk->ReadInt() );
					break;

				// Stats
				case 4:
					LifetimeStats->ReadChunk_4( chunk );
					break;

				// Saved Seeds
				case 5:
					MySavedSeeds->ReadChunk_5( chunk );
					break;

				// Campaign (Chunks 100 and up)
				case 100:
					CampaignCoins = chunk->ReadInt();
					break;
				case 101:
					CampaignLevel = chunk->ReadInt();
					break;
				case 102:
					CampaignIndex = chunk->ReadInt();
					break;
			}
		}
	}

        int PlayerData::GetTotalLevel()
        {
            return GetTotalArcadeLevel() + GetTotalCampaignLevel();
        }

        int PlayerData::GetTotalCampaignLevel()
        {
            return CampaignLevel;
        }

        int PlayerData::GetTotalCampaignIndex()
        {
            return CampaignIndex;
        }

        int PlayerData::GetTotalArcadeLevel()
        {
            int level = 0;
            int id;

			for ( std::map<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >::const_iterator game = 
				ArcadeMenu::HeroArcadeList.begin(); game != ArcadeMenu::HeroArcadeList.end(); ++game )
            {
                id = Challenge_Escalation::getInstance()->CalcGameId_Level(game->first);
                if ( Contains( HighScores, id ) )
                    level += HighScores[id]->Value;

                id = Challenge_TimeCrisis::getInstance()->CalcGameId_Level(game->first);
                if ( Contains( HighScores, id ) )
                    level += HighScores[id]->Value;

                id = Challenge_HeroRush::getInstance()->CalcGameId_Level(game->first);
                if ( Contains( HighScores, id ) )
                    level += HighScores[id]->Value;

                id = Challenge_HeroRush2::getInstance()->CalcGameId_Level(game->first);
                if ( Contains( HighScores, id ) )
                    level += HighScores[id]->Value;
            }

            return level;
        }

	int PlayerData::GetHighScore( int GameId )
	{
		if ( HighScores.find( GameId ) != HighScores.end() )
			return HighScores[ GameId ]->Value;
		else
			return 0;
	}

	void PlayerData::AddHighScore( const boost::shared_ptr<ScoreEntry> &score )
	{
		if ( HighScores.find( score->GameId ) != HighScores.end() && score->Value < HighScores[ score->GameId ]->Value )
			return;

		// FIXME: This was AddOrOverwrite.
		//HighScores.AddOrOverwrite( score->GameId, score );
		HighScores[ score->GameId ] = score;

		// Mark this object as changed, so that it will be saved to disk.
		Changed = true;
	}

	const boost::shared_ptr<PlayerStats> &PlayerData::getStats() const
	{
		return LevelStats;
	}

	boost::shared_ptr<PlayerStats> PlayerData::GetStats( StatGroup group )
	{
		switch ( group )
		{
			case StatGroup_TEMP:
				return TempStats;
			case StatGroup_LEVEL:
				return LevelStats;
			case StatGroup_GAME:
				return GameStats;
			case StatGroup_LIFETIME:
				return LifetimeStats;
			case StatGroup_CAMPAIGN:
				return CampaignStats;
			default:
				return 0;
		}
	}

	boost::shared_ptr<PlayerStats> PlayerData::GetSummedStats( StatGroup group )
	{
		if ( group == StatGroup_LIFETIME )
		{
			static StatGroup groups[] = { StatGroup_TEMP, StatGroup_LEVEL, StatGroup_GAME, StatGroup_LIFETIME };
			static std::vector<StatGroup> vecGroups( VecFromArray( groups ) );
			return SumStats( vecGroups );
		}
		if ( group == StatGroup_CAMPAIGN )
		{
			static StatGroup groups[] = { StatGroup_TEMP, StatGroup_LEVEL, StatGroup_GAME, StatGroup_CAMPAIGN };
			static std::vector<StatGroup> vecGroups( VecFromArray( groups ) );
			return SumStats( vecGroups );
		}
		if ( group == StatGroup_GAME )
		{
			static StatGroup groups[] = { StatGroup_TEMP, StatGroup_LEVEL, StatGroup_GAME };
			static std::vector<StatGroup> vecGroups( VecFromArray( groups ) );
			return SumStats( vecGroups );
		}
		if ( group == StatGroup_LEVEL )
		{
			static StatGroup groups[] = { StatGroup_TEMP, StatGroup_LEVEL };
			static std::vector<StatGroup> vecGroups( VecFromArray( groups ) );
			return SumStats( vecGroups );
		}
		if ( group == StatGroup_TEMP )
		{
			static StatGroup groups[] = { StatGroup_TEMP };
			static std::vector<StatGroup> vecGroups( VecFromArray( groups ) );
			return SumStats( vecGroups );
		}

		return 0;
	}

	boost::shared_ptr<PlayerStats> PlayerData::SumStats( const std::vector<StatGroup> &group )
	{
		boost::shared_ptr<PlayerStats> StatSum = boost::make_shared<PlayerStats>();

		StatSum->Clean();
		for ( std::vector<StatGroup>::const_iterator g = group.begin(); g != group.end(); ++g )
			StatSum->Absorb( GetStats( *g ) );

		return StatSum;
	}

	int PlayerData::GetGameScore()
	{
		return GameStats->Score + LevelStats->Score;
	}

	int PlayerData::GetLevelCoins()
	{
		return LevelStats->Coins + TempStats->Coins;
	}

	int PlayerData::RunningCampaignScore()
	{
		return CampaignStats->Score + GameStats->Score + LevelStats->Score + TempStats->Score;
	}

	int PlayerData::Bank()
	{
		return LifetimeStats->Coins - LifetimeStats->CoinsSpentAtShop;
	}

#if defined(XBOX) || defined(XBOX_SIGNIN)
	boost::shared_ptr<Gamer> PlayerData::CheckForMatchingGamer()
	{
		_MyGamer.reset();
		//return _MyGamer;

		for ( Microsoft::Xna::Framework::GamerServices::SignedInGamerCollection::const_iterator gamer = Gamer::SignedInGamers.begin(); gamer != Gamer::SignedInGamers.end(); ++gamer )
			if ( static_cast<int>( ( *gamer )->PlayerIndex ) == MyIndex )
				_MyGamer = *gamer;

		if ( _MyGamer != 0 )
			StoredName = _MyGamer->Gamertag;

		return _MyGamer;
	}
#endif

	Vector4 PlayerData::GetTextColor()
	{
		Vector4 clr = ColorScheme_Renamed.SkinColor->DetailColor.ToVector4();
		if ( clr.W == 0 )
			clr = Vector4( 1, 1, 1, 1 );
		return clr;
	}

	void PlayerData::SetNameText( const boost::shared_ptr<EzText> &text )
	{
		//text.ShadowOffset = new Vector2(9, 9);
		//text.ShadowColor = Generic.PlayerColorSchemes[PlayerIndex].OutlineColor.Clr;
		text->MyFloatColor = GetTextColor();
		//text.OutlineColor = Generic.PlayerColorSchemes[PlayerIndex].OutlineColor.Clr.ToVector4();
	}

	std::wstring PlayerData::GetName()
	{
	#if defined(XBOX) || defined(XBOX_SIGNIN)
		if ( getMyGamer() != 0 )
			return getMyGamer()->Gamertag;
		else
	#endif
		if ( StoredName.length() > 0 )
			return StoredName;
		else
		{
			if ( RandomNameIndex == -1 )
				RandomNameIndex = Tools::GlobalRnd->RndInt( 0, PlayerManager::RandomNames.size() - 1 );
			return PlayerManager::RandomNames[ RandomNameIndex ];
		}
	}

	void PlayerData::Init( int Index )
	{
		Init();

		MyIndex = Index;
		MyPlayerIndex = static_cast<PlayerIndex>( MyIndex );
		ColorScheme_Renamed = ColorSchemeManager::ColorSchemes[ Index ];
	}

	void PlayerData::Init()
	{
		RandomNameIndex = -1;

		TempStats = boost::make_shared<PlayerStats>();
		LevelStats = boost::make_shared<PlayerStats>();
		GameStats = boost::make_shared<PlayerStats>();
		LifetimeStats = boost::make_shared<PlayerStats>();

		CampaignStats = boost::make_shared<PlayerStats>();
	}

	void PlayerData::InitializeInstanceFields()
	{
		CampaignLevel = 0;
		CampaignCoins = 0;
		StoredName = std::wstring( L"" );
		KeyboardUsedLast = false;
		ColorSchemeIndex = Unset::Int;
	}
}
