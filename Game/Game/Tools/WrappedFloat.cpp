#include <global_header.h>

namespace CloudberryKingdom
{

	WrappedBool::WrappedBool( bool val ) :
		MyBool( val )
	{
	}

	WrappedInt::WrappedInt( int val ) :
		MyInt( val )
	{
	}

	const float &WrappedFloat::getVal()
	{
		if ( GetCallback != 0 )
			MyFloat = GetCallback->Apply();

		return MyFloat;
	}

	void WrappedFloat::setVal( const float &value )
	{
		Set( value );
	}

	WrappedFloat::WrappedFloat() :
		MyFloat( 0 ),
		MinVal( 0 ),
		MaxVal( 0 ),
		DefaultValue( 0 )
	{
		InitializeInstanceFields();
	}

	WrappedFloat::WrappedFloat( float Val, float MinVal, float MaxVal ) :
		MinVal( MinVal ),
		MaxVal( MaxVal )
	{
		InitializeInstanceFields();
		this->setVal( Val );
		DefaultValue = this->getVal();
	}

	void WrappedFloat::Set( float val )
	{
		MyFloat = __min( MaxVal, __max( MinVal, val ) );
		if ( SetCallback != 0 )
			SetCallback->Apply();
	}

	float WrappedFloat::getSpread() const
	{
		return MaxVal - MinVal;
	}

	float WrappedFloat::getRatio()
	{
		return ( getVal() - MinVal ) / getSpread();
	}

	float WrappedFloat::getPercent()
	{
		return 100 * getRatio();
	}

	void WrappedFloat::Release()
	{
		SetCallback.reset();
	}

	void WrappedFloat::InitializeInstanceFields()
	{
		MinVal = FLT_MIN;
		MaxVal = FLT_MAX;
	}
}
