#ifndef LAMBDA_2
#define LAMBDA_2

namespace CloudberryKingdom
{
	template<typename T1, typename T2>
	struct Lambda_2 : boost::enable_shared_from_this<Lambda_2<T1, T2> >
	{

		virtual ~Lambda_2()
		{
#ifdef BOOST_BIN
			OnDestructor( "Lambda_2" );
#endif
		}


		virtual void Apply( const T1 &t1, const T2 &t2 ) = 0;

	};
}


#endif	//#ifndef LAMBDA_2
