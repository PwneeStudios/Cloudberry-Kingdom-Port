#ifndef STARTMENU_MW_HEROSELECT
#define STARTMENU_MW_HEROSELECT

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Menus/MiniMenu.h"
//#include "Game/Player/PlayerManager.h"
#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
//#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/StartLevelMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/Hero Select/HeroDoll.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/Hero Select/HeroSelectOptions.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct HeroItem : public MenuItem
	{
	
		boost::shared_ptr<BobPhsx> Hero;
        boost::shared_ptr<BobPhsx> RequiredHero;
        int RequiredHeroLevel;

		HeroItem( const std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > &pair );
		boost::shared_ptr<HeroItem> HeroItem_Construct( const std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > &pair );
	};

	struct StartMenu_MW_HeroSelect : public ArcadeBaseMenu
	{

		virtual ~StartMenu_MW_HeroSelect()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartMenu_MW_HeroSelect" );
#endif
		}


		using ArcadeBaseMenu::SlideOut;
		using ArcadeBaseMenu::SlideIn;
		using ArcadeBaseMenu::Call;

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

		bool Lock;
		bool Locked();
		bool Locked(boost::shared_ptr<HeroItem> item);
		bool Invisible(boost::shared_ptr<HeroItem> item);

		virtual void Release();

	
		void OnSelect();

	
		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		static void SetItemProperties_FadedOnUnselect( const boost::shared_ptr<MenuItem> &item );

		virtual void OnAdd();

		boost::shared_ptr<QuadClass> Scroll, ScrollTop, ScrollBottom;
		boost::shared_ptr<HeroDoll> MyHeroDoll;
		virtual void Init();

	
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		boost::shared_ptr<EzText> Score, Level_Renamed;


		void MyPhsxStep();
		virtual void OnReturnTo();

	
		void UpdateScore();

		int NumSelectableItems;

		void Update();

		void SetPos();

	
		virtual void Go( const boost::shared_ptr<MenuItem> &item );
	};
}


#endif	//#ifndef STARTMENU_MW_HEROSELECT
