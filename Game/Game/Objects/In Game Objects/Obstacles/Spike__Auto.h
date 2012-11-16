#ifndef SPIKE__AUTO
#define SPIKE__AUTO

#define _USE_MATH_DEFINES
#include "../Game/Objects/AutoGen.h"
#include "../Game/Level/Make/Parameters/Param.h"
#include "../Core/Lambdas/LambdaFunc_1.h"
#include <vector>
#include <cmath>

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
	class Rand;
}

namespace CloudberryKingdom
{
	class Spike;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			class Vector2;
		}
	}
}

namespace CloudberryKingdom
{
	class AutoGen_Parameters;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Spike_Parameters : public AutoGen_Parameters
	{
	public:
		enum OffsetStyles
		{
			OffsetStyles_RND,
			OffsetStyles_SAW_TOOTH,
			OffsetStyles_SINE
		};
	public:
		Param SpikeMinDist, MinSpikeDensity, MaxSpikeDensity, SpikePeriod;

		OffsetStyles OffsetStyle;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

		/// <summary>
		/// Set the period and period offset of the spike.
		/// The spike's position should already have been set.
		/// </summary>
		void SetPeriod( const std::shared_ptr<Spike> &spike, const std::shared_ptr<Rand> &Rnd );
	};

	class Spike_AutoGen : public AutoGen
	{
	private:
		class SpikeCleanup : public LambdaFunc_1<Vector2, Vector2>
		{
		private:
			std::shared_ptr<Spike_Parameters> Params;

		public:
			SpikeCleanup( const std::shared_ptr<Spike_Parameters> &Params );

			Vector2 Apply( Vector2 pos );
		};
	private:
		static const std::shared_ptr<Spike_AutoGen> instance;
	public:
		const static std::shared_ptr<Spike_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static Spike_AutoGen();
	private:
		Spike_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	};
}


#endif	//#ifndef SPIKE__AUTO
