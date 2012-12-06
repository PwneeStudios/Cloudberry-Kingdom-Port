#ifndef STARTMENU_MW_CUSTOMLEVEL
#define STARTMENU_MW_CUSTOMLEVEL

#include <global_header.h>

namespace CloudberryKingdom
{
	class TitleGameData_MW;
}

namespace CloudberryKingdom
{
	class MenuItem;
}




namespace CloudberryKingdom
{
	class StartMenu_MW_CustomLevel : public CustomLevel_GUI
	{
	public:
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_CustomLevel( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void Init();

		virtual void ReturnToCaller();
	};
}


#endif	//#ifndef STARTMENU_MW_CUSTOMLEVEL
