#ifndef ARROWMENU
#define ARROWMENU

#include "../Game/Menus/CkBaseMenu.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class SimpleMenuBase;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class ArrowMenu : public CkBaseMenu
	{
	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;

	protected:
		virtual void ReleaseBody();

	public:
		std::shared_ptr<SimpleMenuBase> MySimple;
		ArrowMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent, const std::shared_ptr<SimpleMenuBase> &MySimple );

		virtual void Init();

	protected:
		virtual void MyDraw();

	public:
		virtual void OnAdd();

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef ARROWMENU
