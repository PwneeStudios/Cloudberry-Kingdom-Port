#ifndef LAMBDA
#define LAMBDA

namespace CloudberryKingdom
{
	struct Lambda : boost::enable_shared_from_this<Lambda>
	{

		virtual ~Lambda()
		{
#ifdef BOOST_BIN
			OnDestructor( "Lambda" );
#endif
		}


		virtual void Apply() = 0;

	};
}


#endif	//#ifndef LAMBDA
