#include <Content/Wad.h>

#include <Content/Texture.h>
#include <Datastructures/Freelist.h>

Wad::Wad( const std::string &base ) :
	base_( base ),
	holderAllocator_( new Freelist< ResourceHolder, 128 >() ),
	defaultTexture_( 0 )
{
	Texture *pinkX = new Texture;
	std::string path = base + "Art/default.png";
	
	pinkX->SetPath( path );
	pinkX->Load();
	pinkX->GpuCreate();

	defaultTexture_ = new ( holderAllocator_->Allocate() ) ResourceHolder( pinkX );

	resourceHolders_[ path ] = defaultTexture_;
}

Wad::~Wad()
{
	HolderMap::iterator i;
	for( i = resourceHolders_.begin(); i != resourceHolders_.end(); ++i )
	{
		Resource *resource = i->second->GetResource();
		delete resource;
	}

	delete holderAllocator_;
}

// Private.
ResourceHolder *Wad::load( const std::string &path )
{
	HolderMap::iterator i = resourceHolders_.find( path );
	if( i != resourceHolders_.end() )
		return i->second;

	Texture *texture = new Texture;
	texture->SetPath( path );
	texture->Load();
	texture->GpuCreate();

	if( !texture->IsLoaded() )
	{
		delete texture;
		return defaultTexture_;
	}

	ResourceHolder *rh = new ( holderAllocator_->Allocate() ) ResourceHolder( texture );
	resourceHolders_[ path ] = rh;

	return rh;
}
