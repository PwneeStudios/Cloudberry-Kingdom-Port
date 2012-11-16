#ifndef STARTMENU_MW_CUSTOMLEVEL
#define STARTMENU_MW_CUSTOMLEVEL

#include "Freeplay/CustomLevel_GUI.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Panel.h"

namespace CloudberryKingdom
{
	class TitleGameData_MW;
}

namespace CloudberryKingdom
{
	class MenuItem;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class StartMenu_MW_CustomLevel : public CustomLevel_GUI
	{
	public:
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_CustomLevel( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void Init();

		virtual void ReturnToCaller();
	};
}


#endif	//#ifndef STARTMENU_MW_CUSTOMLEVEL
