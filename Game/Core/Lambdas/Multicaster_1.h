#ifndef MULTICASTER_1
#define MULTICASTER_1

#include <global_header.h>

namespace CloudberryKingdom
{
	template<typename T>
	struct Multicaster_1 : public Lambda_1<T>
	{
	
		std::vector<boost::shared_ptr<Lambda_1<T> > > MyList;

	
		void Apply( const T &t )
		{
			for ( typename std::vector<boost::shared_ptr<Lambda_1<T> > >::const_iterator L = MyList.begin(); L != MyList.end(); ++L )
				( *L )->Apply( t );
		}

		void Clear()
		{
			MyList.clear();
		}

		void Add( const boost::shared_ptr<Lambda_1<T> > L )
		{
			MyList.push_back( L );
		}

	
		void InitializeInstanceFields()
		{
			MyList = std::vector<boost::shared_ptr<Lambda_1<T> > >();
		}


		Multicaster_1()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef MULTICASTER_1
