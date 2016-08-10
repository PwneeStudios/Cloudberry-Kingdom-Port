#ifndef LAMBDAFUNC_2
#define LAMBDAFUNC_2

namespace CloudberryKingdom
{
	template<typename T1, typename T2, typename OutputType>
	struct LambdaFunc_2 : boost::enable_shared_from_this<LambdaFunc_2<T1, T2, OutputType> >
	{
	
		virtual ~LambdaFunc_2()
		{
#ifdef BOOST_BIN
			OnDestructor( "LambdaFunc_2" );
#endif
		}


		virtual OutputType Apply( const T1 &t1, const T2 &t2 ) = 0;

	};
}


#endif	//#ifndef LAMBDAFUNC_2
