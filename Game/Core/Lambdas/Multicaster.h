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
		void Apply();

		void Clear();

		void Add( const std::shared_ptr<Lambda> &L );

		void Remove( const std::shared_ptr<Lambda> &L );

	private:
		void InitializeInstanceFields();

public:
		Multicaster()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef MULTICASTER
