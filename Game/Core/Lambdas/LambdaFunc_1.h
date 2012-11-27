#ifndef LAMBDAFUNC_1
#define LAMBDAFUNC_1

namespace CloudberryKingdom
{
	template<typename T, typename OutputType>
	class LambdaFunc_1
	{
	public:
		virtual OutputType Apply( T &t ) = 0;
	};
}


#endif	//#ifndef LAMBDAFUNC_1
