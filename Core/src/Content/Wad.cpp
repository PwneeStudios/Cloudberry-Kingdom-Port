#include <Content/Wad.h>

#include <Content/Texture.h>

Wad::Wad( const std::string &base ) :
	base_( base ),
	defaultTexture_( new Texture )
{
	defaultTexture_->SetPath( base + "Art/default.png" );
	defaultTexture_->Load();
	defaultTexture_->GpuCreate();
}

Wad::~Wad()
{
	delete defaultTexture_;
}

// Private.
Resource *Wad::load( const std::string &path )
{
	return defaultTexture_;
}
