#ifndef CONVEYOR__AUTO
#define CONVEYOR__AUTO

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
	struct ConveyorBlock_Parameters : public AutoGen_Parameters
	{
	
		Param Width, KeepUnused, Speed;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	struct ConveyorBlock_AutoGen : public AutoGen
	{
	
		static const std::shared_ptr<ConveyorBlock_AutoGen> instance;
	
		const static std::shared_ptr<ConveyorBlock_AutoGen> &getInstance();

	
		ConveyorBlock_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ConveyorBlock_Parameters> GetParams( const std::shared_ptr<Level> &level );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef CONVEYOR__AUTO
