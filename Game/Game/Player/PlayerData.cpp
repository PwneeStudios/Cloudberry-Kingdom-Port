#include <small_header.h>
#include "Game/Player/PlayerData.h"

#include "Core/Chunk.h"
#include "Core/Tools/Set.h"
#include "Game/Localization.h"
#include "Core/Text/EzText.h"
#include "Game/Games/Meta Games/Arcade Games/Escalate/Escalation.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Time Crisis/TimeCrisis.h"
#include "Game/Tools/EzStorage.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreDatabase.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreEntry.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
#include "Game/Player/ColorScheme.h"
#include "Game/Player/ColorSchemeManager.h"
#include "Game/Player/SavedSeeds.h"
#include "Game/Player/Stats.h"
#include "Game/Tools/Tools.h"
#include "Game/Tools/Unset.h"

#include "Game/Player/ClrTextFx.h"
#include "Game/Tools/WrappedFloat.h"

#include "Hacks/List.h"
#include <Core/Tools/Set.h>
#include <Core/Lambdas/Lambda.h>

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

#ifdef CAFE

	// From SaveWiiU.cpp.  Trying to get the account name.
	extern char *GLOBAL_ACCOUNT_NAME;

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
			Chunk::WriteSingle( writer, 2, guid->first );

		// Purchases
		for ( std::map<int, bool>::const_iterator guid = Purchases->dict.begin(); guid != Purchases->dict.end(); ++guid )
			Chunk::WriteSingle( writer, 3, guid->first );

		// Stats
		LifetimeStats->WriteChunk_4( writer );

		// Save seed
		MySavedSeeds->WriteChunk_5( writer );

		// Campaign (Chunks 100 and up)
		Chunk::WriteSingle( writer, 100, CampaignCoins );
		Chunk::WriteSingle( writer, 101, CampaignLevel );
		Chunk::WriteSingle( writer, 102, CampaignIndex );

        // Player Level
        Chunk::WriteSingle( writer, 23023, LastPlayerLevelUpload );

        // Sound settings
        Chunk::WriteSingle( writer, 84001, Tools::MusicVolume->getVal() );
        Chunk::WriteSingle( writer, 84002, Tools::SoundVolume->getVal() );
        Chunk::WriteSingle( writer, 84003, (int)Localization::CurrentLanguage->MyLanguage );

#if CAFE
#else
		ScoreDatabase::Instance->Serialize(writer);
		PlayerManager::SavePlayerData->Serialize(writer);
#endif
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
		// Clear everything before loading
		if ( MySavedSeeds != 0 ) MySavedSeeds->SeedStrings.clear();
		HighScores.clear();

		boost::shared_ptr<Chunks> chunks = Chunks::Get( Data );
		chunks->StartGettingChunks();
		while( chunks->HasChunk() )
		{
			boost::shared_ptr<Chunk> chunk = chunks->GetChunk();

			ProcessChunk(chunk);

#if CAFE
#else
			ScoreDatabase::ProcessChunk( chunk );
			_SavePlayerData::ProcessChunk( chunk );
#endif
		}

		/*
            // Cheat: Give all unlocks to player
            int l[] = { 7777, 9999, 10000, 10100, 11500, 10200, 10400, 10500, 11000, 10300, 11100, 10900, 11200, 11300, 11400, 10001, 10101, 11501, 10201, 10401, 10501, 11001, 10301, 11101, 10901, 11201, 11301, 11401, 10002, 10003 };
			for ( int i = 0; i < sizeof( l ) / sizeof( int ); ++i )
			{
				int id = l[ i ];

				AddHighScore( boost::make_shared<ScoreEntry>( std::wstring( L"" ), id, 150, 100000, 150, 100000, 100000, 100000 ) );
            }

            CampaignIndex = 326;
            CampaignLevel = 321;
            CampaignCoins = 10000;
            Awardments_Renamed->Add( 100 );
            Awardments_Renamed->Add( 101 );
            Awardments_Renamed->Add( 102 );
			*/
	}

#ifdef PS3
	// Set language on the main thread.
	struct SetLanguageLater : public Lambda
	{
		Localization::Language NewLanguage;

		SetLanguageLater( Localization::Language language )
			: NewLanguage( language )
		{
		}

		void Apply()
		{
			Localization::SetLanguage( NewLanguage );
		}
	};
#endif

	void PlayerData::ProcessChunk( boost::shared_ptr<Chunk> chunk )
	{
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

                // Player Level
            case 23023: LastPlayerLevelUpload = chunk->ReadInt(); break;

            // Sound settings
			case 84001: Tools::MusicVolume->setVal( chunk->ReadFloat() ); break;
			case 84002: Tools::SoundVolume->setVal( chunk->ReadFloat() ); break;
            case 84003:
                int _language = chunk->ReadInt();
                Localization::Language language = ( Localization::Language )_language;
#ifdef PS3
				Tools::AddToDo( boost::make_shared< SetLanguageLater >( language ) );
#else
                Localization::SetLanguage( language );
#endif
				break;
		}
	}

        int PlayerData::GetTotalLevel()
        {
            return GetTotalArcadeLevel() + GetTotalCampaignLevel() + 1;
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

			for ( std::vector<std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > >::const_iterator game = 
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
#if CAFE
		/*if( MyIndex == 0 )
		{
			return L"";//Utf8ToWstring( GLOBAL_ACCOUNT_NAME ? GLOBAL_ACCOUNT_NAME : "" );
		}*/
#endif

	#if defined(XBOX) || defined(XBOX_SIGNIN)
		if ( getMyGamer() != 0 )
			return getMyGamer()->Gamertag;
		else
	#endif
		if ( StoredName.length() > 0 )
			return StoredName;
		else
		{
			// Pick a random name if there is no stored name
			//if ( RandomNameIndex == -1 )
			//	RandomNameIndex = Tools::GlobalRnd->RndInt( 0, PlayerManager::RandomNames.size() - 1 );
			//return PlayerManager::RandomNames[ RandomNameIndex ];
			switch ( MyIndex )
			{
				case 0: return std::wstring( L"Player 1" );
				case 1: return std::wstring( L"Player 2" );
				case 2: return std::wstring( L"Player 3" );
				case 3: return std::wstring( L"Player 4" );
				default: return std::wstring( L"Players" );
			}
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
		LastPlayerLevelUpload = -1;
		CampaignLevel = 0;
		CampaignCoins = 0;
		StoredName = std::wstring( L"" );
		KeyboardUsedLast = false;
		ColorSchemeIndex = Unset::Int;
	}
}
