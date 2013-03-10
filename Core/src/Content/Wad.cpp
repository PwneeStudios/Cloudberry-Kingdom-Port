#include <Content/Wad.h>

#include <Architecture/Scheduler.h>
#include <Content/Font.h>
#include <Content/Texture.h>
#include <Core.h>
#include <Datastructures/Freelist.h>
#include <Utility/Log.h>

Wad::Wad( const std::string &base ) :
	base_( base ),
	holderAllocator_( new Freelist< ResourceHolder, 2048 >() ),
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
	resourceHolders_.clear();

	ResourceSet::iterator i;
	for( i = uniqueResources_.begin(); i != uniqueResources_.end(); ++i )
		delete *i;
	uniqueResources_.clear();

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

// Private.
ResourceHolder *Wad::loadFont( const std::string &path )
{
	HolderMap::iterator i = resourceHolders_.find( path );
	if( i != resourceHolders_.end() )
		return i->second;

	Font *font = new Font;
	ResourceHolder *rh = new ( holderAllocator_->Allocate() ) ResourceHolder( font );

	font->SetPath( path );
	font->Load();

	resourceHolders_[ path ] = rh;
	uniqueResources_.insert( font );

	return rh;
}
