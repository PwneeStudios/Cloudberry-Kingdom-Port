#ifndef LAMBDAFUNC_2
#define LAMBDAFUNC_2

namespace CloudberryKingdom
{
	template<typename T1, typename T2, typename OutputType>
	class LambdaFunc_2
	{
	public:
		virtual OutputType Apply( const T1 &t1, const T2 &t2 ) = 0;
	};
}


#endif	//#ifndef LAMBDAFUNC_2
