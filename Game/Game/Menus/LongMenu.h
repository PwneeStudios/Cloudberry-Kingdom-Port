#ifndef LONGMENU
#define LONGMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct LongMenu : public Menu
	{

		virtual ~LongMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "LongMenu" );
#endif
		}

	
		float Offset;
		float OffsetStep;

		LongMenu();

		virtual void SelectItem( int Index );

		float MaxBottomSpace;
		virtual void PhsxStep();

		float Height();

	
		void SuperScroll();

	
		void FastScroll();

		void Scroll();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LONGMENU
