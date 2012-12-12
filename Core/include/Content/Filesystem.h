#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <Architecture/Singleton.h>

#include <memory>

#ifdef CAFE
	#include "FilesystemWiiU.h"
#else
	#include "FilesystemPc.h"
#endif

// Forward declarations.
class File;

/**
 * Base filesystem.
 */
class Filesystem : public Singleton< Filesystem >
{

#ifdef CAFE
	FilesystemWiiU impl_;
#else
	FilesystemPc impl_;
#endif

private:

	/// No copying.
	Filesystem( const Filesystem & ) { }

	/// No assignment.
	Filesystem &operator = ( const Filesystem & ) {	return *this; }

public:

	Filesystem() { }

	/// Open a file for reading.
	/**
	 * @param path Path to file.
	 * @return File interface.
	 */
	std::shared_ptr<File> Open( const std::string &path )
	{
		return impl_.Open( path );
	}

	/// Get core singleton.
	static Filesystem &GetSingleton();
};

#define FILESYSTEM Filesystem::GetSingleton()

#endif
