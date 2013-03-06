#ifndef MENULISTALL
#define MENULISTALL

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Brackets
	{
	
		boost::shared_ptr<QuadClass> Br1, Br2;
	
		Brackets();

		void Draw( Vector2 Center );

		void AddToDrawPile( const boost::shared_ptr<DrawPile> &pile );

	};

	struct MenuListAll : public MenuList
	{
	
		virtual ~MenuListAll()
		{
#ifdef BOOST_BIN
			OnDestructor( "MenuListAll" );
#endif
		}


		boost::shared_ptr<MenuItem> SelectedItem;

#if defined(WINDOWS)
	
		Vector2 ListPadding;
		Vector2 TotalPadding;
		boost::shared_ptr<MenuItem> LastHitItem;
	
		virtual bool HitTest( Vector2 pos, Vector2 padding );
#endif

	
		boost::shared_ptr<Brackets> MyBrackets;
	
		MenuListAll();
		boost::shared_ptr<MenuListAll> MenuListAll_Construct();

		virtual void PhsxStep( bool Selected );

		virtual void SetIndex( int NewIndex );

		float ShiftAmount;
		virtual void Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENULISTALL
