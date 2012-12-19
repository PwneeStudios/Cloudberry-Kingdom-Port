#ifndef STARTMENU_MW_HEROSELECT
#define STARTMENU_MW_HEROSELECT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct HeroItem : public MenuItem
	{
	
		boost::shared_ptr<BobPhsx> Hero;
		bool Locked;

		HeroItem( const boost::shared_ptr<BobPhsx> &Hero );
	};

	struct StartMenu_MW_HeroSelect : public ArcadeBaseMenu
	{

		using ArcadeBaseMenu::SlideOut;
		using ArcadeBaseMenu::SlideIn;
		using ArcadeBaseMenu::Call;

		using GUI_Panel::Call;
	
		struct OnSelectProxy : public Lambda
		{
		
			boost::shared_ptr<StartMenu_MW_HeroSelect> smmwhs;

		
			OnSelectProxy( const boost::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs );

			void Apply();
		};

	
		struct UpdateScoreProxy : public Lambda
		{
		
			boost::shared_ptr<StartMenu_MW_HeroSelect> smmwhs;

		
			UpdateScoreProxy( const boost::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs );

			void Apply();
		};

	
		struct StartMenuGoLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartMenu_MW_HeroSelect> hs;
		
			StartMenuGoLambda( const boost::shared_ptr<StartMenu_MW_HeroSelect> &hs );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		boost::shared_ptr<TitleGameData_MW> Title;
		boost::shared_ptr<ArcadeMenu> Arcade;

	
		boost::shared_ptr<HeroSelectOptions> Options;

	
		StartMenu_MW_HeroSelect( const boost::shared_ptr<TitleGameData_MW> &Title, const boost::shared_ptr<ArcadeMenu> &Arcade, const boost::shared_ptr<ArcadeItem> &MyArcadeItem );
		boost::shared_ptr<StartMenu_MW_HeroSelect> StartMenu_MW_HeroSelect_Construct( const boost::shared_ptr<TitleGameData_MW> &Title, const boost::shared_ptr<ArcadeMenu> &Arcade, const boost::shared_ptr<ArcadeItem> &MyArcadeItem );

		virtual void Release();

	
		void OnSelect();

	
		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		static void SetItemProperties_FadedOnUnselect( const boost::shared_ptr<MenuItem> &item );

		virtual void OnAdd();

		boost::shared_ptr<HeroDoll> MyHeroDoll;
		virtual void Init();

	
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		boost::shared_ptr<EzText> Score, Level_Renamed;

	
		virtual void OnReturnTo();

	
		void UpdateScore();

		void SetPos();

	
		virtual void Go( const boost::shared_ptr<MenuItem> &item );
	};
}


#endif	//#ifndef STARTMENU_MW_HEROSELECT
