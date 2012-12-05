#ifndef STARTMENU
#define STARTMENU

#include <global_header.h>

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
	class GUI_Panel;
}




namespace CloudberryKingdom
{
	class StartMenu : public CkBaseMenu
	{
	public:
		enum Next
		{
			Next_CAMPAIGN,
			Next_ARCADE,
			Next_FREEPLAY
		};
	private:
		class StartMenuLambda_Campaign : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<StartMenu> sm;
		public:
			StartMenuLambda_Campaign( const std::shared_ptr<StartMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class StartMenuLambda_Arcade : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<StartMenu> sm;
		public:
			StartMenuLambda_Arcade( const std::shared_ptr<StartMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class StartMenuLambda_Freeplay : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<StartMenu> sm;
		public:
			StartMenuLambda_Freeplay( const std::shared_ptr<StartMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class CharacterSelectProxy : public Lambda
		{
		private:
			std::shared_ptr<StartMenu> startMenu;

		public:
			CharacterSelectProxy( const std::shared_ptr<StartMenu> &startMenu );

			void Apply();
		};

	private:
		class MenuGo_ScreenSaverHelper : public Lambda
		{
		private:
			std::shared_ptr<StartMenu> sm;

		public:
			MenuGo_ScreenSaverHelper( const std::shared_ptr<StartMenu> &sm );

			void Apply();
		};

	private:
		class StartMenuLambda_Controls : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<StartMenu> sm;
		public:
			StartMenuLambda_Controls( const std::shared_ptr<StartMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class StartMenuLambda_Options : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<StartMenu> sm;
		public:
			StartMenuLambda_Options( const std::shared_ptr<StartMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class StartMenuLambda_Exit : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<StartMenu> sm;
		public:
			StartMenuLambda_Exit( const std::shared_ptr<StartMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class StartMenuExitLambda : public LambdaFunc_1<std::shared_ptr<Menu> , bool>
		{
		private:
			std::shared_ptr<StartMenu> sm;
		public:
			StartMenuExitLambda( const std::shared_ptr<StartMenu> &sm );

			bool Apply( const std::shared_ptr<Menu> &menu );
		};

	private:
		class DoneWithCharSelectProxy : public Lambda
		{
		private:
			std::shared_ptr<StartMenu> sm;

		public:
			DoneWithCharSelectProxy( const std::shared_ptr<StartMenu> &sm );

			void Apply();
		};

	private:
		class BringNextMenuLambda : public Lambda
		{
		private:
			std::shared_ptr<StartMenu> sm;

		public:
			BringNextMenuLambda( const std::shared_ptr<StartMenu> &sm );

			void Apply();
		};

	public:
		virtual void Hide( const std::shared_ptr<PresetPos> &pos, int frames );

		Next MyNextMenu;

	protected:
		virtual void MenuGo_Campaign( const std::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Arcade( const std::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Freeplay( const std::shared_ptr<MenuItem> &item );

		/// <summary>
		/// When true the user can not selected back.
		/// </summary>
		bool NoBack;

		virtual void BringCharacterSelect();

	public:
		virtual void Show();

		virtual void ReturnToCaller();

	protected:
		virtual void CharacterSelect();

		virtual void MenuGo_ScreenSaver( const std::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Controls( const std::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Stats( const std::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Options( const std::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Exit( const std::shared_ptr<MenuItem> &item );

		virtual void Exit();

	public:
		StartMenu();

		///// <summary>
		///// When true the menu slides in, rather than bubbles in, when a child menu returns control to it
		///// </summary>
		//bool SlideOnReturn = false;

		virtual void SlideIn( int Frames );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		static void SetText_Green( const std::shared_ptr<EzText> &text, bool outline );

		static void SetSelectedText_Green( const std::shared_ptr<EzText> &text, bool outline );

		static void SetItemProperties_Green( const std::shared_ptr<MenuItem> &item, bool outline );

		static void SetItemProperties_Red( const std::shared_ptr<MenuItem> &item );

		virtual void OnAdd();

		virtual void Init();

	private:
		static void GrayItem( const std::shared_ptr<MenuItem> &item );

		void MakeMenu();

		void BlackBox();

		void Centered();

		void Forest();

		void Title3();

	protected:
		virtual void SetChildControl( const std::shared_ptr<GUI_Panel> &child );

		virtual void MyPhsxStep();

	private:
		void DoneWithCharSelect();

	public:
		virtual void BringNextMenu();

	protected:
		virtual void BringCampaign();

		virtual void BringArcade();

		virtual void BringFreeplay();

	public:
		virtual void OnReturnTo();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STARTMENU
