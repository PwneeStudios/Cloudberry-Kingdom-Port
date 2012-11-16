#ifndef FIRESPINNER__AUTO
#define FIRESPINNER__AUTO

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
	class AutoGen_Parameters;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class ParamInfo
	{
	public:
		float MinValue, MaxValue, DefaultValue;

		ParamInfo( float MinValue, float MaxValue, float DefaultValue );
	};

	class FireSpinner_Parameters : public AutoGen_Parameters
	{
		/*
		public enum DirectionStyle { Homogenous, Random, HorizontalSplit, VerticalSplit };
		public DirectionStyle Direction;
		public int Orientation;
		public enum Style { Regular, Clockwork, DoubleOrbit, Rotated, Gap, VariableLength, VariableGap };
		public Style Style1, Style2;
		public int NumStyles;
		*/

/*
        public static ParamInfo _MinDist = new ParamInfo(60, 700, 600, c_MinDist, "Min distance");
        static float c_MinDist(Upgrades u) { return DifficultyHelper.Interp159(650, 270, 110, u[Upgrade.FireSpinner]); }

        public static ParamInfo _MinDensity = new ParamInfo(20, 200, 60, c_MinDensity, "Min density");
        static float c_MinDensity(Upgrades u) { return DifficultyHelper.Interp(50, 80, u[Upgrade.FireSpinner]); }

        public static ParamInfo _MaxDensity = new ParamInfo(20, 400, 60, c_MaxDensity, "Max density");
        static float c_MaxDensity(Upgrades u) { return DifficultyHelper.Interp(50, 150, u[Upgrade.FireSpinner]); }

        public static ParamInfo _Length = new ParamInfo(100, 1200, 300, c_Length, "Length");
        static float c_Length(Upgrades u) { return 240 + 36 * u[Upgrade.FireSpinner]; }

        public static ParamInfo _Period = new ParamInfo(20, 500, 150, c_Period, "Period"); do min and max and num periods?
        static float c_Period(Upgrades u) { return Math.Max(38, 150 + 13 * u[Upgrade.FireSpinner] - 13 * u[Upgrade.Speed]); }

        public static ParamInfo _ColLevel = new ParamInfo(0, 10, 2, c_ColLevel, "Collision level");
        static float c_ColLevel(Upgrades u) { return u[Upgrade.FireSpinner]; }

        public static ParamInfo _NumOffsets = new ParamInfo(1, 32, 4, c_NumOffsets, "Number of period offsets");
        static float c_NumOffsets(Upgrades u) { if (u[Upgrade.FireSpinner] > 6) return 8; else return 4; }
        */
	public:
		Param MinDist, MinDensity, MaxDensity, Length, Period;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );
	};

	class FireSpinner_AutoGen : public AutoGen
	{
	private:
		class Cleanup_2Proxy : public LambdaFunc_1<Vector2, Vector2>
		{
		private:
			std::shared_ptr<FireSpinner_Parameters> Params;

		public:
			Cleanup_2Proxy( const std::shared_ptr<FireSpinner_Parameters> &Params );

			Vector2 Apply( Vector2 pos );
		};

	private:
		static const std::shared_ptr<FireSpinner_AutoGen> instance;
	public:
		const static std::shared_ptr<FireSpinner_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static FireSpinner_AutoGen();
	private:
		FireSpinner_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};

}


#endif	//#ifndef FIRESPINNER__AUTO
