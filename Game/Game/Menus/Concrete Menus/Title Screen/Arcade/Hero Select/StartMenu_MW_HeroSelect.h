#ifndef STARTMENU_MW_HEROSELECT
#define STARTMENU_MW_HEROSELECT

#include "../Game/Menus/Menu Components/MenuItem.h"
#include "../Game/Tools/Resources.h"
#include "../Properties/Resources.Designer.h"
#include "../Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Game/Menus/Concrete Menus/CharacterSelect/ColorSelect.h"
#include "../Game/Menus/Menu Components/MenuListExpand.h"
#include "../Core/Lambdas/Lambda_1.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "../Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include <vector>
#include <tchar.h>
#include "stringconverter.h"

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class EzText;
}

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
	class ArcadeMenu;
}

namespace CloudberryKingdom
{
	class HeroSelectOptions;
}

namespace CloudberryKingdom
{
	class ArcadeItem;
}

namespace CloudberryKingdom
{
	class HeroDoll;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class HeroItem : public MenuItem
	{
	public:
		std::shared_ptr<BobPhsx> Hero;
		bool Locked;

		HeroItem( const std::shared_ptr<BobPhsx> &Hero );
	};

	class StartMenu_MW_HeroSelect : public ArcadeBaseMenu
	{
	private:
		class OnSelectProxy : public Lambda
		{
		private:
			std::shared_ptr<StartMenu_MW_HeroSelect> smmwhs;

		public:
			OnSelectProxy( const std::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs );

			void Apply();
		};

	private:
		class UpdateScoreProxy : public Lambda
		{
		private:
			std::shared_ptr<StartMenu_MW_HeroSelect> smmwhs;

		public:
			UpdateScoreProxy( const std::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs );

			void Apply();
		};

	private:
		class StartMenuGoLambda : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<StartMenu_MW_HeroSelect> hs;
		public:
			StartMenuGoLambda( const std::shared_ptr<StartMenu_MW_HeroSelect> &hs );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	public:
		std::shared_ptr<TitleGameData_MW> Title;
		std::shared_ptr<ArcadeMenu> Arcade;

	private:
		std::shared_ptr<HeroSelectOptions> Options;

	public:
		StartMenu_MW_HeroSelect( const std::shared_ptr<TitleGameData_MW> &Title, const std::shared_ptr<ArcadeMenu> &Arcade, const std::shared_ptr<ArcadeItem> &MyArcadeItem );

		virtual void Release();

	private:
		void OnSelect();

	public:
		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		static void SetItemProperties_FadedOnUnselect( const std::shared_ptr<MenuItem> &item );

		virtual void OnAdd();

		std::shared_ptr<HeroDoll> MyHeroDoll;
		virtual void Init();

	private:
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		std::shared_ptr<EzText> Score, Level_Renamed;

	public:
		virtual void OnReturnTo();

	private:
		void UpdateScore();

		void SetPos();

	public:
		virtual void Go( const std::shared_ptr<MenuItem> &item );
	};
}


#endif	//#ifndef STARTMENU_MW_HEROSELECT
