#include <Content/Wad.h>

#include <Architecture/Scheduler.h>
#include <Content/Texture.h>
#include <Core.h>
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
	uniqueResources_.insert( pinkX );
}

Wad::~Wad()
{
	ResourceSet::iterator i;
	for( i = uniqueResources_.begin(); i != uniqueResources_.end(); ++i )
		delete *i;

	delete holderAllocator_;
}

// Private.
ResourceHolder *Wad::load( const std::string &path )
{
	HolderMap::iterator i = resourceHolders_.find( path );
	if( i != resourceHolders_.end() )
		return i->second;

	ResourceHolder *rh = new ( holderAllocator_->Allocate() ) ResourceHolder( *defaultTexture_ );
	
	// Kick off a loader job.
	Texture *texture = new Texture;
	texture->SetPath( path );
	SCHEDULER->CreateResource( rh, texture );

	resourceHolders_[ path ] = rh;
	uniqueResources_.insert( texture );

	return rh;
}
