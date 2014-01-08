#ifndef _RATINGS_H_
#define _RATINGS_H_

#ifdef PS3

//#define ESRB	// (America)
//#define PEGI  // (Europe, but not UK)
//#define USK   // (UK)
//#define OFLC	// (Australia)
#define CERO

#ifdef ESRB
	#define ONLINE_AGE_CUTOFF 13 // ESRB (America)
#elif defined( PEGI )
	#define ONLINE_AGE_CUTOFF 7  // PEGI (Europe, but not UK)
#elif defined( USK )
	#define ONLINE_AGE_CUTOFF 6  // USK  (UK)
#elif defined( OFLC )
	#define ONLINE_AGE_CUTOFF 0  // OFLC (Australia)
#elif defined( CERO )
	#define ONLINE_AGE_CUTOFF 0  // Japan
#else
	// Nothing. This will cause a compile error because ONLINE_AGE_CUTOFF is not defined.
#endif

#endif

#endif