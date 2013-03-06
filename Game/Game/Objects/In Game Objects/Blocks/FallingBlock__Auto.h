#ifndef FALLINGBLOCK__AUTO
#define FALLINGBLOCK__AUTO

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
	struct ObjectBase;
}

namespace CloudberryKingdom
{
	struct FallingBlock_Parameters : public AutoGen_Parameters
	{
	
		virtual ~FallingBlock_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "FallingBlock_Parameters" );
#endif
		}


		Param Delay, Width, AngryRatio, AngrySpeed, AngryAccel, KeepUnused;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );
	
	};

	struct FallingBlock_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<FallingBlock_AutoGen> instance;
	
		const static boost::shared_ptr<FallingBlock_AutoGen> &getInstance();

	
		FallingBlock_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FALLINGBLOCK__AUTO
