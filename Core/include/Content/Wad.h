/**
 * @file
 *
 * Where's all the data?
 */
#ifndef _WAD_H_
#define _WAD_H_

#include <ForwardDeclarations.h>
#include "ResourcePtr.h"
#include <string>

/**
 * Loader/manager for game content.
 */
class Wad
{

	/// Base resource path.
	std::string base_;

public:
	
	/// Construct a new wad.
	/**
	 * @param base Root directory for this collection.
	 */
	Wad( const std::string &base );

	template< class ResourceType >
	ResourcePtr< ResourceType > Load( const std::string name )
	{
		return ResourcePtr< ResourceType >();
	}

};

#endif
