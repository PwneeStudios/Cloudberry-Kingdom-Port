#include <global_header.h>

namespace CloudberryKingdom
{

	_LineDeath::_LineDeath()
	{
	}

	_LineDeath::_LineDeath( bool BoxesOnly )
	{
		Construct( BoxesOnly );
	}

	void _LineDeath::Construct( bool BoxesOnly )
	{
		getCore()->BoxesOnly = BoxesOnly;

		MakeNew();
	}

	void _LineDeath::Interact( const std::shared_ptr<Bob> &bob )
	{
		if ( Phsx::AABoxAndLineCollisionTest( bob->Box2, MyLine ) )
		{
			if ( getCore()->MyLevel->PlayMode == 0 )
				bob->Die( BobDeathType_LASER, shared_from_this() );
			else
			{
				bool col = Phsx::AABoxAndLineCollisionTest_Tiered( MyLine, getCore(), bob, AutoGenSingleton );

				if ( col )
					getCore()->getRecycle()->CollectObject( shared_from_this() );
			}
		}
	}

	void _LineDeath::DrawBoxes()
	{
		Tools::QDrawer->DrawLine( MyLine.Target.p1, MyLine.Target.p2, Color::Orange, 20 );
	}

	void _LineDeath::Move( Vector2 shift )
	{
		_Death::Move( shift );

		MyLine.Current.p1 += shift;
		MyLine.Current.p2 += shift;
		MyLine.Target.p1 += shift;
		MyLine.Target.p2 += shift;

		p1 += shift;
		p2 += shift;
	}

	void _LineDeath::PhsxStep2()
	{
		if ( !getCore()->SkippedPhsx )
			MyLine.SwapToCurrent();
	}
}
