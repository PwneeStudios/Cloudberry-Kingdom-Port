#ifndef _LIMITS_H_
#define _LIMITS_H_

#ifndef __max
#define __max( a, b )  ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#endif

#ifndef __min
#define __min( a, b )  ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#endif

#ifndef FLT_MIN
#define FLT_MIN         1.175494351e-38F        /* min positive value */
#endif

#ifndef FLT_MAX
#define FLT_MAX         3.402823466e+38F        /* max value */
#endif

#endif
