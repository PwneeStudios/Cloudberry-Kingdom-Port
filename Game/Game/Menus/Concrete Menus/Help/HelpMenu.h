#ifndef HELPMENU
#define HELPMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class Listener;
}

namespace CloudberryKingdom
{
	class GameObject;
}

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class Menu;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class HelpBlurb;
}







namespace CloudberryKingdom
{
	class HelpMenu : public CkBaseMenu
	{
	private:
		class MakeListenerHelper : public Lambda
		{
		private:
			std::shared_ptr<Listener> listener;

		public:
			MakeListenerHelper( const std::shared_ptr<Listener> &listener );

			void Apply();
		};

	private:
		class ReturnToCallerProxy : public Lambda
		{
		private:
			std::shared_ptr<HelpMenu> hm;

		public:
			ReturnToCallerProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	private:
		class WatchComputerHelper : public Lambda
		{
		private:
			std::shared_ptr<HelpMenu> hm;

		public:
			WatchComputerHelper( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	private:
		class WatchComputerProxy : public Lambda
		{
		private:
			std::shared_ptr<HelpMenu> hm;

		public:
			WatchComputerProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	private:
		class IsShowGuidLambda : public LambdaFunc_1<GameObject*, bool>
		{
		public:
			IsShowGuidLambda();

			bool Apply( const std::shared_ptr<GameObject> &obj );
		};

	private:
		class IsSlowMoLambda : public LambdaFunc_1<GameObject*, bool>
		{
		public:
			IsSlowMoLambda();

			bool Apply( const std::shared_ptr<GameObject> &obj );
		};

	private:
		class Toggle_ShowPathHelper : public Lambda
		{
		private:
			std::shared_ptr<HelpMenu> hm;

		public:
			Toggle_ShowPathHelper( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	private:
		class Toggle_ShowPathSetter : public Lambda
		{
		private:
			std::shared_ptr<HelpMenu> hm;
			bool state;

		public:
			Toggle_ShowPathSetter( const std::shared_ptr<HelpMenu> &hm, bool state );

			void Apply();
		};

	private:
		class Toggle_ShowPathProxy : public Lambda_1<bool>
		{
		private:
			std::shared_ptr<HelpMenu> hm;

		public:
			Toggle_ShowPathProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply( bool state );
		};

	private:
		class ShowPathProxy : public Lambda
		{
		private:
			std::shared_ptr<HelpMenu> hm;

		public:
			ShowPathProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	private:
		class Toggle_SloMoHelperPredicate : public LambdaFunc_1<GameObject*, bool>
		{
		public:
			bool Apply( const std::shared_ptr<GameObject> &match );
		};

	private:
		class Toggle_SloMoHelper : public Lambda
		{
		private:
			std::shared_ptr<HelpMenu> hm;

		public:
			Toggle_SloMoHelper( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	private:
		class Toggle_SlowMoProxy : public Lambda_1<bool>
		{
		private:
			std::shared_ptr<HelpMenu> hm;

		public:
			Toggle_SlowMoProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply( bool state );
		};

	private:
		class SlowMoProxy : public Lambda
		{
		private:
			std::shared_ptr<HelpMenu> hm;

		public:
			SlowMoProxy( const std::shared_ptr<HelpMenu> &hm );

			void Apply();
		};

	private:
		class CampaignCoinsLambda : public PlayerIntLambda
		{
		public:
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	private:
		int Bank();

		void Buy( int Cost );

		void SetCoins( int Coins );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		HelpMenu();

		static std::shared_ptr<GameObject> MakeListener();

	private:
		int DelayExit;
	public:
		virtual void ReturnToCaller();

		virtual bool MenuReturnToCaller( const std::shared_ptr<Menu> &menu );

	private:
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

	public:
		virtual void OnAdd();

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	private:
		std::shared_ptr<MenuItem> Item_ShowPath, Item_WatchComputer, Item_SlowMo;

		std::shared_ptr<EzText> CoinsText;

		std::shared_ptr<HelpBlurb> Blurb;

		void Initialization();

		void SetPos();

	protected:
		virtual void AddItem( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void ReturnToCaller( bool PlaySound );

		virtual void SlideIn( int Frames );

	protected:
		virtual void SlideOut_RightPanel( const std::shared_ptr<PresetPos> &Preset, int Frames );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HELPMENU
