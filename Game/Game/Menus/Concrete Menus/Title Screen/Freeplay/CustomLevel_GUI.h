#ifndef CUSTOMLEVEL_GUI
#define CUSTOMLEVEL_GUI

#include <global_header.h>

namespace CloudberryKingdom
{
	struct CustomLevel_GUI : public CkBaseMenu
	{

		static void InitializeStatics();

	
		using GUI_Panel::SlideOut;
		using GUI_Panel::SlideIn;

	
		struct StartLevelFromMenDataStandardLoadProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			std::shared_ptr<LevelSeedData> data;

		
			StartLevelFromMenDataStandardLoadProxy( const std::shared_ptr<LevelSeedData> &data );

			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct StartLevelFromMenuDataInitializeHelper : public Lambda_1<std::shared_ptr<PieceSeedData> >
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;

		
			StartLevelFromMenuDataInitializeHelper( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply( const std::shared_ptr<PieceSeedData> &piece );
		};

	
		struct StartLevelEnableLoadProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			std::shared_ptr<LevelSeedData> data;

		
			StartLevelEnableLoadProxy( const std::shared_ptr<LevelSeedData> &data );

			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct OnReturnFromLevelProxy : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;

		
			OnReturnFromLevelProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct InitOnSetValueHelper : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<LengthSlider> length;

		
			InitOnSetValueHelper( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	
		struct InitOnSlideHelper : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<LengthSlider> length;

		
			InitOnSlideHelper( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	
		struct InitOnSlideHelper2 : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<LengthSlider> length;

		
			InitOnSlideHelper2( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	
		struct InitOnSetValueHelper2 : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<LengthSlider> length;

		
			InitOnSetValueHelper2( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	
		struct InitOnAStartHelper : public LambdaFunc_1<std::shared_ptr<Menu> , bool>
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;

		
			InitOnAStartHelper( const std::shared_ptr<CustomLevel_GUI> &clGui );

			bool Apply( const std::shared_ptr<Menu> &dummy );
		};

	
		struct InitOnIndexSelectHelper : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<MenuList> LocationList;

		
			InitOnIndexSelectHelper( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<MenuList> &LocationList );

			void Apply();
		};

	
		struct InitOnIndexSelect : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<MenuList> GameList;

		
			InitOnIndexSelect( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<MenuList> &GameList );

			void Apply();
		};

	
		struct DiffList_OnIndexProxy : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;

		
			DiffList_OnIndexProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct HeroList_OnIndexProxy : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;

		
			HeroList_OnIndexProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct BringNextProxy : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;

		
			BringNextProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct BringLoadProxy : public Lambda
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;

		
			BringLoadProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct BringLoadProxy1 : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<CustomLevel_GUI> clGui;

		
			BringLoadProxy1( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	
		static std::vector<std::shared_ptr<TileSet> > FreeplayTilesets;
		static std::vector<std::shared_ptr<BobPhsx> > FreeplayHeroes;

		static bool IsMaxLength;
		static int Difficulty;

		/// <summary>
		/// This is the level seed being edited.
		/// </summary>
		std::shared_ptr<LevelSeedData> LevelSeed;
		std::shared_ptr<PieceSeedData> PieceSeed;

		std::shared_ptr<ObjectIcon> HeroIcon, MiniCheckpoint;

	
		static Localization::Words CustomHeroString;

	
		CustomLevel_GUI();
		std::shared_ptr<CustomLevel_GUI> CustomLevel_GUI_Construct();

		void StartLevelFromMenuData();

		void StartLevel( const std::shared_ptr<LevelSeedData> &data );

		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		void OnReturnFromLevel();

		void AnyHero();

		void UpHero_ModShown();

		void UpHero_NoSpaceship();

		void ShowHeros( bool Show );

		float HoldNumCheckpoints;
		int HoldDesiredNumCheckpoints;
		void ShowCheckpoints( bool Show );

		bool HasWall;
		void SelectNormal();

		void SelectBuild();

		void SelectBungee();

		void SelectSurvival();

		bool LeftJustify;
		float LeftJustifyAddX;

		//static Vector2 RightPanelCenter = new Vector2(-410, 75);
		static Vector2 RightPanelCenter;
		std::shared_ptr<LengthSlider> length;
		std::shared_ptr<MenuSliderBase> checkpoints;
		std::shared_ptr<MenuItem> Start;
		std::shared_ptr<MenuList> HeroList, DiffList;
		std::shared_ptr<EzText> HeroText, CheckpointsText;
	
		virtual void Init();

	
		std::shared_ptr<MenuItem> AddHeroItem( const std::shared_ptr<BobPhsx> &hero );

		void DiffList_OnIndex();

		void StartLevel();

		void HeroList_OnIndex();

		bool IsCustomHero();

	
		bool IsCustomDifficulty();

		void SetPos();

	
		void SelectUpLevel();

		void SelectDownLevel();

		/// <summary>
		/// The panel that actually starts the level, when it is started.
		/// </summary>
	
		std::shared_ptr<GUI_Panel> CallingPanel;

	
		void BringNext();

	
		virtual void Show();

	
		std::shared_ptr<CustomHero_GUI> HeroGui;
		void BringHero();

		void BringUpgrades();

		void BringLoad();

	
		virtual void OnReturnTo();

	
		int DesiredNumCheckpoints;
		float DesiredLength;
		int DesiredHeroIndex;
	
		virtual void MyDraw();

	
		static std::wstring SeedStringToLoad;
		static bool ExitFreeplay;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CUSTOMLEVEL_GUI
