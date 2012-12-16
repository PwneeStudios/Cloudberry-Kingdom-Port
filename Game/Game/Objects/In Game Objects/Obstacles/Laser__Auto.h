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

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Laser_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct Laser_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<Laser_AutoGen> instance;
	
		const static boost::shared_ptr<Laser_AutoGen> &getInstance();

	
		Laser_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef LASER__AUTO
