#ifndef RUSH
#define RUSH

#include <small_header.h>

//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Games/GameType.h"
#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Games/Meta Games/StringWorlds/StringWorld_Timed.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Base.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"


namespace CloudberryKingdom
{
	struct Rush : public Challenge
	{
	
		virtual ~Rush()
		{
#ifdef BOOST_BIN
			OnDestructor( "Rush" );
#endif
		}


		struct RushOnTimeExpiredLambda : public Lambda_1<boost::shared_ptr<GUI_Timer_Base> >
		{
		
			boost::shared_ptr<Rush> rush;

		
			RushOnTimeExpiredLambda( const boost::shared_ptr<Rush> &rush );

			void Apply( const boost::shared_ptr<GUI_Timer_Base> &Timer );
		};

	
		struct OnLevelBeginLambda : public LambdaFunc_1<boost::shared_ptr<Level> , bool>
		{
		
			OnLevelBeginLambda();

			bool Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct KillAllPlayersHelper : public LambdaFunc<bool>
		{
		
			boost::shared_ptr<Rush> rush;
			boost::shared_ptr<GameData> game;

		
			KillAllPlayersHelper( const boost::shared_ptr<Rush> &rush, const boost::shared_ptr<GameData> &game );

			bool Apply();
		};

	
		boost::shared_ptr<GUI_Timer> Timer;
	
		void OnTimeExpired( const boost::shared_ptr<GUI_Timer_Base> &Timer );

		int StartIndex;
		boost::shared_ptr<StringWorldTimed> MyStringWorld;
	
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
