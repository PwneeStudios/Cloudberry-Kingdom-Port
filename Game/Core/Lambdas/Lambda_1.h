#ifndef LAMBDA_1
#define LAMBDA_1

namespace CloudberryKingdom
{
	template<typename T>
	struct Lambda_1 : boost::enable_shared_from_this<Lambda_1<T> >
	{

	
		virtual void Apply( const T &t ) = 0;

	};
}


#endif	//#ifndef LAMBDA_1
