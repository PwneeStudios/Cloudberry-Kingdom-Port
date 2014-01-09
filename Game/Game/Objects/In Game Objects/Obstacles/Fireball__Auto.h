#ifndef FIREBALL__AUTO
#define FIREBALL__AUTO

#define _USE_MATH_DEFINES
#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/Tools/CoreMath.h"
//#include "Core/Tools/Random.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Unset.h"


namespace CloudberryKingdom
{

	struct Fireball_Parameters : public AutoGen_Parameters
	{

		virtual ~Fireball_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "Fireball_Parameters" );
#endif
		}

	
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

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Fireball_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct Fireball_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<Fireball_AutoGen> instance;
	
		const static boost::shared_ptr<Fireball_AutoGen> &getInstance();

	
		Fireball_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

	
		void inner( const boost::shared_ptr<Fireball_Parameters> &Params, const boost::shared_ptr<Level> &level, Vector2 pos, int i, LevelGeometry Geometry );

		void BorderFill( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		boost::shared_ptr<Fireball_Parameters> GetParams( const boost::shared_ptr<Level> &level );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );

		static double GetAngle( float MaxAngle, int NumAngles, const boost::shared_ptr<Rand> &Rnd );


		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FIREBALL__AUTO
