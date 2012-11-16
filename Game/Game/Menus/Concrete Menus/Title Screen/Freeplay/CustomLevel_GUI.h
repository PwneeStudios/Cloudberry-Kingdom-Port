#ifndef CUSTOMLEVEL_GUI
#define CUSTOMLEVEL_GUI

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
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class LengthSlider;
}

namespace CloudberryKingdom
{
	class Menu;
}

namespace CloudberryKingdom
{
	class MenuList;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class TileSet;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class ObjectIcon;
}

namespace CloudberryKingdom
{
	class MenuSliderBase;
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
	class CustomHero_GUI;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class CustomLevel_GUI : public CkBaseMenu
	{
	private:
		class StartLevelFromMenDataStandardLoadProxy : public Lambda_1<Level*>
		{
		private:
			std::shared_ptr<LevelSeedData> data;

		public:
			StartLevelFromMenDataStandardLoadProxy( const std::shared_ptr<LevelSeedData> &data );

			void Apply( const std::shared_ptr<Level> &level );
		};

	private:
		class StartLevelFromMenuDataInitializeHelper : public Lambda_1<PieceSeedData*>
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;

		public:
			StartLevelFromMenuDataInitializeHelper( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply( const std::shared_ptr<PieceSeedData> &piece );
		};

	private:
		class StartLevelEnableLoadProxy : public Lambda_1<Level*>
		{
		private:
			std::shared_ptr<LevelSeedData> data;

		public:
			StartLevelEnableLoadProxy( const std::shared_ptr<LevelSeedData> &data );

			void Apply( const std::shared_ptr<Level> &level );
		};

	private:
		class OnReturnFromLevelProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;

		public:
			OnReturnFromLevelProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	private:
		class InitOnSetValueHelper : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<LengthSlider> length;

		public:
			InitOnSetValueHelper( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	private:
		class InitOnSlideHelper : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<LengthSlider> length;

		public:
			InitOnSlideHelper( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	private:
		class InitOnSlideHelper2 : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<LengthSlider> length;

		public:
			InitOnSlideHelper2( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	private:
		class InitOnSetValueHelper2 : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<LengthSlider> length;

		public:
			InitOnSetValueHelper2( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	private:
		class InitOnAStartHelper : public LambdaFunc_1<Menu*, bool>
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;

		public:
			InitOnAStartHelper( const std::shared_ptr<CustomLevel_GUI> &clGui );

			bool Apply( const std::shared_ptr<Menu> &dummy );
		};

	private:
		class InitOnIndexSelectHelper : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<MenuList> LocationList;

		public:
			InitOnIndexSelectHelper( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<MenuList> &LocationList );

			void Apply();
		};

	private:
		class InitOnIndexSelect : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;
			std::shared_ptr<MenuList> GameList;

		public:
			InitOnIndexSelect( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<MenuList> &GameList );

			void Apply();
		};

	private:
		class DiffList_OnIndexProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;

		public:
			DiffList_OnIndexProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	private:
		class HeroList_OnIndexProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;

		public:
			HeroList_OnIndexProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	private:
		class BringNextProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;

		public:
			BringNextProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	private:
		class BringLoadProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;

		public:
			BringLoadProxy( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	private:
		class BringLoadProxy1 : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<CustomLevel_GUI> clGui;

		public:
			BringLoadProxy1( const std::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	public:
		static std::vector<TileSet*> FreeplayTilesets;
		static std::vector<BobPhsx*> FreeplayHeroes;

		static bool IsMaxLength;
		static int Difficulty;

		/// <summary>
		/// This is the level seed being edited.
		/// </summary>
		std::shared_ptr<LevelSeedData> LevelSeed;
		std::shared_ptr<PieceSeedData> PieceSeed;

		std::shared_ptr<ObjectIcon> HeroIcon, MiniCheckpoint;

	private:
		static Localization::Words CustomHeroString;

	public:
		CustomLevel_GUI();

		void StartLevelFromMenuData();

		void StartLevel( const std::shared_ptr<LevelSeedData> &data );

		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

	private:
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
	public:
		virtual void Init();

	private:
		std::shared_ptr<MenuItem> AddHeroItem( const std::shared_ptr<BobPhsx> &hero );

		void DiffList_OnIndex();

		void StartLevel();

		void HeroList_OnIndex();

		bool IsCustomHero();

	public:
		bool IsCustomDifficulty();

		void SetPos();

	private:
		void SelectUpLevel();

		void SelectDownLevel();

		/// <summary>
		/// The panel that actually starts the level, when it is started.
		/// </summary>
	public:
		std::shared_ptr<GUI_Panel> CallingPanel;

	private:
		void BringNext();

	public:
		virtual void Show();

	private:
		std::shared_ptr<CustomHero_GUI> HeroGui;
		void BringHero();

		void BringUpgrades();

		void BringLoad();

	public:
		virtual void OnReturnTo();

	private:
		int DesiredNumCheckpoints;
		float DesiredLength;
		int DesiredHeroIndex;
	protected:
		virtual void MyDraw();

	public:
		static std::wstring SeedStringToLoad;
		static bool ExitFreeplay;
	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CUSTOMLEVEL_GUI
