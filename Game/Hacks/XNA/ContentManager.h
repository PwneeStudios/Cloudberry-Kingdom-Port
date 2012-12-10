#ifndef _CONTENTMANAGER_H_
#define _CONTENTMANAGER_H_

#include "Hacks/XNA/GameServiceContainer.h"

struct ContentManager
{



	ContentManager( const std::wstring &ContentRootDirectory ) :
		RootDirectory( ContentRootDirectory )
	{
	}

	ContentManager( const std::shared_ptr<GameServiceContainer> &container, const std::wstring &root ) :
		RootDirectory( root )
	{
	}

	template<class T>
	std::shared_ptr<T> Load( const std::wstring &name )
	{
		// FIXME
		return std::shared_ptr<T>();
	}

	void Unload(  )
	{
		// FIXME
	}

	// FIXME: set equal to something
	std::wstring RootDirectory;

};

#endif
