#ifndef SAVEDSEEDSGUI
#define SAVEDSEEDSGUI

#include <global_header.h>

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class CustomLevel_GUI;
}

namespace CloudberryKingdom
{
	class Menu;
}

namespace CloudberryKingdom
{
	class EzFont;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class ScrollBar;
}

namespace CloudberryKingdom
{
	class GUI_Panel;
}

namespace CloudberryKingdom
{
	class PlayerData;
}



namespace CloudberryKingdom
{
	class SavedSeedsGUI : public CkBaseMenu
	{
	private:
		class PostMakeStandardLoadHelper : public Lambda_1<std::shared_ptr<Level> >
		{
		private:
			std::shared_ptr<LevelSeedData> seed;

		public:
			PostMakeStandardLoadHelper( const std::shared_ptr<LevelSeedData> &seed );

			void Apply( const std::shared_ptr<Level> &level );
		};

	private:
		class LoadFromFreeplayMenuHelper : public Lambda
		{
		private:
			std::shared_ptr<LevelSeedData> seed;
			std::wstring seedstr;
			std::shared_ptr<CustomLevel_GUI> simple;

		public:
			LoadFromFreeplayMenuHelper( const std::shared_ptr<LevelSeedData> &seed, const std::wstring &seedstr, const std::shared_ptr<CustomLevel_GUI> &simple );

			void Apply();
		};

	private:
		class SaveSeedsDeleteLambda : public LambdaFunc_1<Menu*, bool>
		{
		private:
			std::shared_ptr<SavedSeedsGUI> gui;
		public:
			SaveSeedsDeleteLambda( const std::shared_ptr<SavedSeedsGUI> &gui );

			bool Apply( const std::shared_ptr<Menu> &menu );
		};

	private:
		class ReturnToCallerProxy : public Lambda
		{
		private:
			std::shared_ptr<SavedSeedsGUI> ssGui;

		public:
			ReturnToCallerProxy( const std::shared_ptr<SavedSeedsGUI> &ssGui );

			void Apply();
		};

	private:
		class DoDeletionProxy : public Lambda_1<bool>
		{
		private:
			std::shared_ptr<SavedSeedsGUI> ssGui;

		public:
			DoDeletionProxy( const std::shared_ptr<SavedSeedsGUI> &ssGui );

			void Apply( bool choice );
		};

	private:
		class SortProxy : public Lambda
		{
		private:
			std::shared_ptr<SavedSeedsGUI> ssGui;

		public:
			SortProxy( const std::shared_ptr<SavedSeedsGUI> &ssGui );

			void Apply();
		};

	private:
		class SaveSeedsBackLambda : public LambdaFunc_1<Menu*, bool>
		{
		private:
			std::shared_ptr<SavedSeedsGUI> gui;
		public:
			SaveSeedsBackLambda( const std::shared_ptr<SavedSeedsGUI> &gui );

			bool Apply( const std::shared_ptr<Menu> &menu );
		};

	private:
		class SeedItem : public MenuItem
		{
		public:
			std::wstring Seed;
			bool MarkedForDeletion;

			SeedItem( const std::wstring &name, const std::wstring &seed, const std::shared_ptr<EzFont> &font );

			void ToggleDeletion();

		private:
			void InitializeInstanceFields();
		};

	private:
		class StartLevelProxy1 : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<SavedSeedsGUI> ssGui;
			std::wstring _seed;

		public:
			StartLevelProxy1( const std::shared_ptr<SavedSeedsGUI> &ssGui, const std::wstring &_seed );

			void Apply( const std::shared_ptr<MenuItem> &_menu );
		};

	private:
		class OnAddHelper : public LambdaFunc<bool>
		{
		private:
			std::shared_ptr<ScrollBar> bar;

		public:
			OnAddHelper( const std::shared_ptr<ScrollBar> &bar );

			bool Apply();
		};
	public:
		SavedSeedsGUI();

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	private:
		void StartLevel( const std::wstring &seedstr );

		static std::shared_ptr<CustomLevel_GUI> FreeplayMenu;
	public:
		static void LoadSeed( const std::wstring &seedstr, const std::shared_ptr<GUI_Panel> &panel );

	private:
		static void LoadFromFreeplayMenu( const std::wstring &seedstr, const std::shared_ptr<CustomLevel_GUI> &simple );

		/// <summary>
		/// Returns true if any item in the menu has been marked for deletion.
		/// </summary>
		int NumSeedsToDelete();

		/// <summary>
		/// Mark the current item to be deleted
		/// </summary>
		bool Delete( const std::shared_ptr<Menu> &_menu );

		/// <summary>
		/// Delete the items marked for deletion, if the user selected "Yes"
		/// </summary>
		void DoDeletion( bool choice );

		void Sort();

		std::shared_ptr<PlayerData> player;
	public:
		virtual void Init();

	protected:
		virtual void MyPhsxStep();

	private:
		bool Back( const std::shared_ptr<Menu> &menu );

	public:
		virtual void OnReturnTo();

	private:
		void OptionalBackButton();

		void SetPos();

		void MakeList();

#if defined(PC_VERSION)
#endif

		std::shared_ptr<ScrollBar> bar;
	public:
		virtual void OnAdd();

	private:
		void MakeOptions();
	};
}


#endif	//#ifndef SAVEDSEEDSGUI
