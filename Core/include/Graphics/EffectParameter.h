#ifndef _EFFECTPARAMETERS_H_
#define _EFFECTPARAMETERS_H_

#include <Math/Vectors.h>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

class EffectParameter
{

	struct EffectParameterInternal *internal_;

public:

	EffectParameter( unsigned int progId, int id );
	~EffectParameter();

	void SetValue( const Vector4 &v );
	void SetValue( const Matrix &m );
	void SetValue( const boost::shared_ptr<struct Texture2D> &t );
	void SetValue( const Vector2 &v );
	void SetValue( float v );
	void SetValue( int v );
	float GetValueSingle();

};

#endif
