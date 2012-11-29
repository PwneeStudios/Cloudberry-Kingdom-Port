#ifndef MULTICASTER_2
#define MULTICASTER_2

#include <global_header.h>

namespace CloudberryKingdom
{
	template<typename T1, typename T2>
	class Multicaster_2 : public Lambda_2<T1, T2>
	{
	private:
		std::vector<std::shared_ptr<Lambda_2<T1, T2> > > MyList;

	public:
		void Apply( T1 t1, T2 t2 )
		{
			for ( std::vector<std::shared_ptr<Lambda_2<T1, T2> > >::const_iterator L = MyList.begin(); L != MyList.end(); ++L )
				( *L )->Apply( t1, t2 );
		}

		void Clear()
		{
			MyList.clear();
		}

		void Add( const std::shared_ptr<Lambda_2<T1, T2> > &L )
		{
			MyList.push_back( L );
		}

	private:
		void InitializeInstanceFields()
		{
			MyList = std::vector<std::shared_ptr<Lambda_2<T1, T2> > >();
		}

public:
		Multicaster_2()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef MULTICASTER_2
