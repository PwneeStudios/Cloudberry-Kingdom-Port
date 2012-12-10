#ifndef GHOSTBLOCK__AUTO
#define GHOSTBLOCK__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GhostBlock_Parameters : public AutoGen_Parameters
	{
	
		enum BoxTypes
		{
			BoxTypes_TOP_ONLY,
			BoxTypes_FULL,
			BoxTypes_LONG
		};
	
		Param InLength, OutLength, Width, KeepUnused, TimeSafety;

		BoxTypes BoxType;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	struct GhostBlock_AutoGen : public AutoGen
	{
	
		struct OnGhostUsedLambda : public Lambda
		{
		
			std::shared_ptr<GhostBlock> block;
			std::shared_ptr<Level> level;

		
			OnGhostUsedLambda( const std::shared_ptr<GhostBlock> &block, const std::shared_ptr<Level> &level );

			void Apply();
		};
	
		static const std::shared_ptr<GhostBlock_AutoGen> instance;
	
		const static std::shared_ptr<GhostBlock_AutoGen> &getInstance();

	
		GhostBlock_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

	};
}


#endif	//#ifndef GHOSTBLOCK__AUTO
