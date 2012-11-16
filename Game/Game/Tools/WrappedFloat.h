#ifndef WRAPPEDFLOAT
#define WRAPPEDFLOAT

#include "../Core/Tools/Set.h"
#include <cmath>

namespace CloudberryKingdom
{
	class Lambda;
}

namespace CloudberryKingdom
{
	class LambdaFunc;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class WrappedBool
	{
	public:
		bool MyBool;

		WrappedBool( bool val );
	};

	class WrappedInt
	{
	public:
		int MyInt;

		WrappedInt( int val );
	};

	class WrappedFloat
	{
	public:
		float MyFloat;
		float MinVal, MaxVal;

		const float &getVal() const;
		void setVal( const float &value );

		std::shared_ptr<Lambda> SetCallback;
		std::shared_ptr<LambdaFunc<float> > GetCallback;

		WrappedFloat();

		float DefaultValue;
		WrappedFloat( float Val, float MinVal, float MaxVal );

		void Set( float val );

		const float &getSpread() const;
		const float &getRatio() const;
		const float &getPercent() const;

		void Release();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef WRAPPEDFLOAT
