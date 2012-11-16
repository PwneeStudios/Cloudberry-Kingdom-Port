#include <global_header.h>








#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

namespace CloudberryKingdom
{

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))
	const std::shared_ptr<Gamer> &PlayerData::getMyGamer() const
	{
		return CheckForMatchingGamer();
	}
#endif

	PlayerData::PlayerData()
	{
		InitializeInstanceFields();
		AlwaysSave = true;
		FailLoad();
	}

	void PlayerData::Serialize( const std::shared_ptr<BinaryWriter> &writer )
	{
		// Color scheme
		CustomColorScheme.WriteChunk_0( writer );
		Chunk::WriteSingle( writer, 1, ColorSchemeIndex );

		// High Scores
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::unordered_map<int, ScoreEntry*>::const_iterator HighScore = HighScores.begin(); HighScore != HighScores.end(); ++HighScore )
			HighScore->second->WriteChunk_1000( writer );

		// Awardments
		for ( CloudberryKingdom::Set<int>::const_iterator guid = Awardments_Renamed->begin(); guid != Awardments_Renamed->end(); ++guid )
			Chunk::WriteSingle( writer, 2, ColorSchemeIndex );

		// Purchases
		for ( CloudberryKingdom::Set<int>::const_iterator guid = Purchases->begin(); guid != Purchases->end(); ++guid )
			Chunk::WriteSingle( writer, 3, ColorSchemeIndex );

		// Stats
		LifetimeStats->WriteChunk_4( writer );

		// Save seed
		MySavedSeeds->WriteChunk_5( writer );

		// Campaign (Chunks 100 and up)
		Chunk::WriteSingle( writer, 100, CampaignCoins );
		Chunk::WriteSingle( writer, 101, CampaignLevel );
	}

	void PlayerData::FailLoad()
	{
		MySavedSeeds = std::make_shared<SavedSeeds>();
		HighScores = std::unordered_map<int, ScoreEntry*>();
		Purchases = std::make_shared<Set<int> >();
		Awardments_Renamed = std::make_shared<Set<int> >();
	}

	void PlayerData::Deserialize( std::vector<unsigned char> Data )
	{
		for ( CloudberryKingdom::Chunks::const_iterator chunk = Chunks::Get( Data )->begin(); chunk != Chunks::Get(Data)->end(); ++chunk )
		{
			switch ( ( *chunk )->Type )
			{
				// Color scheme
				case 0:
					CustomColorScheme.ReadChunk_0( *chunk );
					ColorScheme_Renamed = CustomColorScheme;
					break;

				case 1:
					( *chunk )->ReadSingle( ColorSchemeIndex );

					if ( ColorSchemeIndex == Unset::Int )
						ColorSchemeIndex = 0;
					if ( ColorSchemeIndex >= 0 )
						ColorScheme_Renamed = ColorSchemeManager::ColorSchemes[ ColorSchemeIndex ];

					break;

				// High Scores
				case 1000:
					std::shared_ptr<ScoreEntry> score = std::make_shared<ScoreEntry>();
					score->ReadChunk_1000( *chunk );
					AddHighScore( score );
					break;

				// Awardments
				case 2:
					Awardments_Renamed += ( *chunk )->ReadInt();
					break;

				// Purchases
				case 3:
					Purchases += ( *chunk )->ReadInt();
					break;

				// Stats
				case 4:
					LifetimeStats->ReadChunk_4( *chunk );
					break;

				// Saved Seeds
				case 5:
					MySavedSeeds->ReadChunk_5( *chunk );
					break;

				// Campaign (Chunks 100 and up)
				case 100:
					CampaignCoins = ( *chunk )->ReadInt();
					break;
				case 101:
					CampaignLevel = ( *chunk )->ReadInt();
					break;
			}
		}
	}

	int PlayerData::GetHighScore( int GameId )
	{
		if ( HighScores.find( GameId ) != HighScores.end() )
			return HighScores[ GameId ]->Value;
		else
			return 0;
	}

	void PlayerData::AddHighScore( const std::shared_ptr<ScoreEntry> &score )
	{
		if ( HighScores.find( score->GameId ) != HighScores.end() && score->Value < HighScores[ score->GameId ]->Value )
			return;

		HighScores.AddOrOverwrite( score->GameId, score );

		// Mark this object as changed, so that it will be saved to disk.
		Changed = true;
	}

	const std::shared_ptr<PlayerStats> &PlayerData::getStats() const
	{
		return LevelStats;
	}

	std::shared_ptr<PlayerStats> PlayerData::GetStats( StatGroup group )
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

	std::shared_ptr<PlayerStats> PlayerData::GetSummedStats( StatGroup group )
	{
		if ( group == StatGroup_LIFETIME )
			return SumStats( StatGroup_TEMP, StatGroup_LEVEL, StatGroup_GAME, StatGroup_LIFETIME );
		if ( group == StatGroup_CAMPAIGN )
			return SumStats( StatGroup_TEMP, StatGroup_LEVEL, StatGroup_GAME, StatGroup_CAMPAIGN );
		if ( group == StatGroup_GAME )
			return SumStats( StatGroup_TEMP, StatGroup_LEVEL, StatGroup_GAME );
		if ( group == StatGroup_LEVEL )
			return SumStats( StatGroup_TEMP, StatGroup_LEVEL );
		if ( group == StatGroup_TEMP )
			return SumStats( StatGroup_TEMP );

		return 0;
	}

	std::shared_ptr<PlayerStats> PlayerData::SumStats( ... )
	{
		std::shared_ptr<PlayerStats> StatSum = std::make_shared<PlayerStats>();

		StatSum->Clean();
		for ( unknown::const_iterator g = group.begin(); g != group.end(); ++g )
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
	std::shared_ptr<Gamer> PlayerData::CheckForMatchingGamer()
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

	Microsoft::Xna::Framework::Vector4 PlayerData::GetTextColor()
	{
		Vector4 clr = ColorScheme_Renamed.SkinColor.DetailColor.ToVector4();
		if ( clr.W == 0 )
			clr = Vector4( 1, 1, 1, 1 );
		return clr;
	}

	void PlayerData::SetNameText( const std::shared_ptr<EzText> &text )
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

		TempStats = std::make_shared<PlayerStats>();
		LevelStats = std::make_shared<PlayerStats>();
		GameStats = std::make_shared<PlayerStats>();
		LifetimeStats = std::make_shared<PlayerStats>();

		CampaignStats = std::make_shared<PlayerStats>();
	}

	void PlayerData::InitializeInstanceFields()
	{
		CampaignLevel = 0;
		CampaignCoins = 0;
		StoredName = _T( "" );
		KeyboardUsedLast = false;
		ColorSchemeIndex = Unset::Int;
	}
}
