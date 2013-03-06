#ifndef MINIMENU
#define MINIMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct MiniMenu : public Menu
	{

		virtual ~MiniMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "MiniMenu" );
#endif
		}

	
		int ItemsToShow;
	
		int TopItem;
		const int getBottomItem() const;
		void setBottomItem( const int &value );

	
		MiniMenu();

		virtual void SelectItem( int Index );

		virtual void PhsxStep();

		Vector2 Shift;
		virtual void DrawText( int Layer );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MINIMENU
