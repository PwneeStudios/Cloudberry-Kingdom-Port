#ifndef MULTICASTER
#define MULTICASTER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Multicaster : public Lambda
	{
	
		std::vector<boost::shared_ptr<Lambda> > MyList;

	
		void Apply()
		{
			for ( std::vector<boost::shared_ptr<Lambda> >::const_iterator L = MyList.begin(); L != MyList.end(); ++L )
				( *L ).get()->Apply();
		}

		void Clear()
		{
			MyList.clear();
		}

		void Add( const boost::shared_ptr<Lambda> &L )
		{
			MyList.push_back( L );
		}
	};
}


#endif	//#ifndef MULTICASTER
