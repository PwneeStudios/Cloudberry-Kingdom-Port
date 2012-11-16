#ifndef STARTMENU_MW_ARCADE
#define STARTMENU_MW_ARCADE

#include "ArcadeMenu.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include <tchar.h>

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
	class StartMenu_MW_Arcade : public ArcadeMenu
	{
	public:
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_Arcade( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void Go( const std::shared_ptr<MenuItem> &item );

		virtual void OnAdd();

		virtual void Init();

	private:
		void SetPos();
	};
}


#endif	//#ifndef STARTMENU_MW_ARCADE
