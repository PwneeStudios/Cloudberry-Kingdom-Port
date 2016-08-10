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
#include <set>
#include <string>

/**
 * Loader/manager for game content.
 */
class Wad
{

	/// Map between resource names and their holders.
	typedef std::map< std::string, ResourceHolder * > HolderMap;

	/// Set of resources.
	typedef std::set< Resource * > ResourceSet;

	/// Layer of indirection for all resources.
	HolderMap resourceHolders_;

	/// Base resource path.
	std::string base_;

	/// Fast allocator for resource holders.
	Freelist< ResourceHolder, 2048 > *holderAllocator_;

	/// Texture used in place of missing textures.
	ResourceHolder *defaultTexture_;

	/// Unique resource set.
	ResourceSet uniqueResources_;

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

	ResourcePtr< Texture > ForceLoadTexture( const std::string &name );

private:

	/// Load a resource.
	/**
	 * @param path Resource path.
	 * @return Pointer to resource holder object.
	 */
	ResourceHolder *load( const std::string &path );

	/// Load a font file.
	/**
	 * @param path Font path.
	 * @return Pointer to font resource.
	 */
	ResourceHolder *loadFont( const std::string &path );

};

// Specialization for loading Fonts.
template<>
inline ResourcePtr< Font > Wad::Load< Font >( const std::string name )
{
	return ResourcePtr< Font >( loadFont( base_ + name ) );
}

#endif
