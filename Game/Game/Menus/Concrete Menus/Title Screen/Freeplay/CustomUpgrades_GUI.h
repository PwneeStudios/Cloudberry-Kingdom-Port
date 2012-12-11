#ifndef CUSTOMUPGRADES_GUI
#define CUSTOMUPGRADES_GUI

#include <global_header.h>

namespace CloudberryKingdom
{
	struct CustomLevel_GUI;
}

namespace CloudberryKingdom
{
	struct PieceSeedData;
}

namespace CloudberryKingdom
{
	struct MenuSlider;
}

namespace CloudberryKingdom
{
	struct EzText;
}

namespace CloudberryKingdom
{
	struct MenuItem;
}

namespace CloudberryKingdom
{
	struct ObjectIcon;
}




namespace CloudberryKingdom
{

	struct CustomUpgrades_GUI : public CkBaseMenu
	{
	
		struct BlockPieceSeedSetter : public Lambda
		{
		
			std::shared_ptr<CustomUpgrades_GUI> gui;
			Upgrade upgrade;
			std::shared_ptr<MenuSlider> slider;

		
			BlockPieceSeedSetter( const std::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const std::shared_ptr<MenuSlider> &slider );

			void Apply();
		};

	
		struct PieceSeedSetter : public Lambda
		{
		
			std::shared_ptr<CustomUpgrades_GUI> gui;
			Upgrade upgrade;
			std::shared_ptr<MenuSlider> slider;

		
			PieceSeedSetter( const std::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const std::shared_ptr<MenuSlider> &slider );

			void Apply();
		};

	
		struct AddUpgradeAdditionalOnSelect : public Lambda
		{
		
			std::shared_ptr<CustomUpgrades_GUI> cuGui;
			std::shared_ptr<MenuSlider> slider;
			Upgrade upgrade;

		
			AddUpgradeAdditionalOnSelect( const std::shared_ptr<CustomUpgrades_GUI> &cuGui, const std::shared_ptr<MenuSlider> &slider, Upgrade upgrade );

			void Apply();
		};

	
		struct UpgradesSliderLambda : public LambdaFunc<float>
		{
		
			std::shared_ptr<CustomUpgrades_GUI> cu;
			Upgrade upgrade;
		
			UpgradesSliderLambda( const std::shared_ptr<CustomUpgrades_GUI> &cu, Upgrade upgrade );

			float Apply();
		};

	
		struct StartLevelProxy : public Lambda
		{
		
			std::shared_ptr<CustomUpgrades_GUI> cuGui;

		
			StartLevelProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	
		struct ZeroProxy : public Lambda
		{
		
			std::shared_ptr<CustomUpgrades_GUI> cuGui;

		
			ZeroProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	
		struct RandomizeProxy : public Lambda
		{
		
			std::shared_ptr<CustomUpgrades_GUI> cuGui;

		
			RandomizeProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	
		struct GoProxy : public Lambda
		{
		
			std::shared_ptr<CustomUpgrades_GUI> cuGui;

		
			GoProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	
		std::shared_ptr<PieceSeedData> PieceSeed;
		std::shared_ptr<CustomLevel_GUI> CustomLevel;

	
		std::shared_ptr<EzText> TopText;

	
		CustomUpgrades_GUI( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual void OnAdd();

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		std::shared_ptr<ObjectIcon> BigIcon;
	
		void AddUpgrade( Upgrade upgrade );

		void StartLevel();

		void Zero();

		void Randomize();

		float ScaleList;

	
		virtual std::vector<Upgrade> GetUpgradeList();

		virtual void Init();

	
		virtual Localization::Words HeaderText();

	
		void SetPos();

		void MakeMenu();

	
		virtual void Go();

		void StartGame();

	
		void MakeOptions();

		void MakeTopText();

	
		virtual void MyDraw();

	
		void InitializeInstanceFields();
	};

	struct AggressiveUpgrades_GUI : public CustomUpgrades_GUI
	{
	
		AggressiveUpgrades_GUI( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual std::vector<Upgrade> GetUpgradeList();

	
		virtual void Go();

		virtual Localization::Words HeaderText();
	};

	struct PassiveUpgrades_GUI : public CustomUpgrades_GUI
	{
	
		PassiveUpgrades_GUI( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual std::vector<Upgrade> GetUpgradeList();

	
		virtual void Go();

		virtual Localization::Words HeaderText();
	};
}


#endif	//#ifndef CUSTOMUPGRADES_GUI
