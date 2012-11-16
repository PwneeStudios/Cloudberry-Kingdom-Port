#ifndef LAMBDAFUNC
#define LAMBDAFUNC

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{
	template<typename T>
	class LambdaFunc
	{
	public:
		virtual std::shared_ptr<T> Apply() = 0;
	};
}


#endif	//#ifndef LAMBDAFUNC
