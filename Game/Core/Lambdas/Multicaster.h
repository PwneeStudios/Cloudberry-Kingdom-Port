#ifndef MULTICASTER
#define MULTICASTER

#include <global_header.h>

namespace CloudberryKingdom
{
	class Multicaster : public Lambda
	{
	private:
		std::vector<std::shared_ptr<Lambda> > MyList;

	public:
		void Apply()
		{
			for ( std::vector<std::shared_ptr<Lambda> >::const_iterator L = MyList.begin(); L != MyList.end(); ++L )
				( *L ).get()->Apply();
		}

		void Clear()
		{
			MyList.clear();
		}

		void Add( const std::shared_ptr<Lambda> &L )
		{
			MyList.push_back( L );
		}
	};
}


#endif	//#ifndef MULTICASTER
