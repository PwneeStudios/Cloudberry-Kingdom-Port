#ifndef MENULISTEXPAND
#define MENULISTEXPAND

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuListExpand : public CkBaseMenu
	{
	
		struct OnSelectProxy : public Lambda
		{
		
			std::shared_ptr<MenuListExpand> mle;

		
			OnSelectProxy( const std::shared_ptr<MenuListExpand> &mle );

			void Apply();
		};

	
		struct InitOnBMenuHelper : public LambdaFunc_1<std::shared_ptr<Menu> , bool>
		{
		
			std::shared_ptr<MenuListExpand> mle;

		
			InitOnBMenuHelper( const std::shared_ptr<MenuListExpand> &mle );

			bool Apply( const std::shared_ptr<Menu> &menu );
		};

	
		virtual void ReleaseBody();

	
		std::shared_ptr<MenuList> MyMenuList;
	
		MenuListExpand( int Control, const std::shared_ptr<MenuList> &MyMenuList );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		virtual void AddItem( const std::shared_ptr<MenuItem> &item );

	
		void OnSelect();

		std::shared_ptr<QuadClass> backdrop;
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
