#include <global_header.h>

#include <Hacks/List.h>
#include <Hacks/String.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void Awardments::InitializeStatics()
	{
		Awardments::HeroRushScore = 500000;
		Awardments::HeroRush2Score = 500000;
		Awardments::HeroRush2_LevelUnlock = 35;
		Awardments::FastCampaign_Minutes = 20;
		Awardments::CurShift = 0;
		Awardments::Shift = 520;

		Awardments::BeatStr = _T( "Beat a classic castle\non" );
	
		boost::shared_ptr<Awardment> tempVector[] = { boost::shared_ptr<Awardment>(), boost::make_shared<Awardment>( 1, _T( "Italian Plumbing" ), Awardments::BeatStr + CampaignHelper::GetName( 2 ), Hat::Toad ), boost::make_shared<Awardment>( 2, _T( "Bubbly Bop" ), Awardments::BeatStr + CampaignHelper::GetName( 3 ), Hat::BubbleBobble ), boost::make_shared<Awardment>( 3, _T( "Ghouls n' stickmen" ), Awardments::BeatStr + CampaignHelper::GetName( 4 ), Hat::Knight ), boost::make_shared<Awardment>( 4, _T( "Gosu Master" ), Awardments::BeatStr + CampaignHelper::GetName( 5 ), Hat::Gosu ) };
		Awardments::BeatCampaign = VecFromArray( tempVector );
	
		for ( std::vector<boost::shared_ptr<Awardment> >::iterator award = Awardments::BeatCampaign.begin(); award != Awardments::BeatCampaign.end(); ++award ) 
		{
			if ( *award != 0 )
				Awardment_PostConstruct( *award );
		}

		Awardments::JumpAlot = boost::make_shared<Awardment>( 5, _T( "Jumple-upagus" ), _T( "Jump " ) + StringConverterHelper::toString( LotsOfJumps ) + _T( " times." ), Hat::Bubble );
		Awardment_PostConstruct( Awardments::JumpAlot );
		Awardments::HoldForwardFreeplay = boost::make_shared<Awardment>( 6, _T( "White Rabbit" ), std::wstring( _T( "Beat a max length " ) ) + CampaignHelper::GetName( 2 ) + std::wstring( _T( "level, always holding forward. Classic hero. No checkpoints." ) ), Hat::Cloud_Renamed );
		Awardment_PostConstruct( Awardments::HoldForwardFreeplay );
		Awardments::HeroRush_Score = boost::make_shared<Awardment>( 7, _T( "Locked IN" ), std::wstring( _T( "Score " ) ) + ToString( HeroRushScore ) + std::wstring( _T( " points in Hero Rush." ) ), Hat::FallingBlockHead );
		Awardment_PostConstruct( Awardments::HeroRush_Score );
		Awardments::Escalation_Levels = boost::make_shared<Awardment>( 8, _T( "Iron Man" ), _T( "Beat 26.2 levels in Escalation." ), Hat::FireHead );
		Awardment_PostConstruct( Awardments::Escalation_Levels );
		Awardments::FastCampaign2 = boost::make_shared<Awardment>( 10, _T( "Minute man" ), std::wstring( _T( "Beat an" ) ) + CampaignHelper::GetName( 3 ) + std::wstring( _T( "castle in under " ) ) + StringConverterHelper::toString( FastCampaign_Minutes ) + std::wstring( _T( " minutes." ) ), Hat::Pink );
		Awardment_PostConstruct( Awardments::FastCampaign2 );
		Awardments::HeroRush2_Score = boost::make_shared<Awardment>( 12, _T( "Jack of all sticks" ), std::wstring( _T( "Score " ) ) + ToString( HeroRush2Score ) + std::wstring( _T( " points\nin Hero Rush 2:\n{c255,10,10,255}Revenge of the Double Jump." ) ), Hat::Fedora );
		Awardment_PostConstruct( Awardments::HeroRush2_Score );
		Awardments::PartiallyInvisibleCampaign = boost::make_shared<Awardment>( 13, _T( "I HAVE NO FEET" ), std::wstring( _T( "Beat an" ) ) + CampaignHelper::GetName( 3 ) + std::wstring( _T( "castle while invisible. Cape and hat recommended." ) ), Hat::Ghost );
		Awardment_PostConstruct( Awardments::PartiallyInvisibleCampaign );
		Awardments::TotallyInvisibleCampaign = boost::make_shared<Awardment>( 14, _T( "Mind Games" ), _T( "Beat a" ) + CampaignHelper::GetName( 1 ) + _T( "castle while invisible, with no hat and no cape." ), Hat::Brain );
		Awardment_PostConstruct( Awardments::TotallyInvisibleCampaign );
		Awardments::NoCoinFreeplay = boost::make_shared<Awardment>( 15, _T( "Chromotephobia" ), _T( "Beat a max length " ) + CampaignHelper::GetName( 2 ) + _T( "level without grabbing a single coin. Classic hero. No checkpoints." ), Hat::CheckpointHead );
		Awardment_PostConstruct( Awardments::NoCoinFreeplay );
		Awardments::AllCoinsAbusiveCastle = boost::make_shared<Awardment>( 16, _T( "Ebenezer" ), _T( "Grab every coin in\nan" ) + CampaignHelper::GetName( 3 ) + _T( "castle." ), Hat::TopHat );
		Awardment_PostConstruct( Awardments::AllCoinsAbusiveCastle );
		Awardments::NoDeathsNormalCastle = boost::make_shared<Awardment>( 17, _T( "Untouchable" ), _T( "Beat an" ) + CampaignHelper::GetName( 2 ) + _T( "castle without dying once." ), Hat::Afro );
		Awardment_PostConstruct( Awardments::NoDeathsNormalCastle );
		Awardments::PerfectEasyCastle = boost::make_shared<Awardment>( 18, _T( "Perfection" ), _T( "Grab every coin in a" ) + CampaignHelper::GetName( 1 ) + _T( "castle without dying once. Image is everything." ), Hat::Halo );
		Awardment_PostConstruct( Awardments::PerfectEasyCastle );
		Awardments::UnlockHeroRush2 = boost::make_shared<Awardment>( 100, _T( "Hero Rush 2 unlocked!" ),
			Format( _T( "%lsRequired:%ls\n   Level %d in %lsHero Rush" ),
			EzText::ColorToMarkup( Color( unsigned char( 205 ), unsigned char( 10 ), unsigned char( 10 ) ) ).c_str(),
				EzText::ColorToMarkup( Color::White ).c_str(),
				HeroRush2_LevelUnlock,
				EzText::ColorToMarkup( Color( unsigned char( 26 ), unsigned char( 178 ), unsigned char( 231 ) ) ).c_str() ),
			boost::shared_ptr<Hat>() );
		Awardment_PostConstruct( Awardments::UnlockHeroRush2 );
	}

	// Statics
	std::vector<boost::shared_ptr<Awardment> > Awardments::Awards;
	std::map<int, boost::shared_ptr<Awardment> > Awardments::AwardsDict;

	int Awardments::HeroRushScore = 500000;
	int Awardments::HeroRush2Score = 500000;
	int Awardments::HeroRush2_LevelUnlock = 35;
	int Awardments::FastCampaign_Minutes = 20;
	float Awardments::CurShift, Awardments::Shift = 520;

	std::wstring Awardments::BeatStr;
	std::vector<boost::shared_ptr<Awardment> > Awardments::BeatCampaign;
	boost::shared_ptr<Awardment> Awardments::JumpAlot;
	boost::shared_ptr<Awardment> Awardments::HoldForwardFreeplay;
	boost::shared_ptr<Awardment> Awardments::HeroRush_Score;
	boost::shared_ptr<Awardment> Awardments::Escalation_Levels;
	boost::shared_ptr<Awardment> Awardments::FastCampaign2;
	boost::shared_ptr<Awardment> Awardments::HeroRush2_Score;
	boost::shared_ptr<Awardment> Awardments::PartiallyInvisibleCampaign;
	boost::shared_ptr<Awardment> Awardments::TotallyInvisibleCampaign;
	boost::shared_ptr<Awardment> Awardments::NoCoinFreeplay;
	boost::shared_ptr<Awardment> Awardments::AllCoinsAbusiveCastle;
	boost::shared_ptr<Awardment> Awardments::NoDeathsNormalCastle;
	boost::shared_ptr<Awardment> Awardments::PerfectEasyCastle;
	boost::shared_ptr<Awardment> Awardments::UnlockHeroRush2;



	Awardment::Awardment( int Guid, const std::wstring &Name, const std::wstring &Description, const boost::shared_ptr<Hat> &Unlockable )
	{
		this->Name = Name;
		this->Description = Description;
		this->Unlockable = Unlockable;
		this->Guid = Guid;

		// Pulled out to avoid using shared_from_this inside constructor.
		//if ( this->Unlockable != 0 )
		//	this->Unlockable->AssociatedAward = shared_from_this();

		//Awardments::Awards.push_back( shared_from_this() );
	}

	int Awardments::CheckpointsStatsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( StatGroup_LEVEL )->Checkpoints;
	}

	int Awardments::CoinsStatsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( StatGroup_LEVEL )->Coins;
	}

	int Awardments::TotalCoinsStatsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( StatGroup_LEVEL )->TotalCoins;
	}

	bool Awardments::MessageOnScreen()
	{
		for ( GameObjVec::const_iterator obj = Tools::CurGameData->MyGameObjects.begin(); obj != Tools::CurGameData->MyGameObjects.end(); ++obj )
		{
			if ( boost::dynamic_pointer_cast<AwardmentMessage>( *obj ) != 0 )
				return true;
		}

		return false;
	}

	int Awardments::AwardDelay()
	{
		if ( MessageOnScreen() )
			return 160;
		else
			return 0;
	}

	void Awardments::CheckForAward_HoldForward()
	{
		bool Ran = false;
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator p = PlayerManager::getExistingPlayers().begin(); p != PlayerManager::getExistingPlayers().end(); ++p )
		{
			boost::shared_ptr<PlayerStats> stats = ( *p )->GetStats( StatGroup_LEVEL );
			float ratio = stats->FinalTimeSpentNotMoving / static_cast<float>( stats->FinalTimeSpent );
			if ( ratio < .05f && stats->FinalTimeSpentNotMoving < 35 )
				Ran = true;
		}

		bool Reqs = CustomLevel_GUI::IsMaxLength && CustomLevel_GUI::Difficulty >= 1 && PlayerManager::PlayerSum( boost::make_shared<CheckpointsStatsLambda>() ) == 0 && Tools::CurGameData->Freeplay && Tools::CurGameData->DefaultHeroType == BobPhsxNormal::getInstance();

		if ( Ran && Reqs )
			GiveAward( HoldForwardFreeplay );
	}

	void Awardments::CheckForAward_NoCoins()
	{
		bool NoCoins = PlayerManager::PlayerSum( boost::make_shared<CoinsStatsLambda>() ) == 0 && PlayerManager::PlayerMax(boost::make_shared<TotalCoinsStatsLambda>()) > 5;

		bool Reqs = CustomLevel_GUI::IsMaxLength && CustomLevel_GUI::Difficulty >= 1 && PlayerManager::PlayerSum( boost::make_shared<CheckpointsStatsLambda>() ) == 0 && Tools::CurGameData->Freeplay && Tools::CurGameData->DefaultHeroType == BobPhsxNormal::getInstance();

		if ( NoCoins && Reqs )
			GiveAward( NoCoinFreeplay );
	}

	void Awardments::CheckForAward_HeroRush_Score( int Score )
	{
		if ( Score > HeroRushScore )
			GiveAward( HeroRush_Score );
	}

	void Awardments::CheckForAward_HeroRush2_Score( int Score )
	{
		if ( Score > HeroRush2Score )
			GiveAward( HeroRush2_Score );
	}

	void Awardments::CheckForAward_HeroRush2Unlock( int Level_Renamed )
	{
		//if (Level >= 3)
		if ( Level_Renamed >= HeroRush2_LevelUnlock )
			GiveAward( UnlockHeroRush2 );
	}

	void Awardments::CheckForAward_Escalation_Level( int Level_Renamed )
	{
		if ( Level_Renamed >= 26.2f - 1 )
			GiveAward( Escalation_Levels );
	}

	void Awardments::CheckForAward_BeatCampaign( int Index )
	{
		GiveAward( BeatCampaign[ Index ] );
	}

	void Awardments::CheckForAward_FastCampaign( int Index )
	{
		if ( Index != 2 )
			return;

		//if (Campaign.Time < FastCampaign_Minutes * 60 * 62)
		//    GiveAward(FastCampaign2);
	}

	void Awardments::CheckForAward_EbenezerAbusiveCastle( int Index )
	{
		if ( Index < 2 )
			return;

		//if (Campaign.Coins == Campaign.TotalCoins)
		//    GiveAward(AllCoinsAbusiveCastle);
	}

	void Awardments::CheckForAward_PerfectEasyCastle( int Index )
	{
		if ( Index < 0 )
			return;

		//if (Campaign.Coins == Campaign.TotalCoins && Campaign.Attempts == 0)
		//    GiveAward(PerfectEasyCastle);
	}

	void Awardments::CheckForAward_NoDeathNormalCastle( int Index )
	{
		if ( Index < 0 )
			return;

		//if (Campaign.Attempts == 0)
		//    GiveAward(NoDeathsNormalCastle);
	}

	void Awardments::CheckForAward_PartiallyInvisible( int Index )
	{
		if ( Index < 2 )
			return;

		if ( PlayerManager::PartiallyInvisible )
			GiveAward( PartiallyInvisibleCampaign );
	}

	void Awardments::CheckForAward_TotallyInvisible( int Index )
	{
		if ( Index < 0 )
			return;

		if ( PlayerManager::TotallyInvisible )
			GiveAward( TotallyInvisibleCampaign );
	}

	void Awardments::CheckForAward_JumpAlot( const boost::shared_ptr<Bob> &bob )
	{
		int jumps = bob->getMyStats()->Jumps + PlayerManager::Get(bob)->GameStats->Jumps + PlayerManager::Get(bob)->LifetimeStats->Jumps;
		if ( jumps >= LotsOfJumps )
			GiveAward( JumpAlot );
	}

	void Awardments::GiveAward( const boost::shared_ptr<Awardment> &award )
	{
		if ( award == 0 )
			return;

		if ( PlayerManager::NotAllAwarded( award ) )
		{
			// Give the award to each player
			for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator p = PlayerManager::getExistingPlayers().begin(); p != PlayerManager::getExistingPlayers().end(); ++p )
				( *p )->Awardments_Renamed->Add( award->Guid );

			// Show a note saying the reward was given
			boost::shared_ptr<AwardmentMessage> msg = MakeMagic( AwardmentMessage, ( award ) );
			// Don't add any awardments!
			//Tools.CurGameData.AddGameObject(msg);
			Tools::Warning();

			// Remove all other hints
			for ( GameObjVec::const_iterator obj = Tools::CurGameData->MyGameObjects.begin(); obj != Tools::CurGameData->MyGameObjects.end(); ++obj )
			{
				if ( *obj == msg )
					continue;

				boost::shared_ptr<AwardmentMessage> _msg = boost::dynamic_pointer_cast<AwardmentMessage>( *obj );
				if ( 0 != _msg )
					_msg->MyPile->setPos( _msg->MyPile->getPos() + Vector2(0, Shift) );
			}

			PlayerManager::SavePlayerData->Changed = true;
		}
	}

	void Awardments::Init()
	{
		for ( std::vector<boost::shared_ptr<Awardment> >::const_iterator award = Awards.begin(); award != Awards.end(); ++award )
			AwardsDict.insert( std::make_pair( ( *award )->Guid, *award ) );
	}
}
