#ifndef LAMBDAFUNC_1
#define LAMBDAFUNC_1

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{
	template<typename T, typename OutputType>
	class LambdaFunc_1
	{
	public:
		virtual std::shared_ptr<OutputType> Apply( const std::shared_ptr<T> &t ) = 0;
	};
}


#endif	//#ifndef LAMBDAFUNC_1
