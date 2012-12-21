#include <Content/File.h>

#ifdef CAFE
	#include <cafe/demo.h>
	#include <Content/File.h>
	#include <Content/Filesystem.h>
#else
	#include <fstream>
	#include <streambuf>
	#include <string>
#endif

#include <Utility/Log.h>

bool File::ReadAsString( const std::string &path, std::string &str )
{
	using namespace std;

#ifdef CAFE
	u32 length;

	boost::shared_ptr<File> file = FILESYSTEM.Open( path );
	length = file->Size();
	char *buf = new char[ length ];
	file->Read( buf, length );

	str.reserve( length );
	str.assign( buf, buf + length );
	
	delete buf;

	return true;
#else
	ifstream file( path.c_str(), ios::in );

	if( !file )
		return false;

	file.seekg( 0, ios::end );
	str.reserve( static_cast< unsigned int >( file.tellg() ) );
	file.seekg( 0, ios::beg );

	str.assign( ( istreambuf_iterator< char >( file ) ), istreambuf_iterator< char >() );
	return true;
#endif

}