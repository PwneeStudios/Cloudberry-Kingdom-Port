#ifndef GENERATORS
#define GENERATORS

#include <global_header.h>

namespace CloudberryKingdom
{

	class Generators
	{

	public:
		static void InitializeStatics();

	private:
		static std::shared_ptr<Generators> instance;
	public:
		const static std::shared_ptr<Generators> &getInstance();

		static std::vector<std::shared_ptr<AutoGen> > Gens, PreFill_1_Gens, PreFill_2_Gens, ActiveFill_1_Gens, WeightedPreFill_1_Gens;

	public:
		Generators();

	public:
		static void AddGenerator( const std::shared_ptr<AutoGen> &gen );

		static int IndexOf( const std::shared_ptr<AutoGen> &gen );

	};

}


#endif	//#ifndef GENERATORS
