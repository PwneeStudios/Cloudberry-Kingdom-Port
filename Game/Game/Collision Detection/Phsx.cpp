#include <global_header.h>

namespace CloudberryKingdom
{
	bool Phsx::Inside( Vector2 p, Vector2 BL, Vector2 TR )
	{
		if ( p.X > TR.X )
			return false;
		if ( p.X < BL.X )
			return false;
		if ( p.Y > TR.Y )
			return false;
		if ( p.Y < BL.Y )
			return false;

		return true;
	}

	bool Phsx::Inside( Vector2 p, Vector2 BL, Vector2 TR, Vector2 padding )
	{
		return Inside( p, BL - padding, TR + padding );
	}

	bool Phsx::BoxBoxOverlap_Tiered( const boost::shared_ptr<AABox> &Box, const boost::shared_ptr<ObjectData> &Core, const boost::shared_ptr<Bob> &bob, const boost::shared_ptr<AutoGen> &singleton )
	{
		boost::shared_ptr<AutoGen_Parameters> Params = Core->GetParams( singleton );
		int WidthLevel = static_cast<int>( Params->BobWidthLevel.GetVal( Core->Data.Position ) );

		bool col = Phsx::BoxBoxOverlap( bob->GetBox( WidthLevel ), Box );

		return col;
	}

	bool Phsx::AABoxAndLineCollisionTest_Tiered( MovingLine &Line_Renamed, const boost::shared_ptr<ObjectData> &Core, const boost::shared_ptr<Bob> &bob, const boost::shared_ptr<AutoGen> &singleton )
	{
		boost::shared_ptr<AutoGen_Parameters> Params = Core->GetParams( singleton );
		int WidthLevel = static_cast<int>( Params->BobWidthLevel.GetVal( Core->Data.Position ) );

		bool col = Phsx::AABoxAndLineCollisionTest( bob->GetBox( WidthLevel ), Line_Renamed );

		return col;
	}

	bool Phsx::BoxBoxOverlap( const boost::shared_ptr<AABox> &A, const boost::shared_ptr<AABox> &B )
	{
		// Do not need to validate if we are using *.Target directly
		//A.Validate();
		//B.Validate();

		//A.Current.CalcReal();
		//B.Current.CalcReal();

		/*
		Vector2 A_BL = A.Current.RealBL;
		Vector2 B_TR = B.Current.RealTR;
		if (A_BL.X >= B_TR.X || A_BL.Y >= B_TR.Y) return false;
	
		Vector2 A_TR = A.Current.RealTR;
		Vector2 B_BL = B.Current.RealBL;
		if (A_TR.X <= B_BL.X || A_TR.Y <= B_BL.Y) return false;
		 * */

		if ( A->Target->BL.X >= B->Target->TR.X )
			return false;
		if ( A->Target->TR.X <= B->Target->BL.X )
			return false;

		if ( A->Target->BL.Y >= B->Target->TR.Y )
			return false;

		if ( B->TopOnly )
		{
			if ( A->Target->TR.Y <= B->Target->TR.Y )
				return false;
		}
		else
		{
			if ( A->Target->TR.Y <= B->Target->BL.Y )
				return false;
		}

		//if (A.BL.X >= B.TR.X || A.BL.Y >= B.TR.Y) return false;
		//if (A.TR.X <= B.BL.X || A.TR.Y <= B.BL.Y) return false;

		return true;
	}

	bool Phsx::PointAndAABoxCollisionTest( Vector2 &p, const boost::shared_ptr<AABox> &Box )
	{
		return PointAndAABoxCollisionTest( p, Box, 0 );
	}

	bool Phsx::PointAndAABoxCollisionTest( Vector2 &p, const boost::shared_ptr<AABox> &Box, float Padding )
	{
		Box->Validate();
		Vector2 A_BL = Vector2::Min( Box->Current->BL, Box->Target->BL );
		if ( A_BL.X > p.X + Padding || A_BL.Y > p.Y + Padding )
			return false;

		Vector2 A_TR = Vector2::Max( Box->Current->TR, Box->Target->TR );
		if ( A_TR.X < p.X - Padding || A_TR.Y < p.Y - Padding )
			return false;

		return true;
	}

	bool Phsx::PointAndLineCollisionTest( Vector2 &t1, Vector2 &t2, Vector2 &n1, Vector2 &n2, Vector2 &LC1, Vector2 &LT1, float Length, Vector2 &p1, Vector2 &p2 )
	{
		float d1 = Vector2::Dot( p1 - LC1, n1 );
		float d2 = Vector2::Dot( p2 - LT1, n2 );

		if ( Sign( d1 ) != Sign( d2 ) )
		{
			float n = Vector2::Dot( p1 - LC1, t1 );
			if ( n > 0 && n < Length )
				//Console.WriteLine("!!!!!!!!!!!!!!!");
				return true;
		}

		return false;
	}

	bool Phsx::LineAndHorizontalLineCollisionTest( float y, float x1, float x2, Line &L )
	{
		if ( Sign( L.p1.Y - y ) == Sign( L.p2.Y - y ) )
			return false;

		float t = ( y - L.p2.Y ) / ( L.p1.Y - L.p2.Y );
		if ( t < 0 || t > 1 )
			return false;
		float x = t * L.p1.X + ( 1 - t ) * L.p2.X;
		if ( Sign( x - x1 ) == Sign( x - x2 ) )
			return false;

		return true;
	}

	bool Phsx::LineAndVerticalLineCollisionTest( float x, float y1, float y2, Line &L )
	{
		if ( Sign( L.p1.X - x ) == Sign( L.p2.X - x ) )
			return false;

		float t = ( x - L.p2.X ) / ( L.p1.X - L.p2.X );
		if ( t < 0 || t > 1 )
			return false;
		float y = t * L.p1.Y + ( 1 - t ) * L.p2.Y;
		if ( Sign( y - y1 ) == Sign( y - y2 ) )
			return false;

		return true;
	}

	bool Phsx::AABoxAndLineCollisionTest( const boost::shared_ptr<AABox> &Box, MovingLine &L )
	{
		Box->Validate();
		L.Validate();
		if ( L.BL.X > Box->TR.X || L.BL.Y > Box->TR.Y )
			return false;
		if ( L.TR.X < Box->BL.X || L.TR.Y < Box->BL.Y )
			return false;

		if ( false ) //L.SkipEdge)
		{
			Vector2 p1, p2;

			Vector2 t1 = L.Current.p2 - L.Current.p1;
			Vector2 t2 = L.Target.p2 - L.Target.p1;
			float Length = t1.Length();
			t1.Normalize();
			t2.Normalize();
			Vector2 n1 = Vector2();
			n1.X = t1.Y;
			n1.Y = -t1.X;
			Vector2 n2 = Vector2();
			n2.X = t2.Y;
			n2.Y = -t2.X;

			p1 = Box->Current->TR;
			p2 = Box->Target->TR;
			if ( PointAndLineCollisionTest( t1, t2, n1, n2, L.Current.p1, L.Target.p1, Length, p1, p2 ) )
				return true;

			p1 = Box->Current->BL;
			p2 = Box->Target->BL;
			if ( PointAndLineCollisionTest( t1, t2, n1, n2, L.Current.p1, L.Target.p1, Length, p1, p2 ) )
				return true;

			p1 = Vector2( Box->Current->TR.X, Box->Current->BL.Y );
			p2 = Vector2( Box->Target->TR.X, Box->Target->BL.Y );
			if ( PointAndLineCollisionTest( t1, t2, n1, n2, L.Current.p1, L.Target.p1, Length, p1, p2 ) )
				return true;

			p1 = Vector2( Box->Current->BL.X, Box->Current->TR.Y );
			p2 = Vector2( Box->Target->BL.X, Box->Target->TR.Y );
			if ( PointAndLineCollisionTest( t1, t2, n1, n2, L.Current.p1, L.Target.p1, Length, p1, p2 ) )
				return true;

			if ( PointAndAABoxCollisionTest( L.Current.p1, Box ) )
				return true;
			if ( PointAndAABoxCollisionTest( L.Current.p2, Box ) )
				return true;
		}

		if ( !L.SkipOverlap )
		{
			if ( LineAndHorizontalLineCollisionTest( Box->Target->TR.Y, Box->Target->TR.X, Box->Target->BL.X, L.Target ) )
				return true;
			if ( LineAndHorizontalLineCollisionTest( Box->Target->BL.Y, Box->Target->TR.X, Box->Target->BL.X, L.Target ) )
				return true;
			if ( LineAndVerticalLineCollisionTest( Box->Target->TR.X, Box->Target->TR.Y, Box->Target->BL.Y, L.Target ) )
				return true;
			if ( LineAndVerticalLineCollisionTest( Box->Target->BL.X, Box->Target->TR.Y, Box->Target->BL.Y, L.Target ) )
				return true;
		}

		return false;
	}

	bool Phsx::AALineCollisionTest( float ACy, float ATy, float BCy, float BTy, float ACx1, float ACx2, float ATx1, float ATx2, float BCx1, float BCx2, float BTx1, float BTx2 )
	{
		int CurrentSign, TargetSign;

		CurrentSign = Sign( ACy - BCy );
		TargetSign = Sign( ATy - BTy );
		if ( CurrentSign != TargetSign || CurrentSign == 0 && TargetSign == 0 )
		{
			if ( __max( ACx2, ATx2 ) < __max( BCx1, BTx1 ) )
				return false;
			if ( __min( ACx1, ATx1 ) > __min( BCx2, BTx2 ) )
				return false;

			return true;
		}

		return false;
	}

	ColType Phsx::CollisionTest( const boost::shared_ptr<AABox> &A, const boost::shared_ptr<AABox> &B )
	{
		A->Validate();
		B->Validate();
		if ( A->BL.X > B->TR.X || A->BL.Y > B->TR.Y )
			return ColType_NO_COL;
		if ( A->TR.X < B->BL.X || A->TR.Y < B->BL.Y )
			return ColType_NO_COL;

		ColType type = ColType_NO_COL;

		// A bottom to B top
		if ( !A->TopOnly )
		{
			if ( A->Current->BL.Y >= B->Current->TR.Y )
				if ( AALineCollisionTest( A->Current->BL.Y, A->Target->BL.Y, B->Current->TR.Y, B->Target->TR.Y, A->Current->BL.X, A->Current->TR.X, A->Target->BL.X, A->Target->TR.X, B->Current->BL.X, B->Current->TR.X, B->Target->BL.X, B->Target->TR.X ) )
					type = ColType_TOP;
		}

		// A top to B bottom
		if ( !B->TopOnly )
		{
			if ( A->Current->TR.Y <= B->Current->BL.Y )
				if ( AALineCollisionTest( A->Current->TR.Y, A->Target->TR.Y, B->Current->BL.Y, B->Target->BL.Y, A->Current->BL.X, A->Current->TR.X, A->Target->BL.X, A->Target->TR.X, B->Current->BL.X, B->Current->TR.X, B->Target->BL.X, B->Target->TR.X ) )
					type = ColType_BOTTOM;
		}

		if ( !A->TopOnly && !B->TopOnly && !A->NoSides && !B->NoSides )
		{
			// A right to B left
			if ( A->Current->TR.X <= B->Current->BL.X && A->Target->TR.X - A->Current->TR.X >= B->Target->BL.X - B->Current->BL.X )
				if ( AALineCollisionTest( A->Current->TR.X, A->Target->TR.X, B->Current->BL.X, B->Target->BL.X, A->Current->BL.Y, A->Current->TR.Y, A->Target->BL.Y, A->Target->TR.Y, B->Current->BL.Y, B->Current->TR.Y, B->Target->BL.Y, B->Target->TR.Y ) )
					type = ColType_LEFT;

			// A left to B right
			if ( A->Current->BL.X >= B->Current->TR.X && A->Target->BL.X - A->Current->BL.X <= B->Target->TR.X - B->Current->TR.X )
				if ( AALineCollisionTest( A->Current->BL.X, A->Target->BL.X, B->Current->TR.X, B->Target->TR.X, A->Current->BL.Y, A->Current->TR.Y, A->Target->BL.Y, A->Target->TR.Y, B->Current->BL.Y, B->Current->TR.Y, B->Target->BL.Y, B->Target->TR.Y ) )
					type = ColType_RIGHT;
		}

		return type;
	}
}
