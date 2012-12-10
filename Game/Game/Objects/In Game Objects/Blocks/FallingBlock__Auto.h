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
	
		Param Delay, Width, AngryRatio, AngrySpeed, AngryAccel, KeepUnused;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	struct FallingBlock_AutoGen : public AutoGen
	{
	
		static const std::shared_ptr<FallingBlock_AutoGen> instance;
	
		const static std::shared_ptr<FallingBlock_AutoGen> &getInstance();

	
		FallingBlock_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FALLINGBLOCK__AUTO
