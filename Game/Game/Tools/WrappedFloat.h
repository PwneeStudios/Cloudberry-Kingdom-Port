#ifndef WRAPPEDFLOAT
#define WRAPPEDFLOAT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct WrappedBool
	{
	
		bool MyBool;

		WrappedBool( bool val );
	};

	struct WrappedInt : public Object
	{
	
		int MyInt;

		WrappedInt( int val );
	};

	struct WrappedFloat
	{
	
		float MyFloat;
		float MinVal, MaxVal;

		const float &getVal();
		void setVal( const float &value );

		std::shared_ptr<Lambda> SetCallback;
		std::shared_ptr<LambdaFunc<float> > GetCallback;

		WrappedFloat();

		float DefaultValue;
		WrappedFloat( float Val, float MinVal, float MaxVal );

		void Set( float val );

		float getSpread() const;
		float getRatio();
		float getPercent();

		void Release();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef WRAPPEDFLOAT
