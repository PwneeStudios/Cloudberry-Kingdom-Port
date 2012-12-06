#ifndef LASER__AUTO
#define LASER__AUTO

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
	class Laser_Parameters : public AutoGen_Parameters
	{
	public:
		float LaserStepCutoff;
		Param LaserStep, LaserPeriod;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		Laser_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class Laser_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<Laser_AutoGen> instance;
	public:
		const static std::shared_ptr<Laser_AutoGen> &getInstance();

	public:
		Laser_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef LASER__AUTO
