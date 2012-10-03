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

	/// Texture used in place of missing textures.
	Texture *defaultTexture_;

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
		ResourceHolder rh( load( base_ + name ) );
		return ResourcePtr< ResourceType >( rh );
	}
	
private:

	/// Load a resource.
	/**
	 * @param path Resource path.
	 * @return Pointer to resource object.
	 */
	Resource *load( const std::string &path );

};

#endif
