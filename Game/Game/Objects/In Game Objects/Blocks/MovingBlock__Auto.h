#ifndef MOVINGBLOCK__AUTO
#define MOVINGBLOCK__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MovingBlock_Parameters : public AutoGen_Parameters
	{
	
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
