#ifndef HEROSELECTOPTIONS
#define HEROSELECTOPTIONS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct HeroSelectOptions : public ArcadeBaseMenu
	{

		virtual ~HeroSelectOptions() { }

		using ArcadeBaseMenu::SlideOut;
		using ArcadeBaseMenu::SlideIn;
		using ArcadeBaseMenu::Call;

		using GUI_Panel::Call;

	
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
