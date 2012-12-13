#ifndef HELPMENU
#define HELPMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct HelpMenu : public CkBaseMenu
	{
	
		struct MakeListenerHelper : public Lambda
		{
		
			std::shared_ptr<Listener> listener;

		
			MakeListenerHelper( const std::shared_ptr<Listener> &listener );

			void Apply();
		};

	
		struct ReturnToCallerProxy : public Lambda
		{
		
			std::shared_ptr<HelpMenu> hm;

		
			ReturnToCallerProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct WatchComputerHelper : public Lambda
		{
		
			std::shared_ptr<HelpMenu> hm;

		
			WatchComputerHelper( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct WatchComputerProxy : public Lambda
		{
		
			std::shared_ptr<HelpMenu> hm;

		
			WatchComputerProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct IsShowGuidLambda : public LambdaFunc_1<std::shared_ptr<GameObject> , bool>
		{
		
			IsShowGuidLambda();

			bool Apply( const std::shared_ptr<GameObject> &obj );
		};

	
		struct IsSlowMoLambda : public LambdaFunc_1<std::shared_ptr<GameObject> , bool>
		{
		
			IsSlowMoLambda();

			bool Apply( const std::shared_ptr<GameObject> &obj );
		};

	
		struct Toggle_ShowPathHelper : public Lambda
		{
		
			std::shared_ptr<HelpMenu> hm;

		
			Toggle_ShowPathHelper( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct Toggle_ShowPathSetter : public Lambda
		{
		
			std::shared_ptr<HelpMenu> hm;
			bool state;

		
			Toggle_ShowPathSetter( const std::shared_ptr<HelpMenu> &hm, bool state );

			void Apply();
		};

	
		struct Toggle_ShowPathProxy : public Lambda_1<bool>
		{
		
			std::shared_ptr<HelpMenu> hm;

		
			Toggle_ShowPathProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply( const bool &state );
		};

	
		struct ShowPathProxy : public Lambda
		{
		
			std::shared_ptr<HelpMenu> hm;

		
			ShowPathProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct Toggle_SloMoHelperPredicate : public LambdaFunc_1<std::shared_ptr<GameObject> , bool>
		{
		
			bool Apply( const std::shared_ptr<GameObject> &match );
		};

	
		struct Toggle_SloMoHelper : public Lambda
		{
		
			std::shared_ptr<HelpMenu> hm;

		
			Toggle_SloMoHelper( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct Toggle_SlowMoProxy : public Lambda_1<bool>
		{
		
			std::shared_ptr<HelpMenu> hm;

		
			Toggle_SlowMoProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply( const bool &state );
		};

	
		struct SlowMoProxy : public Lambda
		{
		
			std::shared_ptr<HelpMenu> hm;

		
			SlowMoProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	
		struct CampaignCoinsLambda : public PlayerIntLambda
		{
		
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	
		int Bank();

		void Buy( int Cost );

		void SetCoins( int Coins );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		HelpMenu();
		void HelpMenu_Construct();

		static std::shared_ptr<GameObject> MakeListener();

	
		int DelayExit;
	
		virtual void ReturnToCaller();

		virtual bool MenuReturnToCaller( const std::shared_ptr<Menu> &menu );

	
		int Cost_Watch, Cost_Path, Cost_Slow;
		bool Allowed_WatchComputer();

		void WatchComputer();

		bool On_ShowPath();
		bool Allowed_ShowPath();

		void Toggle_ShowPath( bool state );

		void ShowPath();

		bool On_SlowMo();
		bool Allowed_SlowMo();

		void Toggle_SlowMo( bool state );

		void SlowMo();

	
		virtual void OnAdd();

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	
		std::shared_ptr<MenuItem> Item_ShowPath, Item_WatchComputer, Item_SlowMo;

		std::shared_ptr<EzText> CoinsText;

		std::shared_ptr<HelpBlurb> Blurb;

		void Initialization();

		void SetPos();

	
		virtual void AddItem( const std::shared_ptr<MenuItem> &item );

	
		virtual void ReturnToCaller( bool PlaySound );

		virtual void SlideIn( int Frames );

	
		virtual void SlideOut_RightPanel( GUI_Panel::PresetPos Preset, int Frames );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HELPMENU
