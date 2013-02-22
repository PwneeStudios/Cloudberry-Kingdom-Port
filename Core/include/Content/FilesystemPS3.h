#ifndef _FILESYSTEM_PS3_H_
#define _FILESYSTEM_PS3_H_

#include <boost/shared_ptr.hpp>
#include <string>

// Forward declarations.
class File;

/**
 * Pc filesystem.
 */
class FilesystemPS3
{

private:

	/// No copying.
	FilesystemPS3( const FilesystemPS3 & ) { }

	/// No assignment.
	FilesystemPS3 &operator = ( const FilesystemPS3 & ) {	return *this; }

public:

	FilesystemPS3();

	/**
	 * @see Filesystem::Open()
	 */
	boost::shared_ptr<File> Open( const std::string &path, bool write );

};

#endif
