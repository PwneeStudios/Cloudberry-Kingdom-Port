#ifndef MULTICASTER_1
#define MULTICASTER_1

#include <global_header.h>

namespace CloudberryKingdom
{
	template<typename T>
	class Multicaster_1 : public Lambda_1<T>
	{
	private:
		std::vector<std::shared_ptr<Lambda_1<T> > > MyList;

	public:
		void Apply( T t )
		{
			for ( std::vector<std::shared_ptr<Lambda_1<T> > >::const_iterator L = MyList.begin(); L != MyList.end(); ++L )
				( *L )->Apply( t );
		}

		void Clear()
		{
			MyList.clear();
		}

		void Add( const std::shared_ptr<Lambda_1<T> > &L )
		{
			MyList.push_back( L );
		}

	private:
		void InitializeInstanceFields()
		{
			MyList = std::vector<std::shared_ptr<Lambda_1<T> > >();
		}

public:
		Multicaster_1()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef MULTICASTER_1
