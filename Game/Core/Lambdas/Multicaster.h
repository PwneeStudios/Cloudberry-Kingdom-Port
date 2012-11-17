#ifndef MULTICASTER
#define MULTICASTER

#include <global_header.h>

namespace CloudberryKingdom
{
	class Lambda;
}


namespace CloudberryKingdom
{
	class Multicaster : public Lambda
	{
	private:
		std::vector<Lambda*> MyList;

	public:
		void Apply()
		{
			for ( std::vector<Lambda*>::const_iterator L = MyList.begin(); L != MyList.end(); ++L )
				( *L )->Apply();
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
