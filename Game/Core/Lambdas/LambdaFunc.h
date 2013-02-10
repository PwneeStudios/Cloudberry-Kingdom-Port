#ifndef LAMBDAFUNC
#define LAMBDAFUNC

namespace CloudberryKingdom
{
	template<typename T>
	struct LambdaFunc : boost::enable_shared_from_this<LambdaFunc<T> >
	{

		virtual ~LambdaFunc() { }

		virtual T Apply() = 0;

	};
}


#endif	//#ifndef LAMBDAFUNC
