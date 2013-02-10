#ifndef LAMBDA
#define LAMBDA

namespace CloudberryKingdom
{
	struct Lambda : boost::enable_shared_from_this<Lambda>
	{

		virtual ~Lambda() { }

		virtual void Apply() = 0;

	};
}


#endif	//#ifndef LAMBDA
