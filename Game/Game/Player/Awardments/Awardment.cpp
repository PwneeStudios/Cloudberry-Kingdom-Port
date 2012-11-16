#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;


namespace CloudberryKingdom
{

	Awardment::Awardment( int Guid, const std::wstring &Name, const std::wstring &Description, const std::shared_ptr<Hat> &Unlockable )
	{
		this->Name = Name;
		this->Description = Description;
		this->Unlockable = Unlockable;
		this->Guid = Guid;

		if ( this->Unlockable != 0 )
			this->Unlockable->AssociatedAward = this;

		Awardments::Awards.push_back( this );
	}

	int Awardments::CheckpointsStatsLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( StatGroup_LEVEL )->Checkpoints;
	}

	int Awardments::CoinsStatsLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( StatGroup_LEVEL )->Coins;
	}

	int Awardments::TotalCoinsStatsLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( StatGroup_LEVEL )->TotalCoins;
	}

std::vector<Awardment*> Awardments::Awards = std::vector<Awardment*>();
std::unordered_map<int, Awardment*> Awardments::AwardsDict = std::unordered_map<int, Awardment*>();

	bool Awardments::MessageOnScreen()
	{
		for ( std::vector<GameObject*>::const_iterator obj = Tools::CurGameData->MyGameObjects.begin(); obj != Tools::CurGameData->MyGameObjects.end(); ++obj )
		{
			if ( dynamic_cast<AwardmentMessage*>( *obj ) != 0 )
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
		for ( std::vector<PlayerData*>::const_iterator p = PlayerManager::getExistingPlayers().begin(); p != PlayerManager::getExistingPlayers().end(); ++p )
		{
			std::shared_ptr<PlayerStats> stats = ( *p )->GetStats( StatGroup_LEVEL );
			float ratio = stats->FinalTimeSpentNotMoving / static_cast<float>( stats->FinalTimeSpent );
			if ( ratio < .05f && stats->FinalTimeSpentNotMoving < 35 )
				Ran = true;
		}

		bool Reqs = CustomLevel_GUI::IsMaxLength && CustomLevel_GUI::Difficulty >= 1 && PlayerManager::PlayerSum( std::make_shared<CheckpointsStatsLambda>() ) == 0 && Tools::CurGameData->Freeplay && Tools::CurGameData->DefaultHeroType == BobPhsxNormal::getInstance();

		if ( Ran && Reqs )
			GiveAward( HoldForwardFreeplay );
	}

	void Awardments::CheckForAward_NoCoins()
	{
		bool NoCoins = PlayerManager::PlayerSum( std::make_shared<CoinsStatsLambda>() ) == 0 && PlayerManager::PlayerMax(std::make_shared<TotalCoinsStatsLambda>()) > 5;

		bool Reqs = CustomLevel_GUI::IsMaxLength && CustomLevel_GUI::Difficulty >= 1 && PlayerManager::PlayerSum( std::make_shared<CheckpointsStatsLambda>() ) == 0 && Tools::CurGameData->Freeplay && Tools::CurGameData->DefaultHeroType == BobPhsxNormal::getInstance();

		if ( NoCoins && Reqs )
			GiveAward( NoCoinFreeplay );
	}

int Awardments::HeroRushScore = 500000;

	void Awardments::CheckForAward_HeroRush_Score( int Score )
	{
		if ( Score > HeroRushScore )
			GiveAward( HeroRush_Score );
	}

int Awardments::HeroRush2Score = 500000;

	void Awardments::CheckForAward_HeroRush2_Score( int Score )
	{
		if ( Score > HeroRush2Score )
			GiveAward( HeroRush2_Score );
	}

int Awardments::HeroRush2_LevelUnlock = 35;

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

int Awardments::FastCampaign_Minutes = 20;

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

	void Awardments::CheckForAward_JumpAlot( const std::shared_ptr<Bob> &bob )
	{
		int jumps = bob->getMyStats()->Jumps + PlayerManager::Get(bob)->GameStats->Jumps + PlayerManager::Get(bob)->LifetimeStats->Jumps;
		if ( jumps >= LotsOfJumps )
			GiveAward( JumpAlot );
	}

float CurShift, Awardments::Shift = 520;

	void Awardments::GiveAward( const std::shared_ptr<Awardment> &award )
	{
		if ( award == 0 )
			return;

		if ( PlayerManager::NotAllAwarded( award ) )
		{
			// Give the award to each player
			for ( std::vector<PlayerData*>::const_iterator p = PlayerManager::getExistingPlayers().begin(); p != PlayerManager::getExistingPlayers().end(); ++p )
				( *p )->Awardments_Renamed += award->Guid;

			// Show a note saying the reward was given
			std::shared_ptr<AwardmentMessage> msg = std::make_shared<AwardmentMessage>( award );
			// Don't add any awardments!
			//Tools.CurGameData.AddGameObject(msg);
			Tools::Warning();

			// Remove all other hints
			for ( std::vector<GameObject*>::const_iterator obj = Tools::CurGameData->MyGameObjects.begin(); obj != Tools::CurGameData->MyGameObjects.end(); ++obj )
			{
				if ( *obj == msg )
					continue;

				std::shared_ptr<AwardmentMessage> _msg = dynamic_cast<AwardmentMessage*>( *obj );
				if ( 0 != _msg )
					_msg->MyPile->setPos( _msg->MyPile->getPos() + Vector2(0, Shift) );
			}

			PlayerManager::SavePlayerData->Changed = true;
		}
	}

std::wstring Awardments::BeatStr = _T( "Beat a classic castle\non" );
const Awardment* tempVector[] = { 0, std::make_shared<Awardment>( 1, _T( "Italian Plumbing" ), BeatStr + CampaignHelper::GetName( 2 ), Hat::Toad ), std::make_shared<Awardment>( 2, _T( "Bubbly Bop" ), BeatStr + CampaignHelper::GetName( 3 ), Hat::BubbleBobble ), std::make_shared<Awardment>( 3, _T( "Ghouls n' stickmen" ), BeatStr + CampaignHelper::GetName( 4 ), Hat::Knight ), std::make_shared<Awardment>( 4, _T( "Gosu Master" ), BeatStr + CampaignHelper::GetName( 5 ), Hat::Gosu ) };
std::vector<Awardment*> Awardments::BeatCampaign = std::vector<Awardment*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
std::shared_ptr<Awardment> Awardments::JumpAlot = std::make_shared<Awardment>( 5, _T( "Jumple-upagus" ), _T( "Jump " ) + StringConverterHelper::toString( LotsOfJumps ) + _T( " times." ), Hat::Bubble );
std::shared_ptr<Awardment> Awardments::HoldForwardFreeplay = std::make_shared<Awardment>( 6, _T( "White Rabbit" ), _T( "Beat a max length " ) + CampaignHelper::GetName( 2 ) + _T( "level, always holding forward. Classic hero. No checkpoints." ), Hat::Cloud_Renamed );
std::shared_ptr<Awardment> Awardments::HeroRush_Score = std::make_shared<Awardment>( 7, _T( "Locked IN" ), _T( "Score " ) + HeroRushScore + _T( " points in Hero Rush." ), Hat::FallingBlockHead );
std::shared_ptr<Awardment> Awardments::Escalation_Levels = std::make_shared<Awardment>( 8, _T( "Iron Man" ), _T( "Beat 26.2 levels in Escalation." ), Hat::FireHead );
std::shared_ptr<Awardment> Awardments::FastCampaign2 = std::make_shared<Awardment>( 10, _T( "Minute man" ), _T( "Beat an" ) + CampaignHelper::GetName( 3 ) + _T( "castle in under " ) + StringConverterHelper::toString( FastCampaign_Minutes ) + _T( " minutes." ), Hat::Pink );
std::shared_ptr<Awardment> Awardments::HeroRush2_Score = std::make_shared<Awardment>( 12, _T( "Jack of all sticks" ), _T( "Score " ) + HeroRush2Score + _T( " points\nin Hero Rush 2:\n{c255,10,10,255}Revenge of the Double Jump." ), Hat::Fedora );
std::shared_ptr<Awardment> Awardments::PartiallyInvisibleCampaign = std::make_shared<Awardment>( 13, _T( "I HAVE NO FEET" ), _T( "Beat an" ) + CampaignHelper::GetName( 3 ) + _T( "castle while invisible. Cape and hat recommended." ), Hat::Ghost );
std::shared_ptr<Awardment> Awardments::TotallyInvisibleCampaign = std::make_shared<Awardment>( 14, _T( "Mind Games" ), _T( "Beat a" ) + CampaignHelper::GetName( 1 ) + _T( "castle while invisible, with no hat and no cape." ), Hat::Brain );
std::shared_ptr<Awardment> Awardments::NoCoinFreeplay = std::make_shared<Awardment>( 15, _T( "Chromotephobia" ), _T( "Beat a max length " ) + CampaignHelper::GetName( 2 ) + _T( "level without grabbing a single coin. Classic hero. No checkpoints." ), Hat::CheckpointHead );
std::shared_ptr<Awardment> Awardments::AllCoinsAbusiveCastle = std::make_shared<Awardment>( 16, _T( "Ebenezer" ), _T( "Grab every coin in\nan" ) + CampaignHelper::GetName( 3 ) + _T( "castle." ), Hat::TopHat );
std::shared_ptr<Awardment> Awardments::NoDeathsNormalCastle = std::make_shared<Awardment>( 17, _T( "Untouchable" ), _T( "Beat an" ) + CampaignHelper::GetName( 2 ) + _T( "castle without dying once." ), Hat::Afro );
std::shared_ptr<Awardment> Awardments::PerfectEasyCastle = std::make_shared<Awardment>( 18, _T( "Perfection" ), _T( "Grab every coin in a" ) + CampaignHelper::GetName( 1 ) + _T( "castle without dying once. Image is everything." ), Hat::Halo );
std::shared_ptr<Awardment> Awardments::UnlockHeroRush2 = std::make_shared<Awardment>( 100, _T( "Hero Rush 2 unlocked!" ), std::wstring::Format( _T( "{0}Required:{1}\n   Level {3} in {2}Hero Rush" ), EzText::ColorToMarkup( Color( 205, 10, 10 ) ), EzText::ColorToMarkup( Color::White ), EzText::ColorToMarkup( Color( 26, 178, 231 ) ), HeroRush2_LevelUnlock ), 0 );

	void Awardments::Init()
	{
		for ( std::vector<Awardment*>::const_iterator award = Awards.begin(); award != Awards.end(); ++award )
			AwardsDict.insert( make_pair( ( *award )->Guid, *award ) );
	}
}
