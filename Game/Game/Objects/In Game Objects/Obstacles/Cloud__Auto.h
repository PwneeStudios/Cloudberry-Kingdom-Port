#ifndef CLOUD__AUTO
#define CLOUD__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Cloud_Parameters : public AutoGen_Parameters
	{
	
		Param Size, Shiftiness;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	struct Cloud_AutoGen : public AutoGen
	{
	
		static std::shared_ptr<Cloud_AutoGen> instance;
	
		const static std::shared_ptr<Cloud_AutoGen> &getInstance();

	
		Cloud_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef CLOUD__AUTO
