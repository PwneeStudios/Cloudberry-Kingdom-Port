#include <global_header.h>



namespace CloudberryKingdom
{

	const Microsoft::Xna::Framework::Vector2 &CircleBox::getCenter() const
	{
		return _Center;
	}

	void CircleBox::setCenter( const Vector2 &value )
	{
		_Center = value;
		Invalidate();
	}

	const float &CircleBox::getRadius() const
	{
		return _Radius;
	}

	void CircleBox::setRadius( const float &value )
	{
		_Radius = value;
		Invalidate();
	}

	void CircleBox::Invalidate()
	{
		Invalidated = true;
	}

	void CircleBox::MakeNew()
	{
		Invalidated = true;
	}

	CircleBox::CircleBox()
	{
		MakeNew();
	}

	CircleBox::CircleBox( Vector2 center, float radius )
	{
		Initialize( center, radius );
	}

	void CircleBox::Move( Vector2 shift )
	{
		setCenter( getCenter() + shift );

		CalcBounds();
	}

	void CircleBox::Clone( const std::shared_ptr<CircleBox> &A )
	{
		setCenter( A->getCenter() );
		setRadius( A->getRadius() );

		TR = A->TR;
		BL = A->BL;
	}

	void CircleBox::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		writer->Write( getCenter() );
		writer->Write( getRadius() );
	}

	void CircleBox::Read( const std::shared_ptr<BinaryReader> &reader )
	{
		setCenter( reader->ReadVector2() );
		setRadius( reader->ReadSingle() );
	}

	void CircleBox::Draw( Color color )
	{
		Tools::QDrawer->DrawCircle( getCenter(), getRadius(), color );
		Tools::QDrawer->Flush();
	}

	void CircleBox::Initialize( Vector2 center, float radius )
	{
		setCenter( center );
		setRadius( radius );

		Invalidated = true;
	}

	Microsoft::Xna::Framework::Vector2 CircleBox::GetTR()
	{
		Validate();
		return TR;
	}

	Microsoft::Xna::Framework::Vector2 CircleBox::GetBL()
	{
		Validate();
		return BL;
	}

	void CircleBox::CalcBounds()
	{
		TR = getCenter() + Vector2(getRadius(), getRadius());
		BL = getCenter() - Vector2(getRadius(), getRadius());
	}

	void CircleBox::Validate()
	{
		if ( Invalidated )
		{
			CalcBounds();

			Invalidated = false;
		}
	}

	void CircleBox::Scale( float scale )
	{
		setRadius( getRadius() * scale );
	}

	bool CircleBox::BoxOverlap_Tiered( const std::shared_ptr<ObjectData> &Core, const std::shared_ptr<Bob> &bob, const std::shared_ptr<AutoGen> &singleton )
	{
		std::shared_ptr<AutoGen_Parameters> Params = Core->GetParams( singleton );
		int WidthLevel = static_cast<int>( Params->BobWidthLevel.GetVal( Core->Data.Position ) );

		bool col = BoxOverlap( bob->GetBox( WidthLevel ) );

		return col;
	}

	bool CircleBox::BoxOverlap( const std::shared_ptr<AABox> &box )
	{
		Validate();

		if ( box->Target->BL.X >= TR.X )
			return false;
		if ( box->Target->TR.X <= BL.X )
			return false;

		if ( box->Target->BL.Y >= TR.Y )
			return false;
		if ( box->Target->TR.Y <= BL.Y )
			return false;

		std::shared_ptr<FloatRectangle> rect = box->Target;

		return VerticalSegmentOverlap( rect->TR.X, rect->BL.Y, rect->TR.Y ) || VerticalSegmentOverlap( rect->BL.X, rect->BL.Y, rect->TR.Y ) || HorizontalSegmentOverlap( rect->TR.Y, rect->BL.X, rect->TR.X ) || HorizontalSegmentOverlap( rect->BL.Y, rect->BL.X, rect->TR.X ) || ContainedIn( box ); // Inside -  Bottom segment -  Top segment -  Left segment -  Right segment
	}

	bool CircleBox::ContainedIn( const std::shared_ptr<FloatRectangle> &rect )
	{
		return TR.LE( rect->TR ) && BL.GE( rect->BL );
	}

	bool CircleBox::ContainedIn( const std::shared_ptr<AABox> &box )
	{
		box->CalcBounds();
		return TR.LE( box->TR ) && BL.GE( box->BL );
	}

	bool CircleBox::VerticalSegmentOverlap( float x, float y1, float y2 )
	{
		// Get the height of the circle at x (relative to the center)
		float h = Height( x - getCenter().X );

		if ( h == 0 )
			return false;

		// Get the heights of the line segment (relative to the center)
		float h1 = y1 - getCenter().Y;
		float h2 = y2 - getCenter().Y;

		if ( h1 > h )
			return false;
		if ( h2 < -h )
			return false;

		return true;
	}

	bool CircleBox::HorizontalSegmentOverlap( float y, float x1, float x2 )
	{
		// Get the height of the circle at y (relative to the center)
		float h = Height( y - getCenter().Y );

		if ( h == 0 )
			return false;

		// Get the heights of the line segment (relative to the center)
		float h1 = x1 - getCenter().X;
		float h2 = x2 - getCenter().X;

		if ( h1 > h )
			return false;
		if ( h2 < -h )
			return false;

		return true;
	}

	float CircleBox::Height( float x )
	{
		if ( x > getRadius() || x < -getRadius() )
			return 0;
		return static_cast<float>( sqrt( getRadius() * getRadius() - x * x ) );
	}
}
