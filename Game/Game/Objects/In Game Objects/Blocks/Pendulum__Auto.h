#ifndef PENDULUM__AUTO
#define PENDULUM__AUTO

#include <global_header.h>

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
