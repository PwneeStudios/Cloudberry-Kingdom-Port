#ifndef MENULIST
#define MENULIST

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class MenuListExpand;
}

namespace CloudberryKingdom
{
	class Lambda_2;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class Lambda;
}

namespace CloudberryKingdom
{
	class Camera;
}




namespace CloudberryKingdom
{
	class MenuList : public MenuItem
	{
	private:
		class ExpandProxy1 : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<MenuList> ml;

		public:
			ExpandProxy1( const std::shared_ptr<MenuList> &ml );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	public:
		virtual std::vector<std::wstring> GetViewables();

		const bool &getExpandOnGo() const;
		void setExpandOnGo( const bool &value );
	private:
		bool _ExpandOnGo;

	public:
		std::shared_ptr<MenuListExpand> MyMenuListExpand;
		Vector2 MyExpandPos;
		std::shared_ptr<Lambda_2<MenuListExpand*, MenuItem*> > AdditionalExpandProcessing;
		void Expand();

		std::vector<MenuItem*> MyList;
		int ListIndex;

	private:
		static const int SelectDelay = 12;
		int DelayCount;

	public:
		std::shared_ptr<QuadClass> RightArrow, LeftArrow;
		std::shared_ptr<QuadClass> RightArrow_Selected, LeftArrow_Selected;

		bool CustomArrow;
		Vector2 LeftArrowOffset, RightArrowOffset;
		//public Vector2 LeftArrow_SelectedOffset, RightArrow_SelectedOffset;

		std::shared_ptr<Lambda> OnIndexSelect, OnConfirmedIndexSelect;

		/// <summary>
		/// Whether to draw the list's arrows when the list isn't currently selected
		/// </summary>
		bool DrawArrowsWhenUnselected;

#if defined(WINDOWS)
		//Vector2 ListPadding = new Vector2(65, 0);
	private:
		Vector2 ListPadding;
		Vector2 TotalPadding;
	public:
		virtual bool HitTest( Vector2 pos, Vector2 padding );
#endif

		virtual void FadeIn();

		virtual void FadeOut();

		MenuList();

	private:
		void InitializeArrows();

	public:
		virtual float Height();

		virtual float Width();

	private:
		std::map<MenuItem*, void*> ObjDict;
	public:
		void AddItem( const std::shared_ptr<MenuItem> &item, const std::shared_ptr<Object> &obj );

		std::shared_ptr<MenuItem> GetListItem();

		/// <summary>
		/// The object associated with the currently selected MenuItem
		/// </summary>
		const std::shared_ptr<Object> &getCurObj() const;

		/// <summary>
		/// When true the list's index will wrap if too large or too small.
		/// Otherwise it will be restricted.
		/// </summary>
		bool DoIndexWrapping;

		const bool &getOnFirstIndex() const;
		const bool &getOnLastIndex() const;

		bool ValidIndex( int index );

		std::shared_ptr<MenuItem> CurMenuItem;
		void SetSelectedItem( const std::shared_ptr<MenuItem> &item );

		virtual void SetIndex( int NewIndex );

	private:
		int LastIncrDir;
		void IncrementIndex( int Increment );

#if defined(WINDOWS)
	public:
		std::shared_ptr<QuadClass> GetSelectedArrow();
#endif

		/// <summary>
		/// When true clicking on the menu list will selected the next item in the list.
		/// </summary>
		bool ClickForNextItem;

	private:
		bool HoldSelected;
	public:
		virtual void PhsxStep( bool Selected );

		bool Center;
		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENULIST
