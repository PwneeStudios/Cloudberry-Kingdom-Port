#ifndef CUSTOMUPGRADES_GUI
#define CUSTOMUPGRADES_GUI

#include "../Game/Objects/AutoGen.h"
#include "../Game/Tools/Globals.h"
#include "../Game/Localization.h"
#include "../Game/Menus/CkBaseMenu.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Core/Lambdas/LambdaFunc.h"
#include "CustomHero_GUI.h"
#include "../Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
#include "../Game/Menus/Concrete Menus/CharacterSelect/CustomizeMenu.h"
#include "../Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
#include <vector>
#include <cmath>
#include <tchar.h>

namespace CloudberryKingdom
{
	class CustomLevel_GUI;
}

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class MenuSlider;
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
	class ObjectIcon;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class AggressiveUpgrades_GUI : public CustomUpgrades_GUI
	{
	public:
		AggressiveUpgrades_GUI( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual std::vector<Upgrade> GetUpgradeList();

	protected:
		virtual void Go();

		virtual Localization::Words HeaderText();
	};

	class PassiveUpgrades_GUI : public CustomUpgrades_GUI
	{
	public:
		PassiveUpgrades_GUI( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual std::vector<Upgrade> GetUpgradeList();

	protected:
		virtual void Go();

		virtual Localization::Words HeaderText();
	};

	class CustomUpgrades_GUI : public CkBaseMenu
	{
	private:
		class BlockPieceSeedSetter : public Lambda
		{
		private:
			std::shared_ptr<CustomUpgrades_GUI> gui;
			Upgrade upgrade;
			std::shared_ptr<MenuSlider> slider;

		public:
			BlockPieceSeedSetter( const std::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const std::shared_ptr<MenuSlider> &slider );

			void Apply();
		};

	private:
		class PieceSeedSetter : public Lambda
		{
		private:
			std::shared_ptr<CustomUpgrades_GUI> gui;
			Upgrade upgrade;
			std::shared_ptr<MenuSlider> slider;

		public:
			PieceSeedSetter( const std::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const std::shared_ptr<MenuSlider> &slider );

			void Apply();
		};

	private:
		class AddUpgradeAdditionalOnSelect : public Lambda
		{
		private:
			std::shared_ptr<CustomUpgrades_GUI> cuGui;
			std::shared_ptr<MenuSlider> slider;
			Upgrade upgrade;

		public:
			AddUpgradeAdditionalOnSelect( const std::shared_ptr<CustomUpgrades_GUI> &cuGui, const std::shared_ptr<MenuSlider> &slider, Upgrade upgrade );

			void Apply();
		};

	private:
		class UpgradesSliderLambda : public LambdaFunc<float>
		{
		private:
			std::shared_ptr<CustomUpgrades_GUI> cu;
			Upgrade upgrade;
		public:
			UpgradesSliderLambda( const std::shared_ptr<CustomUpgrades_GUI> &cu, Upgrade upgrade );

			float Apply();
		};

	private:
		class StartLevelProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomUpgrades_GUI> cuGui;

		public:
			StartLevelProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	private:
		class ZeroProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomUpgrades_GUI> cuGui;

		public:
			ZeroProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	private:
		class RandomizeProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomUpgrades_GUI> cuGui;

		public:
			RandomizeProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	private:
		class GoProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomUpgrades_GUI> cuGui;

		public:
			GoProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	protected:
		std::shared_ptr<PieceSeedData> PieceSeed;
		std::shared_ptr<CustomLevel_GUI> CustomLevel;

	private:
		std::shared_ptr<EzText> TopText;

	public:
		CustomUpgrades_GUI( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual void OnAdd();

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		std::shared_ptr<ObjectIcon> BigIcon;
	private:
		void AddUpgrade( Upgrade upgrade );

		void StartLevel();

		void Zero();

		void Randomize();

		float ScaleList;

	public:
		virtual std::vector<Upgrade> GetUpgradeList();

		virtual void Init();

	protected:
		virtual Localization::Words HeaderText();

	private:
		void SetPos();

		void MakeMenu();

	protected:
		virtual void Go();

		void StartGame();

	private:
		void MakeOptions();

		void MakeTopText();

	protected:
		virtual void MyDraw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CUSTOMUPGRADES_GUI
