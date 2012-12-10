#ifndef HEROSELECTOPTIONS
#define HEROSELECTOPTIONS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct HeroSelectOptions : public ArcadeBaseMenu
	{
	
		using GUI_Panel::Call;

	
		struct BringLeaderboardProxy : public Lambda
		{
		
			std::shared_ptr<HeroSelectOptions> hso;

		
			BringLeaderboardProxy( const std::shared_ptr<HeroSelectOptions> &hso );

			void Apply();
		};

	
		std::shared_ptr<StartMenu_MW_HeroSelect> HeroSelect;

	
		HeroSelectOptions( const std::shared_ptr<StartMenu_MW_HeroSelect> &HeroSelect );

		virtual void Release();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

	
		void BringLeaderboard();

	
		virtual void MyPhsxStep();

	
		virtual void Init();

	
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		std::shared_ptr<EzText> Score, Level_Renamed;

		void SetPos_Console();

		void SetPos_PC();

	
		virtual void Go( const std::shared_ptr<MenuItem> &item );
	};
}


#endif	//#ifndef HEROSELECTOPTIONS
