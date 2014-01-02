#ifndef SUPER_GLOBAL_HEADER_H
#define SUPER_GLOBAL_HEADER_H

#include "enums.h"
#include "forward_declarations.h"
#include <ForwardDeclarations.h>

// System includes.
#include <algorithm>
#include <PwneeAssert.h>
#include <list>
#include <map>
#define _USE_MATH_DEFINES
#include "math.h"
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#if defined( PS3 ) || defined( VITA )
	#define _T( x ) L##x
#else
	#include <tchar.h>
#endif

#if defined( VITA )
	#define M_E 2.71828182845904523536
	#define M_LOG2E 1.44269504088896340736
	#define M_LOG10E 0.434294481903251827651
	#define M_LN2 0.693147180559945309417
	#define M_LN10 2.30258509299404568402
	#define M_PI 3.14159265358979323846
	#define M_PI_2 1.57079632679489661923
	#define M_PI_4 0.785398163397448309616
	#define M_1_PI 0.318309886183790671538
	#define M_2_PI 0.636619772367581343076
	#define M_1_SQRTPI 0.564189583547756286948
	#define M_2_SQRTPI 1.12837916709551257390
	#define M_SQRT2 1.41421356237309504880
	#define M_SQRT_2 0.707106781186547524401
#endif

// Syntactic sugar
#define MakeMagic( classname, params ) \
	boost::make_shared<classname> params -> classname##_Construct params

namespace CloudberryKingdom
{
	typedef std::vector<boost::shared_ptr<Bob> > BobVec;
	typedef std::vector<boost::shared_ptr<ObjectBase> > ObjectVec;
	typedef std::vector<boost::shared_ptr<BlockBase> > BlockVec;
	typedef std::vector<boost::shared_ptr<GameObject> > GameObjVec;
}

// Jordan's unalphebatized shit. Suck it Oleg.
inline int Sign(int x) { return (x > 0) - (x < 0); }
inline int Sign(float x) { return (x > 0) - (x < 0); }
inline int Sign(double x) { return (x > 0) - (x < 0); }

// Increment an enumeration variable by one.
template<typename E>
inline void Incr( E &e )
{
	e = static_cast<E>( static_cast<int>( e ) + 1 );
#pragma once}

struct Object
{
	virtual ~Object()
	{
	}
};

template<class T>
struct WrappedValue : public Object
{
	T MyValue;

	WrappedValue( T value ) : MyValue( value )
	{
	}
};

template<class T>
inline T Unbox( boost::shared_ptr<Object> o )
{
	return ( *boost::static_pointer_cast<WrappedValue<T> >( o ).get() ).MyValue;
}

template<class T>
inline boost::shared_ptr<Object> MakeSmartObject( T t )
{
	return boost::static_pointer_cast<Object>( boost::make_shared<WrappedValue<T> >( t ) );
}

template<class T>
inline boost::shared_ptr<Object> MakeSmartObject( boost::shared_ptr<T> ptr )
{
	return boost::static_pointer_cast<Object>( ptr );
}

#endif
