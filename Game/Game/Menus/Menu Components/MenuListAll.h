#ifndef MENULISTALL
#define MENULISTALL

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class DrawPile;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class Camera;
}




namespace CloudberryKingdom
{
	class Brackets
	{
	private:
		std::shared_ptr<QuadClass> Br1, Br2;

	public:
		Brackets();

		void Draw( Vector2 Center );

		void AddToDrawPile( const std::shared_ptr<DrawPile> &pile );
	};

	class MenuListAll : public MenuList
	{
	public:
		std::shared_ptr<MenuItem> SelectedItem;

#if defined(WINDOWS)
	private:
		Vector2 ListPadding;
		Vector2 TotalPadding;
		std::shared_ptr<MenuItem> LastHitItem;
	public:
		virtual bool HitTest( Vector2 pos, Vector2 padding );
#endif

	private:
		std::shared_ptr<Brackets> MyBrackets;
	public:
		MenuListAll();

		virtual void PhsxStep( bool Selected );

		virtual void SetIndex( int NewIndex );

		float ShiftAmount;
		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENULISTALL
