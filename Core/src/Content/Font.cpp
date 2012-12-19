#include <Content/Font.h>

#include <algorithm>
#include <Content/File.h>
#include <sstream>
#include <string>

static std::istream& safeGetline( std::istream& is, std::string &t )
{
    t.clear();

    std::istream::sentry se( is, true );
    std::streambuf *sb = is.rdbuf();

    for(;;)
	{
        int c = sb->sbumpc();
        switch (c) {
        case '\r':
            c = sb->sgetc();
            if( c == '\n' )
                sb->sbumpc();
            return is;
        case '\n':
        case EOF:
            return is;
        default:
            t += ( char )c;
        }
    }
}

Font::Font() :
	charSpacing_( 0 )
{
}

void Font::Load()
{
	using namespace std;

	string fileContents;
	if( !File::ReadAsString( GetPath(), fileContents ) )
	{
		setLoaded( false );
		return;
	}

	stringstream ss( fileContents );
	string line;
	
	safeGetline( ss, texturePath_ );

	int lineSpacing;
	ss >> charSpacing_;
	ss.get();
	ss >> lineSpacing;

	int width, height;
	ss >> width;
	ss.get();
	ss >> height;

	memset( quads_, 0, sizeof( quads_ ) );
	memset( dimensions_, 0, sizeof( dimensions_ ) );

	for( char c = ' '; c <= '~'; ++c )
	{
		int x, y, w, h;
		ss >> x;
		ss.get();
		ss >> y;
		ss.get();
		ss >> w;
		ss.get();
		ss >> h;

		dimensions_[ c ] = Vector2(
			static_cast< float >( w ),
			static_cast< float >( h )
		);

		float fx = static_cast< float >( x ) / width;
		float fy = static_cast< float >( y ) / height;
		float fw = dimensions_[ c ].x() / width;
		float fh = dimensions_[ c ].y() / height;

		quads_[ c ] = Vector4( fx, fy, fw, fh );
	}

	setLoaded( true );
}

void Font::Unload()
{
	setLoaded( false );
}