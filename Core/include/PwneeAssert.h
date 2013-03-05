#ifndef PWNEE_ASSERT
#define PWNEE_ASSERT

#if PC_VERSION

	#if !defined( DEBUG ) && !defined( _DEBUG )
		#define assert(x)
	#else
		#define assert(x)                                                       \
			if (!(x)) {                                                         \
				LOG.Write( "Assertion failed in \"%s\", line %d\n"				\
						  "\tProbable bug in software.\n",                      \
						  __FILE__, __LINE__ );                                 \
			}                                                                   \
			else   // This 'else' exists to catch the user's following semicolon
	#endif

#else

	#include <cassert>

#endif

#endif