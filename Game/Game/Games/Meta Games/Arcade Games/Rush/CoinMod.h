#ifndef COINMOD
#define COINMOD

#include <small_header.h>

//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{
	struct CoinMod
	{
	
		enum CoinControlTypes
		{
			CoinControlTypes_MOD_NUMBER,
			CoinControlTypes_MOD_VALUE
		};

	
		boost::shared_ptr<GUI_Timer> MyTimer;
	
		CoinMod( const boost::shared_ptr<GUI_Timer> &Timer );

		/// <summary>
		/// The manner in which coins are controlled to control difficulty.
		/// </summary>
		CoinControlTypes CoinControlType;
		// The level after which difficulty doesn't increase (with respect to coins)
		int LevelMax;

		/// <summary>
		/// Restricts the number of coins in the level so that 
		/// the total amount of seconds possible to gain equals the level's par
		/// </summary>
		void CoinControl( const boost::shared_ptr<Level> &level, int Index );

	
		void CoinControl_ModValue( const boost::shared_ptr<Level> &level, float t );

		//public float ParMultiplier_Start = 1.85f, ParMultiplier_End = 1f;
	
		float ParMultiplier_Start, ParMultiplier_End;
	
		void CoinControl_ModNumber( const boost::shared_ptr<Level> &level, float t );

		int ModCoinNumber( const boost::shared_ptr<Level> &level, int N );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef COINMOD
