#ifndef LAMBDAFUNC
#define LAMBDAFUNC

namespace CloudberryKingdom
{
	template<typename T>
	struct LambdaFunc
	{
	
		virtual T Apply() = 0;
	};
}


#endif	//#ifndef LAMBDAFUNC
