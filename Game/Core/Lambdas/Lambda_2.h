#ifndef LAMBDA_2
#define LAMBDA_2






namespace CloudberryKingdom
{
	template<typename T1, typename T2>
	class Lambda_2
	{
	public:
		virtual void Apply( const std::shared_ptr<T1> &t1, const std::shared_ptr<T2> &t2 ) = 0;
	};
}


#endif	//#ifndef LAMBDA_2
