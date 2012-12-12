#ifndef _FILESYSTEM_PC_H_
#define _FILESYSTEM_PC_H_

#include <memory>
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
	std::shared_ptr<File> Open( const std::string &path, bool write );

};

#endif
