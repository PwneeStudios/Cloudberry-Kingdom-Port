#include <Content/FilesystemVita.h>

#include <boost/make_shared.hpp>
#include <Content/File.h>
#include <sstream>
#include <stdio.h>
#include <Utility/Log.h>

/**
 * File implementation for Pc.
 */
class FileVita : public File
{

	FILE *file_;
	long size_;

private:

	/// No copying.
	FileVita( const FileVita & ) { }

	/// No assignment.
	FileVita &operator = ( const FileVita & ) {	return *this; }

public:

	FileVita( const std::string &path, bool write )
		: file_( NULL )
	{
		std::string absolutePath = "app0:/" + path;
		file_ = fopen( absolutePath.c_str(), "rb" );

		if( !file_ )
			return;

		long start = ftell( file_ );
		fseek( file_, 0, SEEK_END );
		long end = ftell( file_ );
		fseek( file_, 0, SEEK_SET );

		size_ = end - start;
	}

	~FileVita()
	{
		if( file_ )
			fclose( file_ );
	}

	/**
	 * @see File::Read()
	 */
	size_t Read( char *buffer, size_t length )
	{
		return fread( buffer, 1, length, file_ ); 
	}

	/**
	 * @see File::Write()
	 */
	size_t Write( const char *buffer, size_t length )
	{
		return fwrite( buffer, 1, length, file_ );
	}

	/**
	 * @see File::ReadLine()
	 */
	std::string ReadLine()
	{
		std::stringstream ss;

		char c = 0;
		while( !IsEOF() && ( c = static_cast< char >( fgetc( file_ ) ) ) != '\n' )
			ss << c;

		return ss.str();
	}
	
	/**
	 * @see File::Peek()
	 */
	int Peek()
	{
		long checkpoint = ftell( file_ );
		int ch = fgetc( file_ );
		fseek( file_, checkpoint, SEEK_SET );
		return ch;
	}

	/**
	 * @see File::IsOpen()
	 */
	bool IsOpen()
	{
		return file_ != NULL;
	}

	/**
	 * @see File::EOF()
	 */
	bool IsEOF()
	{
		return feof( file_ );
	}

	/**
	 * @see File::Size()
	 */
	unsigned int Size()
	{
		return size_;
	}

};

FilesystemVita::FilesystemVita()
{
}

extern std::string VITA_PATH_PREFIX;

boost::shared_ptr<File> FilesystemVita::Open( const std::string &path, bool write )
{
	std::string localPath;
	if( strncmp( path.c_str(), "ContentVita", 11 ) == 0 )
		localPath = VITA_PATH_PREFIX + path;
	else
		localPath = VITA_PATH_PREFIX + ( path[ 0 ] == '/' ? "ContentVita" : "ContentVita/" ) + path;
	LOG_WRITE( "Opening %s\n", localPath.c_str() );

	return boost::static_pointer_cast<File>( boost::make_shared<FileVita>( localPath, write ) );
}
