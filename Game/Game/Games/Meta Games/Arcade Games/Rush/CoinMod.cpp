#include <global_header.h>

namespace CloudberryKingdom
{

	CoinMod::CoinMod( const std::shared_ptr<GUI_Timer> &Timer )
	{
		InitializeInstanceFields();
		this->MyTimer = Timer;
	}

	void CoinMod::CoinControl( const std::shared_ptr<Level> &level, int Index )
	{
		// Calculate difficulty based on level
		// t ranges from 0 to 1
		float t = CoreMath::RestrictVal( 0.f, 1.f, Index / static_cast<float>( LevelMax ) );

		switch ( CoinControlType )
		{
			case CoinControlTypes_MOD_NUMBER:
				CoinControl_ModNumber( level, t );
				break;
			case CoinControlTypes_MOD_VALUE:
				CoinControl_ModValue( level, t );
				break;
		}
	}

	void CoinMod::CoinControl_ModValue( const std::shared_ptr<Level> &level, float t )
	{
		int NumCoins = ModCoinNumber( level, 6 );

		// Par starts a 1.75 times the actual par, and decreases down to the actual par as t -> 1
		float par = level->Par * ( 2 * ( 1 - t ) + 1 * t );

		MyTimer->CoinTimeValue = static_cast<int>( par / NumCoins );
	}

	void CoinMod::CoinControl_ModNumber( const std::shared_ptr<Level> &level, float t )
	{
		// Par starts a 1.75 times the actual par, and decreases down to the actual par as t -> 1
		float par = level->Par * ( ParMultiplier_Start * ( 1 - t ) + ParMultiplier_End * t );

		int NumCoinsNeeded = static_cast<int>( static_cast<float>( par ) / MyTimer->CoinTimeValue + .65f );

		ModCoinNumber( level, NumCoinsNeeded );
	}

	int CoinMod::ModCoinNumber( const std::shared_ptr<Level> &level, int N )
	{
		// Get all coins
		ObjectVec coins = level->GetObjectList( ObjectType_COIN );

		for ( ObjectVec::const_iterator coin = coins.begin(); coin != coins.end(); ++coin )
			( *coin )->getCore()->MarkedForDeletion = true;

		ObjectVec keep = level->getRnd()->Choose(coins, N);

		for ( ObjectVec::const_iterator coin = keep.begin(); coin != keep.end(); ++coin )
			( *coin )->getCore()->MarkedForDeletion = false;

		int NumCoins = 0;
		for ( ObjectVec::const_iterator coin = coins.begin(); coin != coins.end(); ++coin )
		{
			if ( ( *coin )->getCore()->MarkedForDeletion )
				( *coin )->CollectSelf();
			else
				// Count the number of coins we keep.
				// May be different than N if there were few coins to start with
				NumCoins++;
		}

		level->NumCoins = NumCoins;

		return NumCoins;
	}

	void CoinMod::InitializeInstanceFields()
	{
		CoinControlType = CoinControlTypes_MOD_NUMBER;
		LevelMax = 50;
		ParMultiplier_Start = 1.5f;
		ParMultiplier_End = 1.05f;
	}
}
