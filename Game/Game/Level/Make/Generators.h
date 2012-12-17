#ifndef GENERATORS
#define GENERATORS

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Generators
	{

	
		static void InitializeStatics();

	
		static boost::shared_ptr<Generators> instance;
	
		const static boost::shared_ptr<Generators> &getInstance();

		static std::vector<boost::shared_ptr<AutoGen> > Gens, PreFill_1_Gens, PreFill_2_Gens, ActiveFill_1_Gens, WeightedPreFill_1_Gens;

	
		Generators();

	
		static void AddGenerator( const boost::shared_ptr<AutoGen> &gen );

		static int IndexOf( const boost::shared_ptr<AutoGen> &gen );

	};

}


#endif	//#ifndef GENERATORS
