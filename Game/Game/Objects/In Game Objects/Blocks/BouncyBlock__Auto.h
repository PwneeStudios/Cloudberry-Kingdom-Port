#ifndef BOUNCYBLOCK__AUTO
#define BOUNCYBLOCK__AUTO

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
	class BouncyBlock;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


namespace CloudberryKingdom
{
	class BouncyBlock_Parameters : public AutoGen_Parameters
	{
	public:
		class _Special
		{
			/// <summary>
			/// A special fill type. Creates a ceiling and ground of bouncy blocks.
			/// </summary>
		public:
			bool Hallway;
		};
	public:
		Param Speed, Size, SideDampening, KeepUnused, EdgeSafety;

		_Special Special;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	class BouncyBlock_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<BouncyBlock_AutoGen> instance;
	public:
		const static std::shared_ptr<BouncyBlock_AutoGen> &getInstance();

	private:
		BouncyBlock_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

	private:
		void SetHallwaysBlockProperties( const std::shared_ptr<BouncyBlock> &block, const std::shared_ptr<Level> &level );
		void Hallway( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	public:
		void PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );
	};
}


#endif	//#ifndef BOUNCYBLOCK__AUTO
