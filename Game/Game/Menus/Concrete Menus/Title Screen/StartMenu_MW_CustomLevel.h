#ifndef STARTMENU_MW_CUSTOMLEVEL
#define STARTMENU_MW_CUSTOMLEVEL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct StartMenu_MW_CustomLevel : public CustomLevel_GUI
	{
	
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_CustomLevel( const std::shared_ptr<TitleGameData_MW> &Title );
		void StartMenu_MW_CustomLevel_Construct( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void Init();

		virtual void ReturnToCaller();
	};
}


#endif	//#ifndef STARTMENU_MW_CUSTOMLEVEL
