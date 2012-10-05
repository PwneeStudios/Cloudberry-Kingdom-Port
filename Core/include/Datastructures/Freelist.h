/**
 * @file
 *
 * Freelist data structure.
 */
#ifndef _FREELIST_H_
#define _FREELIST_H_

#include <cassert>
#include <list>
#include <vector>

template< class T, unsigned int N >
class Freelist
{

	/// Heap from which all objects are allocated.
	T *heap_;

	/// Stack of free objects.
	T **stack_;

	/// Top of stack.
	unsigned int top_;

public:

	Freelist() :
		heap_( new T[ N ] ),
		stack_( new T *[ N ] ),
		top_( 0 )
	{
		freeAll();
	}

	~Freelist()
	{
		delete[] stack_;
		delete[] heap_;
	}

	T *Allocate()
	{
		assert( top_ < N );

		return stack_[ top_++ ];
	}

	void Free( T *block )
	{
		assert( top_ > 0 && top_ <= N );
		assert( block >= &heap_[ 0 ] && block < &heap_[ N ] );

		stack_[ --top_ ] = block;
	}

private:

	void freeAll()
	{
		for( unsigned int i = 0; i < N; ++i )
			stack_[ i ] = &heap_[ i ];

		top_ = 0;
	}
};

#endif
