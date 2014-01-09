#ifndef MENULISTEXPAND
#define MENULISTEXPAND

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Tools/ColorHelper.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Menus/Menu Components/MenuList.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct MenuListExpand : public CkBaseMenu
	{

		virtual ~MenuListExpand()
		{
#ifdef BOOST_BIN
			OnDestructor( "MenuListExpand" );
#endif
		}

	
		struct OnSelectProxy : public Lambda
		{
		
			boost::shared_ptr<MenuListExpand> mle;

			OnSelectProxy( const boost::shared_ptr<MenuListExpand> &mle );

			void Apply();

		};

	
		struct InitOnBMenuHelper : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<MenuListExpand> mle;

		
			InitOnBMenuHelper( const boost::shared_ptr<MenuListExpand> &mle );

			bool Apply( const boost::shared_ptr<Menu> &menu );
		};

	
		virtual void ReleaseBody();

	
		boost::shared_ptr<MenuList> MyMenuList;
	
		MenuListExpand( int Control, const boost::shared_ptr<MenuList> &MyMenuList );
		boost::shared_ptr<MenuListExpand> MenuListExpand_Construct( int Control, const boost::shared_ptr<MenuList> &MyMenuList );
	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

		virtual void AddItem( const boost::shared_ptr<MenuItem> &item );

	
		void OnSelect();

		boost::shared_ptr<QuadClass> backdrop;
		Vector2 DefaultBackdropSize;
	
		virtual void Init();

		virtual void OnAdd();

	
		void Back();

	
		virtual void MyDraw();

	
		int Count;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENULISTEXPAND
