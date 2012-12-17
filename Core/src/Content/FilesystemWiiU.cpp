#include <Content/FilesystemWiiU.h>

#include <Content/File.h>

#include <fstream>

/**
 * File implementation for Pc.
 */
class FileWiiU : public File
{
	
private:

	/// No copying.
	FileWiiU( const FileWiiU & ) { }

	/// No assignment.
	FileWiiU &operator = ( const FileWiiU & ) {	return *this; }

public:

	FileWiiU( const std::string &path, bool write )
	{
	}

	/**
	 * @see File::Read()
	 */
	size_t Read( char *buffer, size_t length )
	{
	}

	/**
	 * @see File::Write()
	 */
	size_t Write( const char *buffer, size_t length )
	{
	}

	/**
	 * @see File::ReadLine()
	 */
	std::string ReadLine()
	{
	}
	
	/**
	 * @see File::Peek()
	 */
	int Peek()
	{
	}

	/**
	 * @see File::IsOpen()
	 */
	bool IsOpen()
	{
	}

	/**
	 * @see File::EOF()
	 */
	bool IsEOF()
	{
	}

};

FilesystemWiiU::FilesystemWiiU()
{
}

boost::shared_ptr<File> FilesystemWiiU::Open( const std::string &path, bool write )
{
	return boost::static_pointer_cast<File>( boost::make_shared<FileWiiU>( path, write ) );
}
