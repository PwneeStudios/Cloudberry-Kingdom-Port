#ifndef MENULISTALL
#define MENULISTALL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct QuadClass;
}

namespace CloudberryKingdom
{
	struct DrawPile;
}

namespace CloudberryKingdom
{
	struct MenuItem;
}

namespace CloudberryKingdom
{
	struct Camera;
}




namespace CloudberryKingdom
{
	struct Brackets
	{
	
		std::shared_ptr<QuadClass> Br1, Br2;

	
		Brackets();

		void Draw( Vector2 Center );

		void AddToDrawPile( const std::shared_ptr<DrawPile> &pile );
	};

	struct MenuListAll : public MenuList
	{
	
		std::shared_ptr<MenuItem> SelectedItem;

#if defined(WINDOWS)
	
		Vector2 ListPadding;
		Vector2 TotalPadding;
		std::shared_ptr<MenuItem> LastHitItem;
	
		virtual bool HitTest( Vector2 pos, Vector2 padding );
#endif

	
		std::shared_ptr<Brackets> MyBrackets;
	
		MenuListAll();

		virtual void PhsxStep( bool Selected );

		virtual void SetIndex( int NewIndex );

		float ShiftAmount;
		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENULISTALL
