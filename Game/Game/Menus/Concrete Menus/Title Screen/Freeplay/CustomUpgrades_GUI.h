#ifndef CUSTOMUPGRADES_GUI
#define CUSTOMUPGRADES_GUI

#include <global_header.h>

namespace CloudberryKingdom
{

	struct CustomUpgrades_GUI : public CkBaseMenu
	{
	
		virtual ~CustomUpgrades_GUI()
		{
#ifdef BOOST_BIN
			OnDestructor( "CustomUpgrades_GUI" );
#endif
		}


		struct BlockPieceSeedSetter : public Lambda
		{
		
			boost::shared_ptr<CustomUpgrades_GUI> gui;
			Upgrade upgrade;
			boost::shared_ptr<MenuSlider> slider;

		
			BlockPieceSeedSetter( const boost::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const boost::shared_ptr<MenuSlider> &slider );

			void Apply();
		};

	
		struct PieceSeedSetter : public Lambda
		{
		
			boost::shared_ptr<CustomUpgrades_GUI> gui;
			Upgrade upgrade;
			boost::shared_ptr<MenuSlider> slider;

		
			PieceSeedSetter( const boost::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const boost::shared_ptr<MenuSlider> &slider );

			void Apply();
		};

	
		struct AddUpgradeAdditionalOnSelect : public Lambda
		{
		
			boost::shared_ptr<CustomUpgrades_GUI> cuGui;
			boost::shared_ptr<MenuSlider> slider;
			Upgrade upgrade;

		
			AddUpgradeAdditionalOnSelect( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui, const boost::shared_ptr<MenuSlider> &slider, Upgrade upgrade );

			void Apply();
		};

	
		struct UpgradesSliderLambda : public LambdaFunc<float>
		{
		
			boost::shared_ptr<CustomUpgrades_GUI> cu;
			Upgrade upgrade;
		
			UpgradesSliderLambda( const boost::shared_ptr<CustomUpgrades_GUI> &cu, Upgrade upgrade );

			float Apply();
		};

	
		struct StartLevelProxy : public Lambda
		{
		
			boost::shared_ptr<CustomUpgrades_GUI> cuGui;

		
			StartLevelProxy( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	
		struct ZeroProxy : public Lambda
		{
		
			boost::shared_ptr<CustomUpgrades_GUI> cuGui;

		
			ZeroProxy( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	
		struct RandomizeProxy : public Lambda
		{
		
			boost::shared_ptr<CustomUpgrades_GUI> cuGui;

		
			RandomizeProxy( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	
		struct GoProxy : public Lambda
		{
		
			boost::shared_ptr<CustomUpgrades_GUI> cuGui;

		
			GoProxy( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui );

			void Apply();
		};

	
		boost::shared_ptr<PieceSeedData> PieceSeed;
		boost::shared_ptr<CustomLevel_GUI> CustomLevel;

	
		boost::shared_ptr<EzText> TopText;

	
		CustomUpgrades_GUI( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel );
		boost::shared_ptr<CustomUpgrades_GUI> CustomUpgrades_GUI_Construct( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual void OnAdd();

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		boost::shared_ptr<ObjectIcon> BigIcon;
	
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
	
		virtual ~AggressiveUpgrades_GUI()
		{
#ifdef BOOST_BIN
			OnDestructor( "AggressiveUpgrades_GUI" );
#endif
		}


		AggressiveUpgrades_GUI( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel );
		boost::shared_ptr<AggressiveUpgrades_GUI> AggressiveUpgrades_GUI_Construct( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual std::vector<Upgrade> GetUpgradeList();

	
		virtual void Go();

		virtual Localization::Words HeaderText();
	};

	struct PassiveUpgrades_GUI : public CustomUpgrades_GUI
	{
	
		virtual ~PassiveUpgrades_GUI()
		{
#ifdef BOOST_BIN
			OnDestructor( "PassiveUpgrades_GUI" );
#endif
		}


		PassiveUpgrades_GUI( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel );
		boost::shared_ptr<PassiveUpgrades_GUI> PassiveUpgrades_GUI_Construct( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual std::vector<Upgrade> GetUpgradeList();

	
		virtual void Go();

		virtual Localization::Words HeaderText();
	};
}


#endif	//#ifndef CUSTOMUPGRADES_GUI
