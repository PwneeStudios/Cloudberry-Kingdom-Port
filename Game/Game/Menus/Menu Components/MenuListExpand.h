#ifndef MENULISTEXPAND
#define MENULISTEXPAND

#include "../Game/Menus/CkBaseMenu.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Game/Menus/Concrete Menus/CharacterSelect/ColorSelect.h"
#include "../Game/Menus/Concrete Menus/Title Screen/Arcade/Hero Select/StartMenu_MW_HeroSelect.h"
#include "../Core/Lambdas/LambdaFunc_1.h"
#include <vector>
#include <cmath>
#include <tchar.h>

namespace CloudberryKingdom
{
	class Menu;
}

namespace CloudberryKingdom
{
	class MenuList;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class QuadClass;
}


using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class MenuListExpand : public CkBaseMenu
	{
	private:
		class OnSelectProxy : public Lambda
		{
		private:
			std::shared_ptr<MenuListExpand> mle;

		public:
			OnSelectProxy( const std::shared_ptr<MenuListExpand> &mle );

			void Apply();
		};

	private:
		class InitOnBMenuHelper : public LambdaFunc_1<Menu*, bool>
		{
		private:
			std::shared_ptr<MenuListExpand> mle;

		public:
			InitOnBMenuHelper( const std::shared_ptr<MenuListExpand> &mle );

			bool Apply( const std::shared_ptr<Menu> &menu );
		};

	protected:
		virtual void ReleaseBody();

	private:
		std::shared_ptr<MenuList> MyMenuList;
	public:
		MenuListExpand( int Control, const std::shared_ptr<MenuList> &MyMenuList );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		virtual void AddItem( const std::shared_ptr<MenuItem> &item );

	private:
		void OnSelect();

		std::shared_ptr<QuadClass> backdrop;
		Vector2 DefaultBackdropSize;
	public:
		virtual void Init();

		virtual void OnAdd();

	private:
		void Back();

	protected:
		virtual void MyDraw();

	private:
		int Count;
	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENULISTEXPAND
