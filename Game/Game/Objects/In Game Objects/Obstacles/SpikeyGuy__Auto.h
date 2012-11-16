#ifndef SPIKEYGUY__AUTO
#define SPIKEYGUY__AUTO

#include <global_header.h>

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
	class ObjectBase;
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
	class SpikeyGuy_Parameters : public AutoGen_Parameters
	{
	public:
		class _Special
		{
			/// <summary>
			/// A special fill type. One giant circle. All floaters have the same pivot point.
			/// </summary>
		public:
			bool Pinwheel;

			/// <summary>
			/// A special fill type. Multiple, concentric circles. All floaters have the same pivot point.
			/// </summary>
			bool Rockwheel;
		};
	public:
		Param FloaterMinDist, Density, FloaterPeriod, FloaterScale;
		bool Make;

		_Special Special;


		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	class SpikeyGuy_AutoGen : public AutoGen
	{
	private:
		class MinDistHelper : public LambdaFunc_1<Vector2, Vector2>
		{
		private:
			std::shared_ptr<SpikeyGuy_Parameters> Params;

		public:
			MinDistHelper( const std::shared_ptr<SpikeyGuy_Parameters> &Params );

			Vector2 Apply( Vector2 pos );
		};

	private:
		class SpikeyGuyCleanupMetricLambda : public LambdaFunc_2<ObjectBase*, ObjectBase*, Vector2>
		{
		public:
			SpikeyGuyCleanupMetricLambda();

			Vector2 Apply( const std::shared_ptr<ObjectBase> &A, const std::shared_ptr<ObjectBase> &B );
		};

	private:
		static const std::shared_ptr<SpikeyGuy_AutoGen> instance;
	public:
		const static std::shared_ptr<SpikeyGuy_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static SpikeyGuy_AutoGen();
	protected:
		SpikeyGuy_AutoGen();

	public:
		virtual std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		virtual void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		virtual std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

	private:
		void Circle( const std::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir );

		void Rockwheel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Pinwheel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	public:
		virtual void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef SPIKEYGUY__AUTO
