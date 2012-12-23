#include <Content/FilesystemPc.h>

#include <Content/File.h>

#include <fstream>

/**
 * File implementation for Pc.
 */
class FilePc : public File
{
	
	std::fstream fs_;
	unsigned int size;

private:

	/// No copying.
	FilePc( const FilePc & ) { }

	/// No assignment.
	FilePc &operator = ( const FilePc & ) {	return *this; }

public:

	FilePc( const std::string &path, bool write ) :
		fs_( path, std::ios_base::in | std::ios_base::binary
			| ( write ? std::ios_base::out | std::ios_base::trunc : 0 ) )
	{
		fs_.seekg( 0, std::ios_base::end );
		size = fs_.tellg();
		fs_.seekg( 0 );
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

	/**
	 * @see File::Write()
	 */
	size_t Write( const char *buffer, size_t length )
	{
		std::streamoff start = fs_.tellp();
		fs_.write( buffer, length );
		return static_cast< size_t >( fs_.tellp() - start );
	}

	/**
	 * @see File::ReadLine()
	 */
	std::string ReadLine()
	{
		std::string buffer;
		std::getline( fs_, buffer );
		return buffer;
	}
	
	/**
	 * @see File::Peek()
	 */
	int Peek()
	{
		return fs_.peek();
	}

	/**
	 * @see File::IsOpen()
	 */
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

	/**
	 * @see File::Size()
	 */
	unsigned int Size()
	{
		return size;
	}

};

FilesystemPc::FilesystemPc()
{
}

boost::shared_ptr<File> FilesystemPc::Open( const std::string &path, bool write )
{
	return boost::static_pointer_cast<File>( boost::make_shared<FilePc>( path, write ) );
}
