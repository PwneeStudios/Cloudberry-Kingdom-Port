#ifndef INGAMESTARTMENU
#define INGAMESTARTMENU

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Text/EzText.h"
//#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/ControlScreen.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/SaveLoadSeedMenu.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyQuitLevel.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyRemove.h"
//#include "Game/Menus/Concrete Menus/Score Screens/StatsScreen.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Sub Menus/SoundMenu.h"
//#include "Game/Objects/Game Objects/GameObjects/Listener.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Player/Stats.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct InGameStartMenu : public CkBaseMenu
	{

		bool CenterItems;

		virtual ~InGameStartMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "InGameStartMenu" );
#endif
		}


		struct UnpauseLambda : public Lambda
		{
			boost::shared_ptr<InGameStartMenu> igsm;
		
			UnpauseLambda( boost::shared_ptr<InGameStartMenu> igsm );

			void Apply();
		};

		struct MakeListenerHelper : public LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> >
		{
		
			boost::shared_ptr<GUI_Panel> Apply( const boost::shared_ptr<Listener> &listener );
		};

	
		struct PreventMenuHelper : public Lambda
		{
		
			boost::shared_ptr<Listener> listener;
			boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > Make;

		
			PreventMenuHelper( const boost::shared_ptr<Listener> &listener, const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > &Make );

			void Apply();
		};

	
		struct GoRemoveProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoRemoveProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoControlsHelper : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoControlsHelper( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoControlsProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoControlsProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoOptionsProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoOptionsProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoSaveLoadProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoSaveLoadProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoStatsProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoStatsProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct VerifyExitProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			VerifyExitProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		static bool PreventMenu;

		InGameStartMenu( int Control );
		boost::shared_ptr<InGameStartMenu> InGameStartMenu_Construct( int Control );

		static boost::shared_ptr<GameObject> MakeListener();

		static boost::shared_ptr<GameObject> MakeListener_Base( const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > &Make );

		void OnAdd();

		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

	
		virtual void OnReturnTo();

	
		boost::shared_ptr<MenuItem> RemoveMe;
	
		virtual void Init();

	
		bool MenuReturnToCaller( boost::shared_ptr<Menu> menu );
        boost::shared_ptr<Level> HoldLevel;
        void Unpause();


		void GoRemove();

		void GoControls();

		void GoOptions();

		void GoSaveLoad();

		void GoStats();

		void SetPos();
		void SetPos_WithRemoveMe();
	
		virtual void MakeExitItem();

	
		void VerifyExit();

	
		virtual void MyDraw();
	};
}


#endif	//#ifndef INGAMESTARTMENU
