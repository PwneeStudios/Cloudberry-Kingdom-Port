#ifndef BOULDER__AUTO
#define BOULDER__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Boulder_Parameters : public AutoGen_Parameters
	{

		virtual ~Boulder_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "Boulder_Parameters" );
#endif
		}

	
		struct _Special
		{
			/// <summary>
			/// A special fill type, creating a hallway of floaters.
			/// </summary>
		
			bool Hallway;

			_Special() : Hallway( false ) { }
		};
	
		Param FloaterMinDist, FloaterSparsity, FloaterPeriod, FloaterMaxAngle, FloaterPlaceDelay;

		boost::shared_ptr<TunnelFill> Tunnel;

		_Special Special;

		Vector2 HallwaySpacing;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Boulder_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct Boulder_AutoGen : public AutoGen
	{
	
		struct Cleanup_2Helper : public LambdaFunc_1<Vector2, Vector2>
		{
		
			boost::shared_ptr<Boulder_Parameters> Params;

		
			Cleanup_2Helper( const boost::shared_ptr<Boulder_Parameters> &Params );

			Vector2 Apply( const Vector2 &pos );
		};

	
		struct BoulderFillLambda : public Lambda_1<Vector2>
		{
		
			boost::shared_ptr<Level> level;
			Vector2 TR, BL;
			boost::shared_ptr<Boulder_AutoGen> autogen;

		
			BoulderFillLambda( const boost::shared_ptr<Level> &level, Vector2 TR, Vector2 BL, const boost::shared_ptr<Boulder_AutoGen> &autogen );

			void Apply( const Vector2 &pos );
		};
	
		static boost::shared_ptr<Boulder_AutoGen> instance;
	
		const static boost::shared_ptr<Boulder_AutoGen> &getInstance();

	
		Boulder_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		void Hallway( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );

	
		Vector2 CalcPos( const boost::shared_ptr<Bob> &bob, Vector2 BL, Vector2 TR, const boost::shared_ptr<Rand> &Rnd );

	
		void ActiveFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	};
}


#endif	//#ifndef BOULDER__AUTO
