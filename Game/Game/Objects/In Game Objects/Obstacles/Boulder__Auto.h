#ifndef BOULDER__AUTO
#define BOULDER__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	class TunnelFill;
}

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class Level;
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

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class Rand;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;



namespace CloudberryKingdom
{
	class Boulder_Parameters : public AutoGen_Parameters
	{
	public:
		class _Special
		{
			/// <summary>
			/// A special fill type, creating a hallway of floaters.
			/// </summary>
		public:
			bool Hallway;
		};
	public:
		Param FloaterMinDist, FloaterSparsity, FloaterPeriod, FloaterMaxAngle, FloaterPlaceDelay;

		std::shared_ptr<TunnelFill> Tunnel;

		_Special Special;

		Vector2 HallwaySpacing;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		Boulder_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class Boulder_AutoGen : public AutoGen
	{
	private:
		class Cleanup_2Helper : public LambdaFunc_1<Vector2, Vector2>
		{
		private:
			std::shared_ptr<Boulder_Parameters> Params;

		public:
			Cleanup_2Helper( const std::shared_ptr<Boulder_Parameters> &Params );

			Vector2 Apply( Vector2 pos );
		};

	private:
		class BoulderFillLambda : public Lambda_1<Vector2>
		{
		private:
			std::shared_ptr<Level> level;
			Vector2 TR, BL;
			std::shared_ptr<Boulder_AutoGen> autogen;

		public:
			BoulderFillLambda( const std::shared_ptr<Level> &level, Vector2 TR, Vector2 BL, const std::shared_ptr<Boulder_AutoGen> &autogen );

			void Apply( Vector2 pos );
		};
	private:
		static const std::shared_ptr<Boulder_AutoGen> instance;
	public:
		const static std::shared_ptr<Boulder_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static Boulder_AutoGen();
	private:
		Boulder_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	private:
		void Hallway( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	public:
		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

	private:
		Vector2 CalcPos( const std::shared_ptr<Bob> &bob, Vector2 BL, Vector2 TR, const std::shared_ptr<Rand> &Rnd );

	public:
		void ActiveFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	};
}


#endif	//#ifndef BOULDER__AUTO
