#ifndef MOVINGBLOCK__AUTO
#define MOVINGBLOCK__AUTO

#include <small_header.h>

//#include "Core/Tools/CoreMath.h"
//#include "Core/Tools/Random.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingBlock.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct MovingBlock_Parameters : public AutoGen_Parameters
	{

		virtual ~MovingBlock_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "MovingBlock_Parameters" );
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
	
		enum AspectType
		{
			AspectType_SQUARE,
			AspectType_THIN,
			AspectType_TALL
		};
	
		Param Range, Period, KeepUnused, Size;

		std::vector<int> MotionLevel;
		MotionType Motion;

		std::vector<float> AspectTypeRatio;
		AspectType Aspect;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		MovingBlock_Parameters() : Motion( MotionType_VERTICAL ), Aspect( AspectType_SQUARE )
		{
			InitializeInstanceFields();
		}
	};

	struct MovingBlock_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<MovingBlock_AutoGen> instance;
	
		const static boost::shared_ptr<MovingBlock_AutoGen> &getInstance();

	
		MovingBlock_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void SetMoveType( const boost::shared_ptr<MovingBlock> &mblock, float Displacement, MovingBlock_Parameters::MotionType mtype, const boost::shared_ptr<Rand> &Rnd );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef MOVINGBLOCK__AUTO
