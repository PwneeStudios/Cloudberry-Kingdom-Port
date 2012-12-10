#ifndef FIREBALL__AUTO
#define FIREBALL__AUTO

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	struct Fireball_Parameters : public AutoGen_Parameters
	{
	
		Param FireballMaxAngle, FireballMinDist, MaxFireballDensity, Period;
		Param KeepUnused;

		/// <summary>
		/// Whether the fireballs arc.
		/// </summary>
		bool Arc;

		bool DoFill;

		float BorderFillStep;
		bool BorderTop;

		float SurvivalHallwaySpeed;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Fireball_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct Fireball_AutoGen : public AutoGen
	{
	
		static const std::shared_ptr<Fireball_AutoGen> instance;
	
		const static std::shared_ptr<Fireball_AutoGen> &getInstance();

	
		Fireball_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

	
		void inner( const std::shared_ptr<Fireball_Parameters> &Params, const std::shared_ptr<Level> &level, Vector2 pos, int i, LevelGeometry Geometry );

		void BorderFill( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		std::shared_ptr<Fireball_Parameters> GetParams( const std::shared_ptr<Level> &level );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

		static double GetAngle( float MaxAngle, int NumAngles, const std::shared_ptr<Rand> &Rnd );


		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FIREBALL__AUTO
