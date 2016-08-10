#ifndef _FILESYSTEM_VITA_H_
#define _FILESYSTEM_VITA_H_

#include <boost/shared_ptr.hpp>
#include <string>

// Forward declarations.
class File;

/**
 * Pc filesystem.
 */
class FilesystemVita
{

private:

	/// No copying.
	FilesystemVita( const FilesystemVita & ) { }

	/// No assignment.
	FilesystemVita &operator = ( const FilesystemVita & ) {	return *this; }

public:

	FilesystemVita();

	/**
	 * @see Filesystem::Open()
	 */
	boost::shared_ptr<File> Open( const std::string &path, bool write );

};

#endif
