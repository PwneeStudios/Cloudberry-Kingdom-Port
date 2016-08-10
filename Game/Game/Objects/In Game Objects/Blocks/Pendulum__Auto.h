#ifndef PENDULUM__AUTO
#define PENDULUM__AUTO

#include <small_header.h>

//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Blocks/Pendulum.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct Pendulum_Parameters : public AutoGen_Parameters
	{
	
		virtual ~Pendulum_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "Pendulum_Parameters" );
#endif
		}


		enum MotionType
		{
			MotionType_VERTICAL,
			MotionType_HORIZONTAL,
			MotionType_AA,
			MotionType_CROSS,
			MotionType_STRAIGHT,
			MotionType_CIRLCES,
			MotionType_ALL
		};
	
		Param Period, MaxAngle, KeepUnused, Size;

		std::vector<int> MotionLevel;
		MotionType Motion;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Pendulum_Parameters() :
			Motion( static_cast<MotionType>( 0 ) )
		{
			InitializeInstanceFields();
		}
	};

	struct Pendulum_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<Pendulum_AutoGen> instance;
	
		const static boost::shared_ptr<Pendulum_AutoGen> &getInstance();

	
		Pendulum_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef PENDULUM__AUTO
