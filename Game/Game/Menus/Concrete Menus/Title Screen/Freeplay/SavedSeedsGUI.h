#ifndef SAVEDSEEDSGUI
#define SAVEDSEEDSGUI

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SavedSeedsGUI : public CkBaseMenu
	{
	
		struct PostMakeStandardLoadHelper : public Lambda_1<std::shared_ptr<Level> >
		{
		
			std::shared_ptr<LevelSeedData> seed;

		
			PostMakeStandardLoadHelper( const std::shared_ptr<LevelSeedData> &seed );

			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct LoadFromFreeplayMenuHelper : public Lambda
		{
		
			std::shared_ptr<LevelSeedData> seed;
			std::wstring seedstr;
			std::shared_ptr<CustomLevel_GUI> simple;

		
			LoadFromFreeplayMenuHelper( const std::shared_ptr<LevelSeedData> &seed, const std::wstring &seedstr, const std::shared_ptr<CustomLevel_GUI> &simple );

			void Apply();
		};

	
		struct SaveSeedsDeleteLambda : public LambdaFunc_1<std::shared_ptr<Menu> , bool>
		{
		
			std::shared_ptr<SavedSeedsGUI> gui;
		
			SaveSeedsDeleteLambda( const std::shared_ptr<SavedSeedsGUI> &gui );

			bool Apply( const std::shared_ptr<Menu> &menu );
		};

	
		struct ReturnToCallerProxy : public Lambda
		{
		
			std::shared_ptr<SavedSeedsGUI> ssGui;

		
			ReturnToCallerProxy( const std::shared_ptr<SavedSeedsGUI> &ssGui );

			void Apply();
		};

	
		struct DoDeletionProxy : public Lambda_1<bool>
		{
		
			std::shared_ptr<SavedSeedsGUI> ssGui;

		
			DoDeletionProxy( const std::shared_ptr<SavedSeedsGUI> &ssGui );

			void Apply( const bool &choice );
		};

	
		struct SortProxy : public Lambda
		{
		
			std::shared_ptr<SavedSeedsGUI> ssGui;

		
			SortProxy( const std::shared_ptr<SavedSeedsGUI> &ssGui );

			void Apply();
		};

	
		struct SaveSeedsBackLambda : public LambdaFunc_1<std::shared_ptr<Menu> , bool>
		{
		
			std::shared_ptr<SavedSeedsGUI> gui;
		
			SaveSeedsBackLambda( const std::shared_ptr<SavedSeedsGUI> &gui );

			bool Apply( const std::shared_ptr<Menu> &menu );
		};

	
		struct SeedItem : public MenuItem
		{
		
			std::wstring Seed;
			bool MarkedForDeletion;

			SeedItem( const std::wstring &name, const std::wstring &seed, const std::shared_ptr<EzFont> &font );

			void ToggleDeletion();

		
			void InitializeInstanceFields();
		};

	
		struct StartLevelProxy1 : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<SavedSeedsGUI> ssGui;
			std::wstring _seed;

		
			StartLevelProxy1( const std::shared_ptr<SavedSeedsGUI> &ssGui, const std::wstring &_seed );

			void Apply( const std::shared_ptr<MenuItem> &_menu );
		};

	
		struct OnAddHelper : public LambdaFunc<bool>
		{
		
			std::shared_ptr<ScrollBar> bar;

		
			OnAddHelper( const std::shared_ptr<ScrollBar> &bar );

			bool Apply();
		};
	
		SavedSeedsGUI();
		void SavedSeedsGUI_Construct();

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		void StartLevel( const std::wstring &seedstr );

		static std::shared_ptr<CustomLevel_GUI> FreeplayMenu;
	
		static void LoadSeed( const std::wstring &seedstr, const std::shared_ptr<GUI_Panel> &panel );

	
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
	
		virtual void Init();

	
		virtual void MyPhsxStep();

	
		bool Back( const std::shared_ptr<Menu> &menu );

	
		virtual void OnReturnTo();

	
		void OptionalBackButton();

		void SetPos();

		void MakeList();

#if defined(PC_VERSION)
#endif

		std::shared_ptr<ScrollBar> bar;
	
		virtual void OnAdd();

	
		void MakeOptions();
	};
}


#endif	//#ifndef SAVEDSEEDSGUI
