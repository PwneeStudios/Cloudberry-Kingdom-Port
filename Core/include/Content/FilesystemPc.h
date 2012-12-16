#ifndef _FILESYSTEM_PC_H_
#define _FILESYSTEM_PC_H_

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

// Forward declarations.
class File;

/**
 * Pc filesystem.
 */
class FilesystemPc
{

private:

	/// No copying.
	FilesystemPc( const FilesystemPc & ) { }

	/// No assignment.
	FilesystemPc &operator = ( const FilesystemPc & ) {	return *this; }

public:

	FilesystemPc();

	/**
	 * @see Filesystem::Open()
	 */
	boost::shared_ptr<File> Open( const std::string &path, bool write );

};

#endif
