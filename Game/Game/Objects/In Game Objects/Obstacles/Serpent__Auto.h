#ifndef SERPENT__AUTO
#define SERPENT__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct PieceSeedData;
}

namespace CloudberryKingdom
{
	struct Level;
}

namespace CloudberryKingdom
{
	struct AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	struct Serpent_Parameters : public AutoGen_Parameters
	{
	
		float SerpentStepCutoff;
		Param SerpentStep, SerpentPeriod, NumToMake;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Serpent_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct Serpent_AutoGen : public AutoGen
	{
	
		static std::shared_ptr<Serpent_AutoGen> instance;
	
		const static std::shared_ptr<Serpent_AutoGen> &getInstance();

	
		Serpent_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef SERPENT__AUTO
