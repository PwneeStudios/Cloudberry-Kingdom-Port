#ifndef BLOCKEMITTER__AUTO
#define BLOCKEMITTER__AUTO

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
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	class BlockEmitter;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class BlockEmitter_Parameters : public AutoGen_Parameters
	{
	public:
		enum BoxStyle
		{
			BoxStyle_TOP_ONLY,
			BoxStyle_FULL_BOX
		};

	public:
		enum Style
		{
			Style_FULL,
			Style_SEPARATED
		};
	public:
		Style MyStyle;

		/// <summary>
		/// The frame number on which the last used emitter was marked as used.
		/// </summary>
		int LastUsedTimeStamp;

		Param Delay, Speed, Width, SpeedAdd, WidthAdd, Types, Amp, Dist, DistAdd, KeepUnused;
		float StepCutoff;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		BlockEmitter_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class BlockEmitter_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<BlockEmitter_AutoGen> instance;
	public:
		const static std::shared_ptr<BlockEmitter_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static BlockEmitter_AutoGen();
	private:
		BlockEmitter_AutoGen();

	public:
		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	private:
		static float GetVel( const std::shared_ptr<BlockEmitter_Parameters> &Params, Vector2 &Pos );

		static void SetAndAdd( const std::shared_ptr<Level> &level, const std::shared_ptr<BlockEmitter_Parameters> &Params, Vector2 Pos, const std::shared_ptr<BlockEmitter> &bm );

	public:
		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef BLOCKEMITTER__AUTO
