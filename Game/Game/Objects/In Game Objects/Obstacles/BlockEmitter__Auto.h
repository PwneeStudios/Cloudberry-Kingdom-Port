#ifndef BLOCKEMITTER__AUTO
#define BLOCKEMITTER__AUTO

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingPlatform.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{

	struct BlockEmitter_Parameters : public AutoGen_Parameters
	{

		virtual ~BlockEmitter_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "BlockEmitter_Parameters" );
#endif
		}

	
		enum Style
		{
			Style_FULL,
			Style_SEPARATED,
			Style_LENGTH
		};

	
		Style MyStyle;

		/// <summary>
		/// The frame number on which the last used emitter was marked as used.
		/// </summary>
		int LastUsedTimeStamp;

		Param Delay, Speed, Width, SpeedAdd, WidthAdd, Types, Amp, Dist, DistAdd, KeepUnused;
		float StepCutoff;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		BlockEmitter_Parameters() :
			MyStyle( Style_FULL ),
			LastUsedTimeStamp( 0 ),
			StepCutoff( 0 )
		{
			InitializeInstanceFields();
		}
	};

	struct BlockEmitter_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<BlockEmitter_AutoGen> instance;
	
		const static boost::shared_ptr<BlockEmitter_AutoGen> &getInstance();

	
		BlockEmitter_AutoGen();

	
		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );

		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void PreFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		static float GetVel( const boost::shared_ptr<BlockEmitter_Parameters> &Params, Vector2 &Pos );

		static void SetAndAdd( const boost::shared_ptr<Level> &level, const boost::shared_ptr<BlockEmitter_Parameters> &Params, Vector2 Pos, const boost::shared_ptr<BlockEmitter> &bm );

	
		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef BLOCKEMITTER__AUTO
