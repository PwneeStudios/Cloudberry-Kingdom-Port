#ifndef STARTMENU_MW
#define STARTMENU_MW

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class TitleGameData_MW;
}

namespace CloudberryKingdom
{
	class Menu;
}

namespace CloudberryKingdom
{
	class QuadClass;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class StartMenu_MW : public StartMenu
	{
	protected:
		virtual void MenuGo_Options( const std::shared_ptr<MenuItem> &item );

		virtual void Exit();

	public:
		virtual void BringNextMenu();

		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

	protected:
		virtual void BringCampaign();

		virtual void BringArcade();

		virtual void BringFreeplay();

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void OnAdd();

		virtual bool MenuReturnToCaller( const std::shared_ptr<Menu> &menu );

		virtual void Init();

	private:
		std::shared_ptr<QuadClass> BackBox;

		void BlackBox();

		void SmallBlackBox();
	};
}


#endif	//#ifndef STARTMENU_MW
