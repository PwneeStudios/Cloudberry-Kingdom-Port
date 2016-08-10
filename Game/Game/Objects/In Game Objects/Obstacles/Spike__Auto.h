#ifndef SPIKE__AUTO
#define SPIKE__AUTO

#define _USE_MATH_DEFINES
#include <small_header.h>

//#include "Core/Tools/Random.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/Spike.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	
	struct Spike_Parameters : public AutoGen_Parameters
	{

		virtual ~Spike_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "Spike_Parameters" );
#endif
		}

	
		enum OffsetStyles
		{
			OffsetStyles_RND,
			OffsetStyles_SAW_TOOTH,
			OffsetStyles_SINE,
			OffsetStyles_LENGTH
		};
	
		Param SpikeMinDist, MinSpikeDensity, MaxSpikeDensity, SpikePeriod;

		OffsetStyles OffsetStyle;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

		/// <summary>
		/// Set the period and period offset of the spike.
		/// The spike's position should already have been set.
		/// </summary>
		void SetPeriod( const boost::shared_ptr<Spike> &spike, const boost::shared_ptr<Rand> &Rnd );
	};

	struct Spike_AutoGen : public AutoGen
	{
	
		struct SpikeCleanup : public LambdaFunc_1<Vector2, Vector2>
		{
		
			boost::shared_ptr<Spike_Parameters> Params;

		
			SpikeCleanup( const boost::shared_ptr<Spike_Parameters> &Params );

			Vector2 Apply( const Vector2 &pos );
		};
	
		static boost::shared_ptr<Spike_AutoGen> instance;
	
		const static boost::shared_ptr<Spike_AutoGen> &getInstance();

	
		Spike_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	};
}


#endif	//#ifndef SPIKE__AUTO
