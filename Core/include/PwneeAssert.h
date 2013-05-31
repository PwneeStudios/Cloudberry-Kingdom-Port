#ifndef PWNEE_ASSERT
#define PWNEE_ASSERT

#if defined( CAFE ) || defined( PS3 ) || defined( VITA )

	#include <cassert>

#else

	#if !defined( DEBUG ) && !defined( _DEBUG )

		#define assert(x)

	#else

		#include <intrin.h>

		#undef assert
		#define assert(x)                                                       \
			if (!(x)) {                                                         \
				__debugbreak();													\
			}                                                                   \
			else   // This 'else' exists to catch the user's following semicolon

	#endif
	
#endif

#endif