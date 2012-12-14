#include <global_header.h>

#include <Hacks\String.h>
#include <Hacks\List.h>

namespace CloudberryKingdom
{

	int CoreMath::Modulo( int n, int p )
	{
		int M = n % p;
		if ( M < 0 )
			M += p;
		return M;
	}

	float CoreMath::Modulo( float n, float p )
	{
		float M = n - static_cast<int>( n / p ) * p;
		if ( M < 0 )
			M += p;
		return M;
	}

	float CoreMath::ZigZag( float period, float t )
	{
		float p = period / 2;
		int n = static_cast<int>( floor( t / p ) );
		t -= n * p;
		if ( n % 2 == 0 )
			return t / p;
		else
			return 1 - t / p;
	}

	float CoreMath::PeriodicCentered( float A, float B, float period, float t )
	{
		float Normalized = .5f + .5f * static_cast<float>( sin( t * 2 * M_PI / period ) );
		return A + ( B - A ) * Normalized;
	}

	float CoreMath::Periodic( float A, float B, float period, float t )
	{
		return Periodic( A, B, period, t, 0 );
	}

	float CoreMath::Periodic( float A, float B, float period, float t, float PhaseDegree )
	{
		float Normalized = .5f - .5f * static_cast<float>( cos( t * 2 * M_PI / period + CoreMath::Radians( PhaseDegree ) ) );
		return A + ( B - A ) * Normalized;
	}

	Vector2 CoreMath::Periodic( Vector2 A, Vector2 B, float period, float t )
	{
		float Normalized = .5f - .5f * static_cast<float>( cos( t * 2 * M_PI / period ) );
		return A + ( B - A ) * Normalized;
	}

	std::wstring CoreMath::Time( int frames )
	{
		int h = Hours( frames );
		int m = Minutes( frames );
		int s = Seconds( frames );
		int mi = Milliseconds( frames );

		//return string.Format("{0:0}h:{1:00}m:{2:00}.{3:00}", h, m, s, mi);
		//return Format( _T( "{0:0}:{1:00}:{2:00}.{3:00}" ), h, m, s, mi );
		return Format( _T( "%d:%02d:%02d.%03d" ), h, m, s, mi );
	}

	std::wstring CoreMath::ShortTime( int frames )
	{
		int h = Hours( frames );
		int m = Minutes( frames );
		int s = Seconds( frames );
		int mi = Milliseconds( frames );

		if ( h > 0 )
			return Format( _T( "%d:%02d:%02d.%03d" ), h, m, s, mi );
		else if ( m > 0 )
			return Format( _T( "%d:%02d" ), m, s );
		else if ( s > 10 )
			return Format( _T( "%d.%d" ), s, mi / 10 );
		else
			return Format( _T( "%d.%02d" ), s, mi );
	}

	int CoreMath::Hours( int frames )
	{
		return static_cast<int>( frames / ( 60 * 60 * 62 ) );
	}

	int CoreMath::Minutes( int frames )
	{
		float Remainder = frames - 60.f * 60 * 62 * Hours( frames );
		return static_cast<int>( Remainder / ( 60 * 62 ) );
	}

	int CoreMath::Seconds( int frames )
	{
		float Remainder = frames - 60.f * 60 * 62 * Hours( frames ) - 60 * 62 * Minutes( frames );
		return static_cast<int>( Remainder / 62 );
	}

	int CoreMath::Milliseconds( int frames )
	{
		float Remainder = frames - 60.f * 60 * 62 * Hours( frames ) - 60 * 62 * Minutes( frames ) - 62 * Seconds( frames );
		return static_cast<int>( 100 * Remainder / 62 );
	}

	float CoreMath::Degrees( float Radians )
	{
		return static_cast<float>( Radians * 180 / M_PI );
	}

	float CoreMath::Radians( float Degrees )
	{
		return static_cast<float>( Degrees * M_PI / 180 );
	}

float CoreMath::c = 180 / static_cast<float>( M_PI );

	float CoreMath::RadianDist( float a1, float a2 )
	{
		return AngleDist( c * a1, c * a2 );
	}

	float CoreMath::AngleDist( float a1, float a2 )
	{
		float dist = abs( a1 - a2 );
		dist = fmod( dist, 360.f );
		return __min( dist, 360 - dist );
	}

	float CoreMath::VectorToAngle( Vector2 v )
	{
		return static_cast<float>( atan2( v.Y, v.X ) );
	}

	Vector2 CoreMath::CartesianToPolar( Vector2 v )
	{
		Vector2 polar = Vector2( VectorToAngle( v ), polar.Y = v.Length() );
		return polar;
	}

	Vector2 CoreMath::PolarToCartesian( Vector2 v )
	{
		return v.Y * AngleToDir( v.X );
	}

	Vector2 CoreMath::AngleToDir( double Angle )
	{
		return Vector2( static_cast<float>( cos( Angle ) ), static_cast<float>( sin( Angle ) ) );
	}

	Vector2 CoreMath::DegreesToDir( double Angle )
	{
		return AngleToDir( M_PI / 180 * Angle );
	}

	float CoreMath::Snap( float x, float spacing )
	{
		return spacing * static_cast<int>( x / spacing );
	}

	Vector2 CoreMath::Snap( Vector2 x, Vector2 spacing )
	{
		return Vector2( Snap( x.X, spacing.X ), Snap( x.Y, spacing.Y ) );
	}

	float CoreMath::SupNorm( Vector2 v )
	{
		return __max( abs( v.X ), abs( v.Y ) );
	}

	Vector2 CoreMath::Sign( Vector2 v )
	{
		return Vector2( static_cast<float>( ::Sign( v.X ) ), static_cast<float>( ::Sign( v.Y ) ) );
	}

	/*float CoreMath::Max( ... )
	{
		float max = vals[ 0 ];
		for ( int i = 1; i < vals->Length; i++ )
			max = __max( max, vals[ i ] );
		return max;
	}*/

	void CoreMath::MaxAndMin( Vector2 &p1, Vector2 &p2, Vector2 &Max, Vector2 &Min )
	{
		if ( p1.X > p2.X )
		{
			Max.X = p1.X;
			Min.X = p2.X;
		}
		else
		{
			Max.X = p2.X;
			Min.X = p1.X;
		}

		if ( p1.Y > p2.Y )
		{
			Max.Y = p1.Y;
			Min.Y = p2.Y;
		}
		else
		{
			Max.Y = p2.Y;
			Min.Y = p1.Y;
		}
	}

	Vector2 CoreMath::Abs( Vector2 v )
	{
		return Vector2( abs( v.X ), abs( v.Y ) );
	}

	bool CoreMath::Close( Vector2 v1, Vector2 v2, Vector2 Cutoff )
	{
		if ( v1.X > v2.X + Cutoff.X )
			return false;
		if ( v1.X < v2.X - Cutoff.X )
			return false;
		if ( v1.Y > v2.Y + Cutoff.Y )
			return false;
		if ( v1.Y < v2.Y - Cutoff.Y )
			return false;
		return true;
	}

	Vector2 CoreMath::Restrict( float min, float max, Vector2 val )
	{
		val.X = RestrictVal( min, max, val.X );
		val.Y = RestrictVal( min, max, val.Y );

		return val;
	}

	float CoreMath::RestrictVal( float min, float max, float val )
	{
		if ( val > max )
			val = max;
		if ( val < min )
			val = min;

		return val;
	}

	void CoreMath::Restrict( float min, float max, float &val )
	{
		val = RestrictVal( min, max, val );
	}

	int CoreMath::RestrictVal( int min, int max, int val )
	{
		if ( val > max )
			val = max;
		if ( val < min )
			val = min;

		return val;
	}

	void CoreMath::Restrict( int min, int max, int &val )
	{
		val = RestrictVal( min, max, val );
	}

	float CoreMath::MultiLerpRestrict( float t, const std::vector<float> &values )
	{
		if ( t <= 0 )
			return values[ 0 ];
		if ( t >= values.size() - 1 )
			return values[ values.size() - 1 ];

		int i1 = std::min( static_cast<int>( t ), static_cast<int>( values.size() ) - 1 );
		int i2 = i1 + 1;

		return Lerp( values[ i1 ], values[ i2 ], t - i1 );
	}

	Vector2 CoreMath::MultiLerpRestrict( float t, const std::vector<Vector2> &values )
	{
		if ( t <= 0 )
			return values[ 0 ];
		if ( t >= values.size() - 1 )
			return values[ values.size() - 1 ];

		int i1 = std::min( static_cast<int>( t ), static_cast<int>( values.size() ) - 1 );
		int i2 = i1 + 1;

		return Vector2::Lerp( values[ i1 ], values[ i2 ], t - i1 );
	}

	int CoreMath::LerpRestrict( int v1, int v2, float t )
	{
		return static_cast<int>( LerpRestrict( static_cast<float>( v1 ), static_cast<float>( v2 ), t ) );
	}

	int CoreMath::Lerp( int v1, int v2, float t )
	{
		return static_cast<int>( Lerp( static_cast<float>( v1 ), static_cast<float>( v2 ), t ) );
	}

	float CoreMath::LerpRestrict( float v1, float v2, float t )
	{
		return Lerp( v1, v2, CoreMath::RestrictVal( 0.f, 1.f, t ) );
	}

	float CoreMath::Lerp( float v1, float v2, float t )
	{
		return ( 1 - t ) * v1 + t * v2;
	}

	Vector2 CoreMath::LerpRestrict( Vector2 v1, Vector2 v2, float t )
	{
		if ( t > 1 )
			return v2;
		if ( t < 0 )
			return v1;
		return Vector2::Lerp( v1, v2, t );
	}

	float CoreMath::SpecialLerp( float v1, float v2, float t )
	{
		if ( v1 == 0 )
			t = static_cast<float>( __max( 0, t - .5 ) );

		return ( 1 - t ) * v1 + t * v2;
	}

	float CoreMath::SpecialLerpRestrict( float v1, float v2, float t )
	{
		return SpecialLerp( v1, v2, CoreMath::RestrictVal( 0.f, 1.f, t ) );
	}

	float CoreMath::Lerp( Vector2 g1, Vector2 g2, float t )
	{
		float width = g2.X - g1.X;
		float s = ( t - g1.X ) / width;

		return g2.Y * s + g1.Y * ( 1 - s );
	}

	float CoreMath::SmoothLerp( float v1, float v2, float t )
	{
		float tempVector[] = { CoreMath::Lerp( v1, v2, 0 ), CoreMath::Lerp( v1, v2, 0.5f ), CoreMath::Lerp( v1, v2, 0.75f ), CoreMath::Lerp( v1, v2, 0.875f ), CoreMath::Lerp( v1, v2, 0.9375f ), CoreMath::Lerp( v1, v2, 1 ) };
		return FancyLerp( t, std::vector<float>( VecFromArray( tempVector ) ) );
	}

	float CoreMath::FancyLerp( float t, std::vector<float> keyframes )
	{
		if ( t >= 1 )
			return keyframes[ keyframes.size() - 1 ];
		if ( t <= 0 )
			return keyframes[ 0 ];

		float _t = keyframes.size() * t;
		int frame = static_cast<int>( _t );

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		float v1 = frame > 0 ? keyframes[ frame - 1 ] : keyframes[ 0 ];
		float v2 = keyframes[ frame ];
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		float v3 = ( frame + 1 ) < static_cast<int>( keyframes.size() ) ? keyframes[ frame + 1 ] : keyframes[ keyframes.size() - 1 ];
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		float v4 = ( frame + 2 ) < static_cast<int>( keyframes.size() ) ? keyframes[ frame + 2 ] : keyframes[ keyframes.size() - 1 ];

		//return Vector2.CatmullRom(v1, v2, v3, v4, _t - frame);
		//return Vector2.Hermite(v2, v2 - v1, v3, v4 - v3, _t - frame);
		return Lerp( v2, v3, _t - frame );
	}

	Vector2 CoreMath::FancyLerp( float t, std::vector<Vector2> keyframes )
	{
		if ( t >= 1 )
			return keyframes[ keyframes.size() - 1 ];
		if ( t <= 0 )
			return keyframes[ 0 ];

		float _t = keyframes.size() * t;
		int frame = static_cast<int>( _t );

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		Vector2 v1 = ( frame > 0 ) ? keyframes[ frame - 1 ] : keyframes[ 0 ];
		Vector2 v2 = keyframes[ frame ];
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		Vector2 v3 = ( frame + 1 ) < static_cast<int>( keyframes.size() ) ? keyframes[ frame + 1 ] : keyframes[ keyframes.size() - 1 ];
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		Vector2 v4 = ( frame + 2 ) < static_cast<int>( keyframes.size() ) ? keyframes[ frame + 2 ] : keyframes[ keyframes.size() - 1 ];

		//return Vector2.CatmullRom(v1, v2, v3, v4, _t - frame);
		//return Vector2.Hermite(v2, v2 - v1, v3, v4 - v3, _t - frame);
		return Vector2::Lerp( v2, v3, _t - frame );
	}

	float CoreMath::ParabolaInterp( float t, Vector2 apex, float zero1 )
	{
		float q = static_cast<float>( pow( zero1 - apex.X, 2 ) );
		return apex.Y * static_cast<float>( q - pow( t - apex.X, 2 ) ) / q;
	}

	float CoreMath::ParabolaInterp( float t, Vector2 apex, float zero1, float power )
	{
		float q = static_cast<float>( pow( abs( zero1 - apex.X ), power ) );
		return apex.Y * static_cast<float>( q - pow( abs( t - apex.X ), power ) ) / q;
	}

	Vector2 CoreMath::Reciprocal( Vector2 v )
	{
		return Vector2( v.Y, -v.X );
	}

	void CoreMath::RotatedBasis( float Degrees, Vector2 &v )
	{
		Vector2 e1 = CoreMath::DegreesToDir( Degrees );
		Vector2 e2 = CoreMath::DegreesToDir( Degrees + 90 );

		v = v.X * e1 + v.Y * e2;
	}

	void CoreMath::PointyAxisTo( BasePoint &Base, Vector2 dir )
	{
		PointxAxisTo( Base, Reciprocal( dir ) );
	}

	void CoreMath::PointxAxisTo( BasePoint &Base, Vector2 dir )
	{
		PointxAxisTo( Base.e1, Base.e2, dir );
	}

	void CoreMath::PointxAxisTo( Vector2 &e1, Vector2 &e2, Vector2 dir )
	{
		if ( dir.Length() < .0001f )
			return;

		dir.Normalize();

		float l = e1.Length();
		e1 = dir * l;

		l = e2.Length();
		e2.X = -e1.Y;
		e2.Y = e1.X;
		e2.Normalize();
		e2 *= l;
	}

	void CoreMath::PointxAxisToAngle( BasePoint &Base, float angle )
	{
		PointxAxisTo( Base, CoreMath::AngleToDir( angle ) );
	}
}
