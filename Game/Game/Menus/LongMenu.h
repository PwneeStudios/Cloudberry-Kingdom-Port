#ifndef LONGMENU
#define LONGMENU

#include "Menu.h"
#include <vector>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class LongMenu : public Menu
	{
	public:
		float Offset;
		float OffsetStep;

		LongMenu();

		virtual void SelectItem( int Index );

		float MaxBottomSpace;
		virtual void PhsxStep();

		float Height();

	private:
		void SuperScroll();

	public:
		void FastScroll();

		void Scroll();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LONGMENU
