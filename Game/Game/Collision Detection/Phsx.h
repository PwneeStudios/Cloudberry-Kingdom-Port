#ifndef PHSX
#define PHSX

#include <small_header.h>

//#include "Game/Collision Detection/AABox.h"
//#include "Game/Collision Detection/Line.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/Bob/Bob.h"


namespace CloudberryKingdom
{
	struct AutoGen;
}

namespace CloudberryKingdom
{
	struct Bob;
}

namespace CloudberryKingdom
{
	struct AABox;
}

namespace CloudberryKingdom
{
	struct ObjectData;
}

namespace CloudberryKingdom
{
	struct colData
	{
	
		bool Collision;
		float Location;
	};

	struct Phsx
	{
		/// <summary>
		/// Return true if a point is in a box specified by BL and TR.
		/// </summary>
	
		static bool Inside( Vector2 p, Vector2 BL, Vector2 TR );

		static bool Inside( Vector2 p, Vector2 BL, Vector2 TR, Vector2 padding );

		/// <summary>
		/// Performs a collision detection between Box and a list of tiered boxes associated with the Bob.
		/// </summary>
		static bool BoxBoxOverlap_Tiered( const boost::shared_ptr<AABox> &Box, const boost::shared_ptr<ObjectData> &Core, const boost::shared_ptr<Bob> &bob, const boost::shared_ptr<AutoGen> &singleton );

		/// <summary>
		/// Performs a collision detection between Box and a list of tiered boxes associated with the Bob.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The parameter Line was renamed since it is named the same as a user-defined type:
		static bool AABoxAndLineCollisionTest_Tiered( MovingLine &Line_Renamed, const boost::shared_ptr<ObjectData> &Core, const boost::shared_ptr<Bob> &bob, const boost::shared_ptr<AutoGen> &singleton );

		/// <summary>
		/// Returns true if A.Current and B.Current overlap
		/// </summary>
		static bool BoxBoxOverlap( const boost::shared_ptr<AABox> &A, const boost::shared_ptr<AABox> &B );

		static bool PointAndAABoxCollisionTest( Vector2 &p, const boost::shared_ptr<AABox> &Box );
		static bool PointAndAABoxCollisionTest( Vector2 &p, const boost::shared_ptr<AABox> &Box, float Padding );

		static bool PointAndLineCollisionTest( Vector2 &t1, Vector2 &t2, Vector2 &n1, Vector2 &n2, Vector2 &LC1, Vector2 &LT1, float Length, Vector2 &p1, Vector2 &p2 );

		static bool LineAndHorizontalLineCollisionTest( float y, float x1, float x2, Line &L );

		static bool LineAndVerticalLineCollisionTest( float x, float y1, float y2, Line &L );

		static bool AABoxAndLineCollisionTest( const boost::shared_ptr<AABox> &Box, MovingLine &L );



		static bool AALineCollisionTest( float ACy, float ATy, float BCy, float BTy, float ACx1, float ACx2, float ATx1, float ATx2, float BCx1, float BCx2, float BTx1, float BTx2 );

		static ColType CollisionTest( const boost::shared_ptr<AABox> &A, const boost::shared_ptr<AABox> &B );
	};
}


#endif	//#ifndef PHSX
