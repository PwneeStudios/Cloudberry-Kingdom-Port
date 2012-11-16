#ifndef GHOSTBLOCK__AUTO
#define GHOSTBLOCK__AUTO

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
	class GhostBlock;
}

namespace CloudberryKingdom
{
	class AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class GhostBlock_Parameters : public AutoGen_Parameters
	{
	public:
		enum BoxTypes
		{
			BoxTypes_TOP_ONLY,
			BoxTypes_FULL,
			BoxTypes_LONG
		};
	public:
		Param InLength, OutLength, Width, KeepUnused, TimeSafety;

		BoxTypes BoxType;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	class GhostBlock_AutoGen : public AutoGen
	{
	private:
		class OnGhostUsedLambda : public Lambda
		{
		private:
			std::shared_ptr<GhostBlock> block;
			std::shared_ptr<Level> level;

		public:
			OnGhostUsedLambda( const std::shared_ptr<GhostBlock> &block, const std::shared_ptr<Level> &level );

			void Apply();
		};
	private:
		static const std::shared_ptr<GhostBlock_AutoGen> instance;
	public:
		const static std::shared_ptr<GhostBlock_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static GhostBlock_AutoGen();
	private:
		GhostBlock_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

	};
}


#endif	//#ifndef GHOSTBLOCK__AUTO
