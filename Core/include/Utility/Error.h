#ifndef _ERROR_H_
#define _ERROR_H_

#ifdef CAFE
#include <cafe.h>
typedef s32 ErrorType;
#else
typedef unsigned int ErrorType;
#endif

/// Display a system error.
/**
 * @param errorCode Current error code.
 */
void DisplayError( ErrorType errorCode );

#endif