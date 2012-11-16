#ifndef COREMATH
#define COREMATH

#define _USE_MATH_DEFINES
#include <global_header.h>









namespace CloudberryKingdom
{
	class CoreMath
	{
	public:
		static int Modulo( int n, int p );
		static float Modulo( float n, float p );
		static float ZigZag( float period, float t );
		static float PeriodicCentered( float A, float B, float period, float t );
		static float Periodic( float A, float B, float period, float t );
		static float Periodic( float A, float B, float period, float t, float PhaseDegree );
		static Vector2 Periodic( Vector2 A, Vector2 B, float period, float t );
		static std::wstring Time( int frames );
		static std::wstring ShortTime( int frames );
		static int Hours( int frames );
		static int Minutes( int frames );
		static int Seconds( int frames );
		static int Milliseconds( int frames );
		/// <summary>
		/// Convert radians to degrees.
		/// </summary>
		static float Degrees( float Radians );
		/// <summary>
		/// Convert degrees to radians.
		/// </summary>
		static float Radians( float Degrees );
		static float c;
		static float RadianDist( float a1, float a2 );
		static float AngleDist( float a1, float a2 );
		static float VectorToAngle( Vector2 v );
		static Vector2 CartesianToPolar( Vector2 v );
		static Vector2 PolarToCartesian( Vector2 v );
		/// <summary>
		/// Converts an angle in radians to a normalized direction vector.
		/// </summary>
		/// <param name="Angle">The angle in radians.</param>
		/// <returns></returns>
		static Vector2 AngleToDir( double Angle );
		/// <summary>
		/// Converts an angle in degrees to a normalized direction vector.
		/// </summary>
		/// <param name="Angle">The angle in degrees.</param>
		/// <returns></returns>
		static Vector2 DegreesToDir( double Angle );
		static float Snap( float x, float spacing );
		static Vector2 Snap( Vector2 x, Vector2 spacing );
		/// <summary>
		/// Calculate the sup norm of a vector.
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		static float SupNorm( Vector2 v );
		static Vector2 Sign( Vector2 v );
//ORIGINAL LINE: public static float Max(params float[] vals)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		static float Max( ... );
		/// <summary>
		/// Take in two vectors and find both the max and the min.
		/// </summary>
		static void MaxAndMin( Vector2 &p1, Vector2 &p2, Vector2 &Max, Vector2 &Min );
		/// <summary>
		/// Returns the component-wise absolute value of the Vector2
		/// </summary>
		static Vector2 Abs( Vector2 v );
		/// <summary>
		/// Checks whether two points are close to each other.
		/// </summary>
		/// <param name="v1">The first point.</param>
		/// <param name="v2">The second point.</param>
		/// <param name="Cutoff">The cutoff range.</param>
		/// <returns></returns>
		static bool Close( Vector2 v1, Vector2 v2, Vector2 Cutoff );
		static Vector2 Restrict( float min, float max, Vector2 val );
		/// <summary>
		/// Restrict a value between a min and a max.
		/// </summary>
		static float Restrict( float min, float max, float val );
		static void Restrict( float min, float max, float &val );
		/// <summary>
		/// Restrict a value between a min and a max.
		/// </summary>
		static int Restrict( int min, int max, int val );
		static void Restrict( int min, int max, int &val );

		/// <summary>
		/// Interpolate between a list of values.
		/// t = 0 returns the first value, t = 1 the second value, etc
		/// </summary>
//ORIGINAL LINE: public static float MultiLerpRestrict(float t, params float[] values)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		static float MultiLerpRestrict( float t, ... );
//ORIGINAL LINE: public static Vector2 MultiLerpRestrict(float t, params Vector2[] values)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		static Vector2 MultiLerpRestrict( float t, ... );
		static int LerpRestrict( int v1, int v2, float t );
		static int Lerp( int v1, int v2, float t );
		static float LerpRestrict( float v1, float v2, float t );
		static float Lerp( float v1, float v2, float t );
		static Vector2 LerpRestrict( Vector2 v1, Vector2 v2, float t );

		/// <summary>
		/// Linear interpolation with the additional property that
		/// if v1 == 0, then t <- Max(0, t - .5)
		/// </summary>
		static float SpecialLerp( float v1, float v2, float t );

		/// <summary>
		/// Special linear interpolation, followed by a restriction between the v0 and v1 values.
		/// </summary>
		static float SpecialLerpRestrict( float v1, float v2, float t );

		/// <summary>
		/// Let f(x) be a linear function such that f(g1.x) = g1.y and f(g2.x) = g2.y.
		/// This function returns f(t).
		static float Lerp( Vector2 g1, Vector2 g2, float t );

		static float SmoothLerp( float v1, float v2, float t );
		static float FancyLerp( float t, std::vector<float> keyframes );
		static Vector2 FancyLerp( float t, std::vector<Vector2> keyframes );
		static float ParabolaInterp( float t, Vector2 apex, float zero1 );
		static float ParabolaInterp( float t, Vector2 apex, float zero1, float power );




		static Vector2 Reciprocal( Vector2 v );
		static void RotatedBasis( float Degrees, Vector2 &v );
		static void PointyAxisTo( BasePoint &Base, Vector2 dir );
		static void PointxAxisTo( BasePoint &Base, Vector2 dir );
		static void PointxAxisTo( Vector2 &e1, Vector2 &e2, Vector2 dir );
		static void PointxAxisToAngle( BasePoint &Base, float angle );
	};
}


#endif	//#ifndef COREMATH
