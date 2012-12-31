#ifndef _VECTORS_H_
#define _VECTORS_H_

/**
 * 2-vector.
 */
class Vector2
{

public:

	float X;
	float Y;

	Vector2();
	Vector2( const Vector2 &other );
	Vector2( float x, float y );
	explicit Vector2( float x );

	float x() const;
	float y() const;

	float LengthSquared() const;
	
	float Length() const;

	void Normalize();
	void FastNormalize();

	Vector2 Normalized() const;
	Vector2 FastNormalized() const;

	static Vector2 CatmullRom(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, float t);

	static float Distance( const Vector2 &a, const Vector2 &b );

	static float Dot( const Vector2 &a, const Vector2 &b );

	static Vector2 Min( const Vector2 &a, const Vector2 &b );

	static Vector2 Max( const Vector2 &a, const Vector2 &b );

    /// <summary>
    /// Whether the vector is less than or equal to another vector in both components
    /// </summary>
    bool LE(Vector2 a);

	/// <summary>
    /// Whether the vector is greater than or equal to another vector in both components
    /// </summary>
    bool GE(Vector2 a);

	Vector2 &operator += ( const Vector2 &a );

	Vector2 &operator -= ( const Vector2 &a );

	Vector2 &operator *= ( float k );

	Vector2 &operator *= ( const Vector2 &a );

	Vector2 &operator /= ( float k );

	Vector2 operator / ( const Vector2 &a );

	Vector2 operator + ( const Vector2 &a ) const;

	Vector2 operator * ( float k ) const;

	Vector2 operator * ( const Vector2 &a );

	Vector2 operator - ( const Vector2 &a ) const;

	Vector2 operator / ( float k ) const;

	Vector2 operator / ( const Vector2 &a ) const;

	bool operator == ( const Vector2 &a ) const;

	bool operator != ( const Vector2 &a ) const;

	static Vector2 Lerp( const Vector2 &a, const Vector2 &b, float t );

};

inline Vector2 operator * ( float k, const Vector2 &a )
{
	return a * k;
}

class Vector3
{

public:

	float X;
	float Y;
	float Z;

	Vector3();
	Vector3( const Vector3 &other );
	Vector3( float x, float y, float z );
	explicit Vector3( float x );

	static Vector3 Lerp( const Vector3 &v1, const Vector3 &v2, float t );

	static Vector3 CatmullRom(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4, float t);

	Vector3 operator + ( const Vector3 &a ) const;

	Vector3 operator * ( float k ) const;

};

inline Vector3 operator * ( float k, const Vector3 &a )
{
	return a * k;
}

class Vector4
{

public:

	float X;
	float Y;
	float Z;
	float W;

	Vector4();
	Vector4( const Vector4 &other);
	explicit Vector4( float x );
	Vector4( float x, float y, float z, float w );

	float x() const;
	float y() const;
	float z() const;
	float w() const;

	float r() const;
	float g() const;
	float b() const;
	float a() const;

	static Vector4 Lerp( const Vector4 &a, const Vector4 &b, float t );

	Vector4 operator + ( const Vector4 &a ) const;

	Vector4 operator - ( const Vector4 &a ) const;

	Vector4 operator * ( const Vector4 &a ) const;

	Vector4 operator * ( float k ) const;

	Vector4 &operator *= ( const Vector4 &a );

	Vector4 &operator *= ( float k );

	Vector4 &operator += ( const Vector4 &a );

	bool operator == ( const Vector4 &a ) const;

	bool operator != ( const Vector4 &a ) const;

};

inline Vector4 operator * ( float k, const Vector4 &a )
{
	return a * k;
}


class Matrix
{

public:

	union
	{
		struct
		{
			float M11, M12, M13, M14;
			float M21, M22, M23, M24;
			float M31, M32, M33, M34;
			float M41, M42, M43, M44;
		};

		float M[16];
	};

	Matrix();

	// FIXME: Might need to transpose this.
	Matrix( float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44 );

	static Matrix Identity();

	static Matrix CreateScale( float x, float y, float z );

	const Matrix operator * ( float s ) const;

	const Matrix operator + ( const Matrix &m ) const;

	const Matrix operator * ( const Matrix &m ) const;

};

const Matrix operator * ( float s, const Matrix &m );

#endif
