#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	WrappedBool::WrappedBool( bool val )
	{
		MyBool = val;
	}

	WrappedInt::WrappedInt( int val )
	{
		MyInt = val;
	}

	const float &WrappedFloat::getVal() const
	{
		if ( GetCallback != 0 )
			MyFloat = GetCallback->Apply();

		return MyFloat;
	}

	void WrappedFloat::setVal( const float &value )
	{
		Set( value );
	}

	WrappedFloat::WrappedFloat()
	{
		InitializeInstanceFields();
	}

	WrappedFloat::WrappedFloat( float Val, float MinVal, float MaxVal )
	{
		InitializeInstanceFields();
		this->MinVal = MinVal;
		this->MaxVal = MaxVal;
		this->setVal( Val );
	DefaultValue = this->getVal();
	}

	void WrappedFloat::Set( float val )
	{
		MyFloat = __min( MaxVal, __max( MinVal, val ) );
		if ( SetCallback != 0 )
			SetCallback->Apply();
	}

	const float &WrappedFloat::getSpread() const
	{
		return MaxVal - MinVal;
	}

	const float &WrappedFloat::getRatio() const
	{
		return ( getVal() - MinVal ) / getSpread();
	}

	const float &WrappedFloat::getPercent() const
	{
		return 100 * getRatio();
	}

	void WrappedFloat::Release()
	{
		SetCallback.reset();
	}

	void WrappedFloat::InitializeInstanceFields()
	{
		MinVal = float::MinValue;
		MaxVal = float::MaxValue;
	}
}
