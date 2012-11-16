#ifndef FIREBALL__AUTO
#define FIREBALL__AUTO

#define _USE_MATH_DEFINES
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
	class Rand;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;



namespace CloudberryKingdom
{
	class Fireball_Parameters : public AutoGen_Parameters
	{
	public:
		Param FireballMaxAngle, FireballMinDist, MaxFireballDensity, Period;
		Param KeepUnused;

		/// <summary>
		/// Whether the fireballs arc.
		/// </summary>
		bool Arc;

		bool DoFill;

		float BorderFillStep;
		bool BorderTop;

		float SurvivalHallwaySpeed;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		Fireball_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class Fireball_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<Fireball_AutoGen> instance;
	public:
		const static std::shared_ptr<Fireball_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static Fireball_AutoGen();
	private:
		Fireball_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

	private:
		void inner( const std::shared_ptr<Fireball_Parameters> &Params, const std::shared_ptr<Level> &level, Vector2 pos, int i, LevelGeometry Geometry );

		void BorderFill( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

	public:
		std::shared_ptr<Fireball_Parameters> GetParams( const std::shared_ptr<Level> &level );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

		static double GetAngle( float MaxAngle, int NumAngles, const std::shared_ptr<Rand> &Rnd );


		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FIREBALL__AUTO
