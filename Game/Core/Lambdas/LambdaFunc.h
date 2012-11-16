#ifndef LAMBDAFUNC
#define LAMBDAFUNC

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
