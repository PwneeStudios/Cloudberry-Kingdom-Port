#ifndef SERPENT__AUTO
#define SERPENT__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class AutoGen_Parameters;
}






namespace CloudberryKingdom
{
	class Serpent_Parameters : public AutoGen_Parameters
	{
	public:
		float SerpentStepCutoff;
		Param SerpentStep, SerpentPeriod, NumToMake;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		Serpent_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class Serpent_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<Serpent_AutoGen> instance;
	public:
		const static std::shared_ptr<Serpent_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static Serpent_AutoGen();
	private:
		Serpent_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef SERPENT__AUTO
