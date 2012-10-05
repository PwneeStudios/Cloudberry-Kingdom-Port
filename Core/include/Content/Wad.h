/**
 * @file
 *
 * Where's all the data?
 */
#ifndef _WAD_H_
#define _WAD_H_

#include <ForwardDeclarations.h>
#include <map>
#include "ResourcePtr.h"
#include <string>

/**
 * Loader/manager for game content.
 */
class Wad
{

	/// Map between resource names and their holders.
	typedef std::map< std::string, ResourceHolder * > HolderMap;

	/// Layer of indirection for all resources.
	HolderMap resourceHolders_;

	/// Base resource path.
	std::string base_;

	/// Fast allocator for resource holders.
	Freelist< ResourceHolder, 128 > *holderAllocator_;

	/// Texture used in place of missing textures.
	ResourceHolder *defaultTexture_;

public:
	
	/// Construct a new wad.
	/**
	 * @param base Root directory for this collection.
	 */
	Wad( const std::string &base );
	~Wad();

	template< class ResourceType >
	ResourcePtr< ResourceType > Load( const std::string name )
	{
		return ResourcePtr< ResourceType >( load( base_ + name ) );
	}
	
private:

	/// Load a resource.
	/**
	 * @param path Resource path.
	 * @return Pointer to resource holder object.
	 */
	ResourceHolder *load( const std::string &path );

};

#endif
