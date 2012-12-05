#ifndef MENULISTEXPAND
#define MENULISTEXPAND

#include <global_header.h>

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
		class InitOnBMenuHelper : public LambdaFunc_1<std::shared_ptr<Menu> , bool>
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
