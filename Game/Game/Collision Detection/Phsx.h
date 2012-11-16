#ifndef PHSX
#define PHSX

#include <global_header.h>

namespace CloudberryKingdom
{
	class AutoGen;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class AABox;
}

namespace CloudberryKingdom
{
	class ObjectData;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


namespace CloudberryKingdom
{
	class colData
	{
	public:
		bool Collision;
		float Location;
	};

	enum ColType
	{
		ColType_NO_COL,
		ColType_LEFT,
		ColType_RIGHT,
		ColType_TOP,
		ColType_BOTTOM
	};

	class Phsx
	{
		/// <summary>
		/// Return true if a point is in a box specified by BL and TR.
		/// </summary>
	public:
		static bool Inside( Vector2 p, Vector2 BL, Vector2 TR );

		static bool Inside( Vector2 p, Vector2 BL, Vector2 TR, Vector2 padding );

		/// <summary>
		/// Performs a collision detection between Box and a list of tiered boxes associated with the Bob.
		/// </summary>
		static bool BoxBoxOverlap_Tiered( const std::shared_ptr<AABox> &Box, const std::shared_ptr<ObjectData> &Core, const std::shared_ptr<Bob> &bob, const std::shared_ptr<AutoGen> &singleton );

		/// <summary>
		/// Performs a collision detection between Box and a list of tiered boxes associated with the Bob.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The parameter Line was renamed since it is named the same as a user-defined type:
		static bool AABoxAndLineCollisionTest_Tiered( MovingLine &Line_Renamed, const std::shared_ptr<ObjectData> &Core, const std::shared_ptr<Bob> &bob, const std::shared_ptr<AutoGen> &singleton );

		/// <summary>
		/// Returns true if A.Current and B.Current overlap
		/// </summary>
		static bool BoxBoxOverlap( const std::shared_ptr<AABox> &A, const std::shared_ptr<AABox> &B );

		static bool PointAndAABoxCollisionTest( Vector2 &p, const std::shared_ptr<AABox> &Box );
		static bool PointAndAABoxCollisionTest( Vector2 &p, const std::shared_ptr<AABox> &Box, float Padding );

		static bool PointAndLineCollisionTest( Vector2 &t1, Vector2 &t2, Vector2 &n1, Vector2 &n2, Vector2 &LC1, Vector2 &LT1, float Length, Vector2 &p1, Vector2 &p2 );

		static bool LineAndHorizontalLineCollisionTest( float y, float x1, float x2, Line &L );

		static bool LineAndVerticalLineCollisionTest( float x, float y1, float y2, Line &L );

		static bool AABoxAndLineCollisionTest( const std::shared_ptr<AABox> &Box, MovingLine &L );



		static bool AALineCollisionTest( float ACy, float ATy, float BCy, float BTy, float ACx1, float ACx2, float ATx1, float ATx2, float BCx1, float BCx2, float BTx1, float BTx2 );

		static ColType CollisionTest( const std::shared_ptr<AABox> &A, const std::shared_ptr<AABox> &B );
	};
}


#endif	//#ifndef PHSX
