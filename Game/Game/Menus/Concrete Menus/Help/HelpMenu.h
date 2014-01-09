#ifndef HELPMENU
#define HELPMENU

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Games/GameType.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Concrete Menus/Help/HelpBlurb.h"
#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Menu Components/MenuToggle.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Objects/Game Objects/GameObjects/Guide.h"
//#include "Game/Objects/Game Objects/GameObjects/Listener.h"
//#include "Game/Objects/Game Objects/GameObjects/SlowMo.h"
//#include "Game/Menus/Concrete Menus/Help/HintGiver.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Grab/Coin.h"
//#include "Game/Player/Awardments/Awardment.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	enum CostGrowthTypes { CostGrowthTypes_None, CostGrowthTypes_DoublePerBuy };

	struct HelpMenu : public CkBaseMenu
	{

		virtual ~HelpMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "HelpMenu" );
#endif
		}


		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;

		struct MakeListenerHelper : public Lambda
		{
		
			boost::shared_ptr<Listener> listener;

		
			MakeListenerHelper( const boost::shared_ptr<Listener> &listener );

			void Apply();
		};

	
		struct ReturnToCallerProxy : public Lambda
		{
		
			boost::shared_ptr<HelpMenu> hm;

		
			ReturnToCallerProxy( const boost::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct WatchComputerHelper : public Lambda
		{
		
			boost::shared_ptr<HelpMenu> hm;

		
			WatchComputerHelper( const boost::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct WatchComputerProxy : public Lambda
		{
		
			boost::shared_ptr<HelpMenu> hm;

		
			WatchComputerProxy( const boost::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct IsShowGuidLambda : public LambdaFunc_1<boost::shared_ptr<GameObject> , bool>
		{
		
			IsShowGuidLambda();

			bool Apply( const boost::shared_ptr<GameObject> &obj );
		};

	
		struct IsSlowMoLambda : public LambdaFunc_1<boost::shared_ptr<GameObject> , bool>
		{
		
			IsSlowMoLambda();

			bool Apply( const boost::shared_ptr<GameObject> &obj );
		};

	
		struct Toggle_ShowPathHelper : public Lambda
		{
		
			boost::shared_ptr<HelpMenu> hm;

		
			Toggle_ShowPathHelper( const boost::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct Toggle_ShowPathSetter : public Lambda
		{
		
			boost::shared_ptr<HelpMenu> hm;
			bool state;

		
			Toggle_ShowPathSetter( const boost::shared_ptr<HelpMenu> &hm, bool state );

			void Apply();
		};

	
		struct Toggle_ShowPathProxy : public Lambda_1<bool>
		{
		
			boost::shared_ptr<HelpMenu> hm;

		
			Toggle_ShowPathProxy( const boost::shared_ptr<HelpMenu> &hm );

			void Apply( const bool &state );
		};

	
		struct ShowPathProxy : public Lambda
		{
		
			boost::shared_ptr<HelpMenu> hm;

		
			ShowPathProxy( const boost::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct Toggle_SloMoHelperPredicate : public LambdaFunc_1<boost::shared_ptr<GameObject> , bool>
		{
		
			bool Apply( const boost::shared_ptr<GameObject> &match );
		};

	
		struct Toggle_SloMoHelper : public Lambda
		{
		
			boost::shared_ptr<HelpMenu> hm;

		
			Toggle_SloMoHelper( const boost::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct Toggle_SlowMoProxy : public Lambda_1<bool>
		{
		
			boost::shared_ptr<HelpMenu> hm;

		
			Toggle_SlowMoProxy( const boost::shared_ptr<HelpMenu> &hm );

			void Apply( const bool &state );
		};

	
		struct SlowMoProxy : public Lambda
		{
		
			boost::shared_ptr<HelpMenu> hm;

		
			SlowMoProxy( const boost::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct CampaignCoinsLambda : public PlayerIntLambda
		{
		
			virtual ~CampaignCoinsLambda()
			{
#ifdef BOOST_BIN
				OnDestructor( "CampaignCoinsLambda" );
#endif
			}

			virtual int Apply( const boost::shared_ptr<PlayerData> &p );

		};

	
		int Bank();

		void Buy( int Cost );

		void SetCoins( int Coins );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		HelpMenu();
		boost::shared_ptr<HelpMenu> HelpMenu_Construct();

		static boost::shared_ptr<GameObject> MakeListener();

	
		int DelayExit;
	
		virtual void ReturnToCaller();

		virtual bool MenuReturnToCaller( const boost::shared_ptr<Menu> &menu );

	
		static CostGrowthTypes CostGrowthType;
		static int Cost_Multiplier_Watch, Cost_Multiplier_Path, Cost_Multiplier_Slow;

		static void SetCostGrowthType(CostGrowthTypes type);

		static int CurrentCostTo_Watch();
		static int CurrentCostTo_Slow();
		static int CurrentCostTo_Path();

		static int CostMultiplier;
		static int Cost_Watch, Cost_Path, Cost_Slow;
		bool Allowed_WatchComputer();

		void WatchComputer();

		bool On_ShowPath();
		bool Allowed_ShowPath();

		void Toggle_ShowPath( bool state );

		void ShowPath();

		bool On_SlowMo();
		bool Allowed_SlowMo();

		void Toggle_SlowMo( bool state );

		void DoSlowMo();

	
		virtual void OnAdd();

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

	
		boost::shared_ptr<MenuItem> Item_ShowPath, Item_WatchComputer, Item_SlowMo;

		boost::shared_ptr<EzText> CoinsText;

		boost::shared_ptr<HelpBlurb> Blurb;

		void Initialization();

		void SetPos();

	
		virtual void AddItem( const boost::shared_ptr<MenuItem> &item );

	
		virtual void ReturnToCaller( bool PlaySound );

		virtual void SlideIn( int Frames );

	
		virtual void SlideOut_RightPanel( GUI_Panel::PresetPos Preset, int Frames );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HELPMENU
