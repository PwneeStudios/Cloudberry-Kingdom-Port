#ifndef CLOUD__AUTO
#define CLOUD__AUTO

#include "../Game/Objects/AutoGen.h"
#include "../Game/Level/Make/Parameters/Param.h"

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Cloud_Parameters : public AutoGen_Parameters
	{
	public:
		Param Size, Shiftiness;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	class Cloud_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<Cloud_AutoGen> instance;
	public:
		const static std::shared_ptr<Cloud_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static Cloud_AutoGen();
	private:
		Cloud_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef CLOUD__AUTO
