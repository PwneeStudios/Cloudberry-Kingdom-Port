#ifndef SAVEDSEEDSGUI
#define SAVEDSEEDSGUI

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SavedSeedsGUI : public CkBaseMenu
	{
	
		struct PostMakeStandardLoadHelper : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<LevelSeedData> seed;

		
			PostMakeStandardLoadHelper( const boost::shared_ptr<LevelSeedData> &seed );

			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct LoadFromFreeplayMenuHelper : public Lambda
		{
		
			boost::shared_ptr<LevelSeedData> seed;
			std::wstring seedstr;
			boost::shared_ptr<CustomLevel_GUI> simple;

		
			LoadFromFreeplayMenuHelper( const boost::shared_ptr<LevelSeedData> &seed, const std::wstring &seedstr, const boost::shared_ptr<CustomLevel_GUI> &simple );

			void Apply();
		};

	
		struct SaveSeedsDeleteLambda : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<SavedSeedsGUI> gui;
		
			SaveSeedsDeleteLambda( const boost::shared_ptr<SavedSeedsGUI> &gui );

			bool Apply( const boost::shared_ptr<Menu> &menu );
		};

	
		struct ReturnToCallerProxy : public Lambda
		{
		
			boost::shared_ptr<SavedSeedsGUI> ssGui;

		
			ReturnToCallerProxy( const boost::shared_ptr<SavedSeedsGUI> &ssGui );

			void Apply();
		};

	
		struct DoDeletionProxy : public Lambda_1<bool>
		{
		
			boost::shared_ptr<SavedSeedsGUI> ssGui;

		
			DoDeletionProxy( const boost::shared_ptr<SavedSeedsGUI> &ssGui );

			void Apply( const bool &choice );
		};

	
		struct SortProxy : public Lambda
		{
		
			boost::shared_ptr<SavedSeedsGUI> ssGui;

		
			SortProxy( const boost::shared_ptr<SavedSeedsGUI> &ssGui );

			void Apply();
		};

	
		struct SaveSeedsBackLambda : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<SavedSeedsGUI> gui;
		
			SaveSeedsBackLambda( const boost::shared_ptr<SavedSeedsGUI> &gui );

			bool Apply( const boost::shared_ptr<Menu> &menu );
		};

	
		struct SeedItem : public MenuItem
		{
		
			std::wstring Seed;
			bool MarkedForDeletion;

			SeedItem( const std::wstring &name, const std::wstring &seed, const boost::shared_ptr<EzFont> &font );
			boost::shared_ptr<SeedItem> SeedItem_Construct( const std::wstring &name, const std::wstring &seed, const boost::shared_ptr<EzFont> &font );

			void ToggleDeletion();
		
			void InitializeInstanceFields();

		};

	
		struct StartLevelProxy1 : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SavedSeedsGUI> ssGui;
			std::wstring _seed;

		
			StartLevelProxy1( const boost::shared_ptr<SavedSeedsGUI> &ssGui, const std::wstring &_seed );

			void Apply( const boost::shared_ptr<MenuItem> &_menu );
		};

	
		struct OnAddHelper : public LambdaFunc<bool>
		{
		
			boost::shared_ptr<ScrollBar> bar;

		
			OnAddHelper( const boost::shared_ptr<ScrollBar> &bar );

			bool Apply();
		};
	
		SavedSeedsGUI();
		boost::shared_ptr<SavedSeedsGUI> SavedSeedsGUI_Construct();

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		void StartLevel( const std::wstring &seedstr );

		static boost::shared_ptr<CustomLevel_GUI> FreeplayMenu;
	
		static void LoadSeed( const std::wstring &seedstr, const boost::shared_ptr<GUI_Panel> &panel );

	
		static void LoadFromFreeplayMenu( const std::wstring &seedstr, const boost::shared_ptr<CustomLevel_GUI> &simple );

		/// <summary>
		/// Returns true if any item in the menu has been marked for deletion.
		/// </summary>
		int NumSeedsToDelete();

		/// <summary>
		/// Mark the current item to be deleted
		/// </summary>
		bool Delete( const boost::shared_ptr<Menu> &_menu );

		/// <summary>
		/// Delete the items marked for deletion, if the user selected "Yes"
		/// </summary>
		void DoDeletion( bool choice );

		void Sort();

		boost::shared_ptr<PlayerData> player;
	
		virtual void Init();

	
		virtual void MyPhsxStep();

	
		bool Back( const boost::shared_ptr<Menu> &menu );

	
		virtual void OnReturnTo();

	
		void OptionalBackButton();

		void SetPos();

		void MakeList();

#if defined(PC_VERSION)
#endif

		boost::shared_ptr<ScrollBar> bar;
	
		virtual void OnAdd();

	
		void MakeOptions();
	};
}


#endif	//#ifndef SAVEDSEEDSGUI
