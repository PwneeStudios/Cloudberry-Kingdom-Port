#ifndef COINMOD
#define COINMOD

#include <global_header.h>

namespace CloudberryKingdom
{
	class GUI_Timer;
}

namespace CloudberryKingdom
{
	class Level;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;

namespace CloudberryKingdom
{
	class CoinMod
	{
	public:
		enum CoinControlTypes
		{
			CoinControlTypes_MOD_NUMBER,
			CoinControlTypes_MOD_VALUE
		};

	private:
		std::shared_ptr<GUI_Timer> MyTimer;
	public:
		CoinMod( const std::shared_ptr<GUI_Timer> &Timer );

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
		void CoinControl( const std::shared_ptr<Level> &level, int Index );

	private:
		void CoinControl_ModValue( const std::shared_ptr<Level> &level, float t );

		//public float ParMultiplier_Start = 1.85f, ParMultiplier_End = 1f;
	public:
		float ParMultiplier_Start, ParMultiplier_End;
	private:
		void CoinControl_ModNumber( const std::shared_ptr<Level> &level, float t );

		int ModCoinNumber( const std::shared_ptr<Level> &level, int N );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef COINMOD
