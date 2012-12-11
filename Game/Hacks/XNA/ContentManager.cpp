#include <global_header.h>

#include "ContentManager.h"
#include "GraphicsDevice.h"

template<> std::shared_ptr<SoundEffect> ContentManager::Load<SoundEffect>( const std::wstring &name )
{
	return std::make_shared<SoundEffect>();
}

template<> std::shared_ptr<Song> ContentManager::Load<Song>( const std::wstring &name )
{
	return std::make_shared<Song>();
}

template<> std::shared_ptr<Texture2D> ContentManager::Load<Texture2D>( const std::wstring &name )
{
	return std::make_shared<Texture2D>(std::shared_ptr<GraphicsDevice>(), 1, 1);
}

template<> std::shared_ptr<SpriteFont> ContentManager::Load<SpriteFont>( const std::wstring &name )
{
	return std::make_shared<SpriteFont>();
}

template<> std::shared_ptr<Effect> ContentManager::Load<Effect>( const std::wstring &name )
{
	return std::make_shared<Effect>();
}

