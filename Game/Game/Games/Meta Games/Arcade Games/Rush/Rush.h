#ifndef RUSH
#define RUSH

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Rush : public Challenge
	{
	
		struct RushOnTimeExpiredLambda : public Lambda_1<std::shared_ptr<GUI_Timer_Base> >
		{
		
			std::shared_ptr<Rush> rush;

		
			RushOnTimeExpiredLambda( const std::shared_ptr<Rush> &rush );

			void Apply( const std::shared_ptr<GUI_Timer_Base> &Timer );
		};

	
		struct OnLevelBeginLambda : public LambdaFunc_1<std::shared_ptr<Level> , bool>
		{
		
			OnLevelBeginLambda();

			bool Apply( const std::shared_ptr<Level> &level );
		};

	
		struct KillAllPlayersHelper : public LambdaFunc<bool>
		{
		
			std::shared_ptr<Rush> rush;
			std::shared_ptr<GameData> game;

		
			KillAllPlayersHelper( const std::shared_ptr<Rush> &rush, const std::shared_ptr<GameData> &game );

			bool Apply();
		};

	
		std::shared_ptr<GUI_Timer> Timer;
	
		void OnTimeExpired( const std::shared_ptr<GUI_Timer_Base> &Timer );

		int StartIndex;
		std::shared_ptr<StringWorldTimed> MyStringWorld;
	
		virtual void Start( int StartLevel );

	
		virtual void AdditionalPreStart();

	
		void InitializeInstanceFields();


		Rush()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef RUSH
