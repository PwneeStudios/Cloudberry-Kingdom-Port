#ifndef NORMALBLOCK__AUTO
#define NORMALBLOCK__AUTO

#include "../Game/Objects/AutoGen.h"
#include "../Game/Level/Make/Parameters/Param.h"
#include "../Game/Level/Make/PieceSeedData.h"

namespace CloudberryKingdom
{
	class Wall;
}

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
	class NormalBlock_Parameters : public AutoGen_Parameters
	{
	public:
		Param KeepUnused;

		/// <summary>
		/// Whether to make normal blocks or not. Doesn't affect other fill weights.
		/// </summary>
		bool Make;

		bool CustomWeight;

		std::shared_ptr<Wall> MyWall;
		std::shared_ptr<Wall> SetWall( LevelGeometry geometry );

		/// <summary>
		/// Whether to do the standard Stage1Fill. False when certain special fills are set.
		/// </summary>
		bool DoStage1Fill, DoInitialPlats, DoFinalPlats;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		NormalBlock_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class NormalBlock_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<NormalBlock_AutoGen> instance;
	public:
		const static std::shared_ptr<NormalBlock_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static NormalBlock_AutoGen();
	private:
		NormalBlock_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

	private:
		void MakeWall( const std::shared_ptr<Level> &level );

		std::shared_ptr<NormalBlock_Parameters> GetParams( const std::shared_ptr<Level> &level );

	public:
		void PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );
		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef NORMALBLOCK__AUTO
