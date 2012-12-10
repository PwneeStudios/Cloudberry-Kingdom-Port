#ifndef LASER__AUTO
#define LASER__AUTO

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
	struct Laser_Parameters : public AutoGen_Parameters
	{
	
		float LaserStepCutoff;
		Param LaserStep, LaserPeriod;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Laser_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct Laser_AutoGen : public AutoGen
	{
	
		static const std::shared_ptr<Laser_AutoGen> instance;
	
		const static std::shared_ptr<Laser_AutoGen> &getInstance();

	
		Laser_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef LASER__AUTO
