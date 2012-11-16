#ifndef LAMBDAFUNC_1
#define LAMBDAFUNC_1

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
