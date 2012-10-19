#include <Content/Font.h>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>

void Font::Load()
{
	using namespace std;

	ifstream file( GetPath().c_str() );

	if( !file )
	{
		setLoaded( false );
		return;
	}

	stringstream ss;
	string line;
	
	getline( file, texturePath_ );

	getline( file, line );
	ss.str( line );
	int charSpacing, lineSpacing;
	ss >> charSpacing;
	ss.get();
	ss >> lineSpacing;

	getline( file, line );
	ss.clear();
	ss.str( line );
	int width, height;
	ss >> width;
	ss.get();
	ss >> height;

	memset( quads_, 0, sizeof( quads_ ) );
	memset( dimensions_, 0, sizeof( dimensions_ ) );

	for( char c = ' '; c <= '~'; ++c )
	{
		getline( file, line );
		ss.clear();
		ss.str( line );

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