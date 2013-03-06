#include <global_header.h>

#include <Audio/SoundEffect.h>
#include <Audio/Song.h>
#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Core.h>
#include <Graphics/Effect.h>

#include "ContentManager.h"
#include "GraphicsDevice.h"

#include <Hacks/String.h>
#include <Utility/Log.h>

void DebugFrame(float r, float g, float b);

template<> boost::shared_ptr<SoundEffect> ContentManager::Load<SoundEffect>( const std::wstring &name )
{
	DebugFrame(1, 0, 0);
	boost::shared_ptr<SoundEffect> sound = boost::make_shared<SoundEffect>();
	sound->Load( WstringToUtf8( name ) );
	return sound;
}

template<> boost::shared_ptr<Song> ContentManager::Load<Song>( const std::wstring &name )
{
	DebugFrame(0, 1, 0);
	LOG.Write( "Loading song %s\n", WstringToUtf8( name ).c_str() );
	boost::shared_ptr<Song> song = boost::make_shared<Song>();
	song->Load( WstringToUtf8( name ) );
	return song;
}

template<> boost::shared_ptr<Texture2D> ContentManager::Load<Texture2D>( const std::wstring &name )
{
	boost::shared_ptr<Texture2D> t2d = boost::make_shared<Texture2D>(boost::shared_ptr<GraphicsDevice>(), 1, 1);
	DebugFrame(0, 0, 1);
#if defined(DEBUG)
	//t2d->texture_ = CONTENT->Load<Texture>( "Art/default.png" ); // WARNING: Fast load
	t2d->texture_ = CONTENT->Load<Texture>( WstringToUtf8( name ) + ".png" );
#else
	//t2d->texture_ = CONTENT->Load<Texture>( "Art/default.png" ); // WARNING: Fast load
	t2d->texture_ = CONTENT->Load<Texture>( WstringToUtf8( name ) + ".png" );
#endif

	return t2d;
}

template<> boost::shared_ptr<SpriteFont> ContentManager::Load<SpriteFont>( const std::wstring &name )
{
	DebugFrame(1, 1, 0);
	return boost::make_shared<SpriteFont>( WstringToUtf8( name ) );
}

template<> boost::shared_ptr<Effect> ContentManager::Load<Effect>( const std::wstring &name )
{
	DebugFrame(0, 1, 1);
	LOG.Write( "Loading effect: %s\n", WstringToUtf8( name ).c_str() );
	boost::shared_ptr<Effect> effect = boost::make_shared<Effect>();
	effect->Load( WstringToUtf8( name ) );
	return effect;
}

