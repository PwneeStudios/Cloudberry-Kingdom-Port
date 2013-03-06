#ifndef MENULIST
#define MENULIST

#include <global_header.h>

namespace CloudberryKingdom
{

	struct MenuList : public MenuItem
	{
		
		virtual ~MenuList()
		{
#ifdef BOOST_BIN
			OnDestructor( "MenuList" );
#endif
		}


		struct ExpandProxy1 : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<MenuList> ml;

		
			ExpandProxy1( const boost::shared_ptr<MenuList> &ml );

			void Apply( const boost::shared_ptr<MenuItem> &dummy );
		};

	
		virtual std::vector<std::wstring> GetViewables();

		const bool &getExpandOnGo() const;
		void setExpandOnGo( const bool &value );
	
		bool _ExpandOnGo;

	
		boost::shared_ptr<MenuListExpand> MyMenuListExpand;
		Vector2 MyExpandPos;
		boost::shared_ptr<Lambda_2<boost::shared_ptr<MenuListExpand>, boost::shared_ptr<MenuItem> > > AdditionalExpandProcessing;
		void Expand();

        void Release();

		std::vector<boost::shared_ptr<MenuItem> > MyList;
		int ListIndex;

	
		static const int SelectDelay = 12;
		int DelayCount;

	
		boost::shared_ptr<QuadClass> RightArrow, LeftArrow;
		boost::shared_ptr<QuadClass> RightArrow_Selected, LeftArrow_Selected;

		bool CustomArrow;
		Vector2 LeftArrowOffset, RightArrowOffset;
		//public Vector2 LeftArrow_SelectedOffset, RightArrow_SelectedOffset;

		boost::shared_ptr<Lambda> OnIndexSelect, OnConfirmedIndexSelect;

		/// <summary>
		/// Whether to draw the list's arrows when the list isn't currently selected
		/// </summary>
		bool DrawArrowsWhenUnselected;

#if defined(WINDOWS)
		//Vector2 ListPadding = new Vector2(65, 0);
	
		Vector2 ListPadding;
		Vector2 TotalPadding;
	
		virtual bool HitTest( Vector2 pos, Vector2 padding );
#endif

		virtual void FadeIn();

		virtual void FadeOut();

		MenuList();
		boost::shared_ptr<MenuList> MenuList_Construct();
	
		void InitializeArrows();
	
		virtual float Height();

		virtual float Width();
	
		std::map<boost::shared_ptr<MenuItem>, boost::shared_ptr<Object> > ObjDict;
	
		void AddItem( const boost::shared_ptr<MenuItem> &item, const boost::shared_ptr<Object> &obj );

		boost::shared_ptr<MenuItem> GetListItem();

		/// <summary>
		/// The object associated with the currently selected MenuItem
		/// </summary>
		const boost::shared_ptr<Object> &getCurObj();

		/// <summary>
		/// When true the list's index will wrap if too large or too small.
		/// Otherwise it will be restricted.
		/// </summary>
		bool DoIndexWrapping;

		const bool getOnFirstIndex() const;
		const bool getOnLastIndex() const;

		bool ValidIndex( int index );

		boost::shared_ptr<MenuItem> CurMenuItem;
		void SetSelectedItem( const boost::shared_ptr<MenuItem> &item );

		virtual void SetIndex( int NewIndex );

	
		int LastIncrDir;
		void IncrementIndex( int Increment );

#if defined(WINDOWS)
	
		boost::shared_ptr<QuadClass> GetSelectedArrow();
#endif

		/// <summary>
		/// When true clicking on the menu list will selected the next item in the list.
		/// </summary>
		bool ClickForNextItem;

	
		bool HoldSelected;
	
		virtual void PhsxStep( bool Selected );

		bool Center;
		virtual void Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENULIST
