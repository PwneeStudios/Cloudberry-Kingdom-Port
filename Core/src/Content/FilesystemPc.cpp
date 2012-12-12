#include <Content/FilesystemPc.h>

#include <Content/File.h>

#include <fstream>

/**
 * File implementation for Pc.
 */
class FilePc : public File
{
	
	std::fstream fs_;

private:

	/// No copying.
	FilePc( const FilePc & ) { }

	/// No assignment.
	FilePc &operator = ( const FilePc & ) {	return *this; }

public:

	FilePc( const std::string &path ) :
		fs_( path, std::ios_base::in | std::ios_base::binary )
	{
	}

	/**
	 * @see File::Read()
	 */
	size_t Read( char *buffer, size_t length )
	{
		std::streamoff start = fs_.tellg();
		fs_.read( buffer, length );
		return static_cast< size_t >( fs_.tellg() - start );
	}

	int Peek()
	{
		return fs_.peek();
	}

	bool IsOpen()
	{
		return fs_.is_open();
	}

	/**
	 * @see File::EOF()
	 */
	bool IsEOF()
	{
		return fs_.eof();
	}

};

FilesystemPc::FilesystemPc()
{
}

std::shared_ptr<File> FilesystemPc::Open( const std::string &path )
{
	return std::static_pointer_cast<File>( std::make_shared<FilePc>( path ) );
}
