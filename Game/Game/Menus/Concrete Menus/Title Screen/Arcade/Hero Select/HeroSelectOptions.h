#ifndef HEROSELECTOPTIONS
#define HEROSELECTOPTIONS

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Player/LeaderboardView.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreDatabase.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreEntry.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/StartLevelMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/Hero Select/StartMenu_MW_HeroSelect.h"
//#include "Game/Objects/Game Objects/GameObjects/End/HighScorePanel.h"


namespace CloudberryKingdom
{
	struct HeroSelectOptions : public ArcadeBaseMenu
	{

		virtual ~HeroSelectOptions()
		{
#ifdef BOOST_BIN
			OnDestructor( "HeroSelectOptions" );
#endif
		}


		using ArcadeBaseMenu::SlideOut;
		using ArcadeBaseMenu::SlideIn;
		using ArcadeBaseMenu::Call;

	
		struct BringLeaderboardProxy : public Lambda
		{
		
			boost::shared_ptr<HeroSelectOptions> hso;

		
			BringLeaderboardProxy( const boost::shared_ptr<HeroSelectOptions> &hso );

			void Apply();
		};

	
		boost::shared_ptr<StartMenu_MW_HeroSelect> HeroSelect;

	
		HeroSelectOptions( const boost::shared_ptr<StartMenu_MW_HeroSelect> &HeroSelect );
		boost::shared_ptr<HeroSelectOptions> HeroSelectOptions_Construct( const boost::shared_ptr<StartMenu_MW_HeroSelect> &HeroSelect );

		virtual void Release();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

	
		void BringLeaderboard();

	
		virtual void MyPhsxStep();

	
		virtual void Init();

	
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		boost::shared_ptr<EzText> Score, Level_Renamed;

		void SetPos_Console();

		void SetPos_PC();

	
		virtual void Go( const boost::shared_ptr<MenuItem> &item );
	};
}


#endif	//#ifndef HEROSELECTOPTIONS
