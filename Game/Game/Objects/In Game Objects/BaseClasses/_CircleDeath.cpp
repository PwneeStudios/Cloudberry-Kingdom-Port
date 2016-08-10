#include <small_header.h>
#include "Game/Objects/In Game Objects/BaseClasses/_CircleDeath.h"

#include "Game/Collision Detection/Circle.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_Death.h"

#include "Game/Level/Level.h"

namespace CloudberryKingdom
{

	void _CircleDeath::MakeNew()
	{
		Circle->Initialize( Vector2(), 1 );

		getCore()->Init();
		getCore()->GenData.OverlapWidth = 60;

		getCore()->SkippedPhsx = true;
		getCore()->ContinuousEnabled = true;
	}

	_CircleDeath::_CircleDeath() :
		Radius( 0 )
	{
	}

	_CircleDeath::_CircleDeath( bool BoxesOnly ) :
		Radius( 0 )
	{
		Construct( BoxesOnly );
	}

	void _CircleDeath::Construct( bool BoxesOnly )
	{
		getCore()->BoxesOnly = BoxesOnly;

		Circle = boost::make_shared<CircleBox>();

		MakeNew();
	}

	void _CircleDeath::Scale( float scale )
	{
		Circle->Scale( scale );
	}

	void _CircleDeath::ActivePhsxStep()
	{
		Circle->setCenter( getPos() );
		Circle->setRadius( Radius );

		if ( getCore()->WakeUpRequirements )
		{
			Circle->Invalidate();

			getCore()->WakeUpRequirements = false;
		}
	}

	void _CircleDeath::DrawBoxes()
	{
		Circle->Draw( bColor( 50, 50, 255, 120 ) );
	}

	void _CircleDeath::Move( Vector2 shift )
	{
		_Death::Move( shift );

		Circle->Move( shift );
	}

	void _CircleDeath::Interact( const boost::shared_ptr<Bob> &bob )
	{
		if ( !getCore()->SkippedPhsx )
		{
			bool Col = Circle->BoxOverlap( bob->Box2 );

			if ( Col )
			{
				if ( getCore()->MyLevel->PlayMode == 0 )
				{
					bob->Die( DeathType, shared_from_this() );
					Die();
				}

				if ( getCore()->MyLevel->PlayMode != 0 )
				{
					bool col = Circle->BoxOverlap_Tiered( getCore(), bob, AutoGenSingleton );

					if ( col )
						CollectSelf();
				}
			}
		}
	}

	void _CircleDeath::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		getCore()->WakeUpRequirements = true;
	}
}
