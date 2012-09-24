#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <cassert>

/**
 * Base class for things there should only be one of.
 */
template< class T >
class Singleton
{

private:

	/// No copying.
	Singleton( const Singleton< T > & ) { }

	/// No assignment.
	Singleton &operator = ( const Singleton< T > & ) { }

protected:

	/// Pointer to the singleton instance.
	static T *singleton_;

public:

	Singleton()
	{
		assert( !singleton_ );
		singleton_ = static_cast< T * >( this );
	}

	~Singleton()
	{
		assert( singleton_ );
		singleton_ = 0;
	}

	static T &GetSingleton()
	{
		assert( singleton_ );
		return *singleton_;
	}

};

#endif
