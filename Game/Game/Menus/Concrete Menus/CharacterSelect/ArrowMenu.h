#ifndef ARROWMENU
#define ARROWMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class SimpleMenuBase;
}




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
