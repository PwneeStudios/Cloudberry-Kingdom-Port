#ifndef _FILESYSTEM_WIIU_H_
#define _FILESYSTEM_WIIU_H_

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

// Forward declarations.
class File;

/**
 * WiiU filesystem.
 */
class FilesystemWiiU
{

private:

	/// No copying.
	FilesystemWiiU( const FilesystemWiiU & ) { }

	/// No assignment.
	FilesystemWiiU &operator = ( const FilesystemWiiU & ) {	return *this; }

public:

	FilesystemWiiU();

	/**
	 * @see Filesystem::Open()
	 */
	boost::shared_ptr<File> Open( const std::string &path, bool write );

};

#endif
