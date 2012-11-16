#ifndef RUSH
#define RUSH

#include <global_header.h>

namespace CloudberryKingdom
{
	class GUI_Timer_Base;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class GUI_Timer;
}

namespace CloudberryKingdom
{
	class StringWorldTimed;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;


namespace CloudberryKingdom
{
	class Rush : public Challenge
	{
	private:
		class RushOnTimeExpiredLambda : public Lambda_1<GUI_Timer_Base*>
		{
		private:
			std::shared_ptr<Rush> rush;

		public:
			RushOnTimeExpiredLambda( const std::shared_ptr<Rush> &rush );

			void Apply( const std::shared_ptr<GUI_Timer_Base> &Timer );
		};

	private:
		class OnLevelBeginLambda : public LambdaFunc_1<Level*, bool>
		{
		public:
			OnLevelBeginLambda();

			bool Apply( const std::shared_ptr<Level> &level );
		};

	private:
		class KillAllPlayersHelper : public LambdaFunc<bool>
		{
		private:
			std::shared_ptr<Rush> rush;
			std::shared_ptr<GameData> game;

		public:
			KillAllPlayersHelper( const std::shared_ptr<Rush> &rush, const std::shared_ptr<GameData> &game );

			bool Apply();
		};

	public:
		std::shared_ptr<GUI_Timer> Timer;
	protected:
		void OnTimeExpired( const std::shared_ptr<GUI_Timer_Base> &Timer );

		int StartIndex;
		std::shared_ptr<StringWorldTimed> MyStringWorld;
	public:
		virtual void Start( int StartLevel );

	protected:
		virtual void AdditionalPreStart();

	private:
		void InitializeInstanceFields();

public:
		Rush()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef RUSH
