#ifndef FALLINGBLOCK__AUTO
#define FALLINGBLOCK__AUTO

#include <global_header.h>

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






namespace CloudberryKingdom
{
	class FallingBlock_Parameters : public AutoGen_Parameters
	{
	public:
		Param Delay, Width, AngryRatio, AngrySpeed, AngryAccel, KeepUnused;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	class FallingBlock_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<FallingBlock_AutoGen> instance;
	public:
		const static std::shared_ptr<FallingBlock_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static FallingBlock_AutoGen();
	private:
		FallingBlock_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FALLINGBLOCK__AUTO
