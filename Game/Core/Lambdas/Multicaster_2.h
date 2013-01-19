#ifndef MULTICASTER_2
#define MULTICASTER_2

#include <global_header.h>

namespace CloudberryKingdom
{
	template<typename T1, typename T2>
	struct Multicaster_2 : public Lambda_2<T1, T2>
	{
	
		std::vector<boost::shared_ptr<Lambda_2<T1, T2> > > MyList;

	
		void Apply( const T1 &t1, const T2 &t2 )
		{
			for ( typename std::vector<boost::shared_ptr<Lambda_2<T1, T2> > >::const_iterator L = MyList.begin(); L != MyList.end(); ++L )
				( *L )->Apply( t1, t2 );
		}

		void Clear()
		{
			MyList.clear();
		}

		void Add( const boost::shared_ptr<Lambda_2<T1, T2> > &L )
		{
			MyList.push_back( L );
		}

	
		void InitializeInstanceFields()
		{
			MyList = std::vector<boost::shared_ptr<Lambda_2<T1, T2> > >();
		}


		Multicaster_2()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef MULTICASTER_2
