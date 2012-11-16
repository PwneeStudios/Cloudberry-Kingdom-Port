#ifndef GENERATORS
#define GENERATORS

#include <vector>

namespace CloudberryKingdom
{
	class AutoGen;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{
	class Generators
	{
	private:
		static const std::shared_ptr<Generators> instance;
	public:
		const static std::shared_ptr<Generators> &getInstance() const;

		static std::vector<AutoGen*> Gens, PreFill_1_Gens, PreFill_2_Gens, ActiveFill_1_Gens, WeightedPreFill_1_Gens;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static Generators();
	private:
		Generators();

	public:
		static void AddGenerator( const std::shared_ptr<AutoGen> &gen );

		static int IndexOf( const std::shared_ptr<AutoGen> &gen );
	};
}


#endif	//#ifndef GENERATORS
