#ifndef SPIKEYGUY__AUTO
#define SPIKEYGUY__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SpikeyGuy_Parameters : public AutoGen_Parameters
	{
	
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


		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	struct SpikeyGuy_AutoGen : public AutoGen
	{
	
		struct MinDistHelper : public LambdaFunc_1<Vector2, Vector2>
		{
		
			std::shared_ptr<SpikeyGuy_Parameters> Params;

		
			MinDistHelper( const std::shared_ptr<SpikeyGuy_Parameters> &Params );

			Vector2 Apply( const Vector2 &pos );
		};

	
		struct SpikeyGuyCleanupMetricLambda : public LambdaFunc_2<std::shared_ptr<ObjectBase> , std::shared_ptr<ObjectBase> , Vector2>
		{
		
			SpikeyGuyCleanupMetricLambda();

			Vector2 Apply( const std::shared_ptr<ObjectBase> &A, const std::shared_ptr<ObjectBase> &B );
		};

	
		static std::shared_ptr<SpikeyGuy_AutoGen> instance;
	
		const static std::shared_ptr<SpikeyGuy_AutoGen> &getInstance();

	
		SpikeyGuy_AutoGen();

	
		virtual std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		virtual void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		virtual std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

	
		void Circle( const std::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir );

		void Rockwheel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Pinwheel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		virtual void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef SPIKEYGUY__AUTO
