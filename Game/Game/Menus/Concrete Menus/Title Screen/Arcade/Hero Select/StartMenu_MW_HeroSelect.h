#ifndef STARTMENU_MW_HEROSELECT
#define STARTMENU_MW_HEROSELECT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsx;
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
	struct TitleGameData_MW;
}

namespace CloudberryKingdom
{
	struct ArcadeMenu;
}

namespace CloudberryKingdom
{
	struct HeroSelectOptions;
}

namespace CloudberryKingdom
{
	struct ArcadeItem;
}

namespace CloudberryKingdom
{
	struct HeroDoll;
}

namespace CloudberryKingdom
{
	struct HeroItem : public MenuItem
	{
	
		std::shared_ptr<BobPhsx> Hero;
		bool Locked;

		HeroItem( const std::shared_ptr<BobPhsx> &Hero );
	};

	struct StartMenu_MW_HeroSelect : public ArcadeBaseMenu
	{
	
		using GUI_Panel::Call;

	
		struct OnSelectProxy : public Lambda
		{
		
			std::shared_ptr<StartMenu_MW_HeroSelect> smmwhs;

		
			OnSelectProxy( const std::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs );

			void Apply();
		};

	
		struct UpdateScoreProxy : public Lambda
		{
		
			std::shared_ptr<StartMenu_MW_HeroSelect> smmwhs;

		
			UpdateScoreProxy( const std::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs );

			void Apply();
		};

	
		struct StartMenuGoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<StartMenu_MW_HeroSelect> hs;
		
			StartMenuGoLambda( const std::shared_ptr<StartMenu_MW_HeroSelect> &hs );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		std::shared_ptr<TitleGameData_MW> Title;
		std::shared_ptr<ArcadeMenu> Arcade;

	
		std::shared_ptr<HeroSelectOptions> Options;

	
		StartMenu_MW_HeroSelect( const std::shared_ptr<TitleGameData_MW> &Title, const std::shared_ptr<ArcadeMenu> &Arcade, const std::shared_ptr<ArcadeItem> &MyArcadeItem );

		virtual void Release();

	
		void OnSelect();

	
		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		static void SetItemProperties_FadedOnUnselect( const std::shared_ptr<MenuItem> &item );

		virtual void OnAdd();

		std::shared_ptr<HeroDoll> MyHeroDoll;
		virtual void Init();

	
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		std::shared_ptr<EzText> Score, Level_Renamed;

	
		virtual void OnReturnTo();

	
		void UpdateScore();

		void SetPos();

	
		virtual void Go( const std::shared_ptr<MenuItem> &item );
	};
}


#endif	//#ifndef STARTMENU_MW_HEROSELECT
