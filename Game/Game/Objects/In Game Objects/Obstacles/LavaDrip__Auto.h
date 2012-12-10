#ifndef LAVADRIP__AUTO
#define LAVADRIP__AUTO

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
	struct LavaDrip_Parameters : public AutoGen_Parameters
	{
	
		float LavaDripStepCutoff;
		Param LavaDripStep, Speed;
		VectorParam Length;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		LavaDrip_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct LavaDrip_AutoGen : public AutoGen
	{
	
		static const std::shared_ptr<LavaDrip_AutoGen> instance;
	
		const static std::shared_ptr<LavaDrip_AutoGen> &getInstance();

	
		LavaDrip_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef LAVADRIP__AUTO
