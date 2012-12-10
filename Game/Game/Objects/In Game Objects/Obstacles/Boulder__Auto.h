#ifndef BOULDER__AUTO
#define BOULDER__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Boulder_Parameters : public AutoGen_Parameters
	{
	
		struct _Special
		{
			/// <summary>
			/// A special fill type, creating a hallway of floaters.
			/// </summary>
		
			bool Hallway;
		};
	
		Param FloaterMinDist, FloaterSparsity, FloaterPeriod, FloaterMaxAngle, FloaterPlaceDelay;

		std::shared_ptr<TunnelFill> Tunnel;

		_Special Special;

		Vector2 HallwaySpacing;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	
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
		
			std::shared_ptr<Boulder_Parameters> Params;

		
			Cleanup_2Helper( const std::shared_ptr<Boulder_Parameters> &Params );

			Vector2 Apply( const Vector2 &pos );
		};

	
		struct BoulderFillLambda : public Lambda_1<Vector2>
		{
		
			std::shared_ptr<Level> level;
			Vector2 TR, BL;
			std::shared_ptr<Boulder_AutoGen> autogen;

		
			BoulderFillLambda( const std::shared_ptr<Level> &level, Vector2 TR, Vector2 BL, const std::shared_ptr<Boulder_AutoGen> &autogen );

			void Apply( const Vector2 &pos );
		};
	
		static const std::shared_ptr<Boulder_AutoGen> instance;
	
		const static std::shared_ptr<Boulder_AutoGen> &getInstance();

	
		Boulder_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		void Hallway( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	
		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

	
		Vector2 CalcPos( const std::shared_ptr<Bob> &bob, Vector2 BL, Vector2 TR, const std::shared_ptr<Rand> &Rnd );

	
		void ActiveFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	};
}


#endif	//#ifndef BOULDER__AUTO
