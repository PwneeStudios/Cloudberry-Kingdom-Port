#ifndef STARTMENU_MW_ARCADE
#define STARTMENU_MW_ARCADE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct StartMenu_MW_Arcade : public ArcadeMenu
	{
	
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_Arcade( const std::shared_ptr<TitleGameData_MW> &Title );
		void StartMenu_MW_Arcade_Construct( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void Go( const std::shared_ptr<MenuItem> &item );

		virtual void OnAdd();

		virtual void Init();

	
		void SetPos();
	};
}


#endif	//#ifndef STARTMENU_MW_ARCADE
