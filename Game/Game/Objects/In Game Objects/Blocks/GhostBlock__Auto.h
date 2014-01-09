#ifndef GHOSTBLOCK__AUTO
#define GHOSTBLOCK__AUTO

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Blocks/GhostBlock.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{
	struct GhostBlock_Parameters : public AutoGen_Parameters
	{
	
		virtual ~GhostBlock_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "GhostBlock_Parameters" );
#endif
		}


		enum BoxTypes
		{
			BoxTypes_TOP_ONLY,
			BoxTypes_FULL,
			BoxTypes_LONG
		};
	
		Param InLength, OutLength, Width, KeepUnused, TimeSafety;

		BoxTypes BoxType;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );
	};

	struct GhostBlock_AutoGen : public AutoGen
	{
	
		struct OnGhostUsedLambda : public Lambda
		{
		
			boost::shared_ptr<GhostBlock> block;
			boost::shared_ptr<Level> level;

		
			OnGhostUsedLambda( const boost::shared_ptr<GhostBlock> &block, const boost::shared_ptr<Level> &level );

			void Apply();
		};
	
		static boost::shared_ptr<GhostBlock_AutoGen> instance;
	
		const static boost::shared_ptr<GhostBlock_AutoGen> &getInstance();

	
		GhostBlock_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

	};
}


#endif	//#ifndef GHOSTBLOCK__AUTO
