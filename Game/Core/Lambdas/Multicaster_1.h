#ifndef MULTICASTER_1
#define MULTICASTER_1

#include "Lambda_1.h"
#include <vector>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{
	template<typename T>
	class Multicaster_1 : public Lambda_1<T>
	{
	private:
		std::vector<Lambda_1<T>*> MyList;

	public:
		void Apply( T t )
		{
			for ( std::vector<Lambda_1<T>*>::const_iterator L = MyList.begin(); L != MyList.end(); ++L )
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
			MyList = std::vector<Lambda_1<T>*>();
		}

public:
		Multicaster_1()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef MULTICASTER_1
