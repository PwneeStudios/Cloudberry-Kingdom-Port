#ifndef SPIKEYGUY__AUTO
#define SPIKEYGUY__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{

	struct SpikeyGuy_Parameters : public AutoGen_Parameters
	{

		virtual ~SpikeyGuy_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "SpikeyGuy_Parameters" );
#endif
		}


		struct _Special
		{
			/// <summary>
			/// A special fill type. One giant circle. All floaters have the same pivot point.
			/// </summary>
		
			bool Pinwheel;

			/// <summary>
			/// A special fill type. Multiple, concentric circles. All floaters have the same pivot point.
			/// </summary>
			bool Rockwheel;
		};
	
		Param FloaterMinDist, Density, FloaterPeriod, FloaterScale;
		bool Make;

		_Special Special;


		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );
	};

	struct SpikeyGuy_AutoGen : public AutoGen
	{

		virtual ~SpikeyGuy_AutoGen()
		{
#ifdef BOOST_BIN
			OnDestructor( "SpikeyGuy_AutoGen" );
#endif
		}

	
		struct MinDistHelper : public LambdaFunc_1<Vector2, Vector2>
		{
		
			boost::shared_ptr<SpikeyGuy_Parameters> Params;

		
			MinDistHelper( const boost::shared_ptr<SpikeyGuy_Parameters> &Params );

			Vector2 Apply( const Vector2 &pos );
		};

	
		struct SpikeyGuyCleanupMetricLambda : public LambdaFunc_2<boost::shared_ptr<ObjectBase> , boost::shared_ptr<ObjectBase> , Vector2>
		{
		
			SpikeyGuyCleanupMetricLambda();

			Vector2 Apply( const boost::shared_ptr<ObjectBase> &A, const boost::shared_ptr<ObjectBase> &B );
		};

	
		static boost::shared_ptr<SpikeyGuy_AutoGen> instance;
	
		const static boost::shared_ptr<SpikeyGuy_AutoGen> &getInstance();

	
		SpikeyGuy_AutoGen();

	
		virtual boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		virtual void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		virtual boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );

	
		void Circle( const boost::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir );

		void Rockwheel( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Pinwheel( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		virtual void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};

}


#endif	//#ifndef SPIKEYGUY__AUTO
