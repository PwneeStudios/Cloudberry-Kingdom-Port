#ifndef _TROPHY_VITA_H_
#define _TROPHY_VITA_H_

#include <np.h>

/// Get access to the trophy system.
/**
 * @param context Trophy system context.
 * @param handle Trophy system handle.
 * @return True if the context and handle are valid, false otherwise.
 */
bool GetTrophyContext( SceNpTrophyContext &context, SceNpTrophyHandle &handle );

#endif
