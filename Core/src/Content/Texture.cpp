#include <Content/Texture.h>

#include <cassert>
#include <fstream>
#include <GL/glew.h>
#include <iostream>
#include <zlib.h>

#define NTOHS( val ) \
	( ( ( val ) & 0xff ) << 8 | ( val ) >> 8 )

#define NTOHL( val ) \
	( ( NTOHS( ( val ) & 0xffff ) << 16 ) | ( NTOHS( val >> 16 ) ) )

/** Read a unsigned integer from a PNG file. */
static unsigned int ReadPngUInt( std::ifstream &file )
{
	unsigned int temp;
	file.read( reinterpret_cast< char * >( &temp ), sizeof( unsigned int ) );
	return NTOHL( temp );
}

/** Read an integer from a PNG file. */
static int ReadPngInt( std::ifstream &file )
{
	return static_cast< int >( ReadPngUInt( file ) ) ;
}

#undef NTOHS
#undef NTOHL

struct TextureInternal
{
	GLuint TextureId;
};

Texture::Texture() :
	width_( 0 ),
	height_( 0 ),
	internal_( new TextureInternal )
{
	memset( internal_, 0, sizeof( TextureInternal ) );
}

Texture::~Texture()
{
	GpuDestroy();
	Unload();

	delete internal_;
}

void Texture::Load()
{
	loadPng();
}

void Texture::Unload()
{
	width_ = 0;
	height_ = 0;
	data_ = std::vector< char >();
}

void Texture::GpuCreate()
{
	glGenTextures( 1, &internal_->TextureId );
	glBindTexture( GL_TEXTURE_2D, internal_->TextureId );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, reinterpret_cast< GLvoid * >( &data_[ 0 ] ) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glBindTexture( GL_TEXTURE_2D, 0 );
}

void Texture::GpuDestroy()
{
	glDeleteTextures( 1, &internal_->TextureId );
	internal_->TextureId = 0;
}

void Texture::Activate()
{
	glBindTexture( GL_TEXTURE_2D, internal_->TextureId );
}

// Private.
void Texture::loadPng()
{
	using namespace std;

	const string &path = GetPath();
	std::ifstream file( path.c_str(), ios_base::in | ios_base::binary );
	if( !file.is_open() )
	{
		cout << "Failed to load texture: " << path << endl;
		setLoaded( false );
		return;
	}

#pragma pack( push )
#pragma pack( 1 )
	struct Signature
	{
		char TransmissionCheck;
		char Png[ 3 ];
		char DosCrLf[ 2 ];
		char DisplayStop;
		char UnixLf;
	} signature;

	struct Chunk
	{
		unsigned int Length;
		union
		{
			unsigned int Type;
			char Name[ 4 ];
		};
		unsigned int Checksum;
	} chunk;

	struct IHDR
	{
		int Width;
		int Height;
		char BitDepth;
		char ColorType;
		char CompressionMethod;
		char FilterMethod;
		char InterlaceMethod;
	} ihdr;
#pragma pack( pop )

	file.read( reinterpret_cast< char * >( &signature ), sizeof( signature ) );

	// Concatenated image data.
	std::vector< char > data;

	// Read a chunk.
	bool done = false;
	while( !done )
	{
		chunk.Length = ReadPngUInt( file );
		chunk.Type = ReadPngUInt( file );

		switch( chunk.Type )
		{
		case 'IHDR':
			ihdr.Width  = ReadPngInt( file );
			ihdr.Height = ReadPngInt( file );
			width_ = ihdr.Width;
			height_ = ihdr.Height;
			file.read( reinterpret_cast< char * >( &ihdr.BitDepth ), 5 * sizeof( char ) );
			break;
		case 'IDAT':
			{
				size_t oldSize = data.size();
				data.resize( oldSize + chunk.Length );

				// Read the compressed data.
				file.read( &data[ oldSize ], chunk.Length );
			}
			break;
		case 'IEND':
			done = true;
			continue;
			break;
		default:
			file.seekg( chunk.Length, ios_base::cur );
			break;
		}

		chunk.Checksum = ReadPngUInt( file );
	}

	if( ( ihdr.ColorType == 2 && ihdr.BitDepth == 8 )
		|| ( ihdr.ColorType == 6 && ihdr.BitDepth == 8 ) )
	{
		vector< char > buffer( width_ * height_
			* ( ( ihdr.ColorType == 2 ) ? 3 : 4 ) + height_ );

		if( !uncompress( data, buffer ) )
		{
			setLoaded( false );
			return;
		}

		// Allocate enough output space for a full RGBA stream.
		data_.resize( width_ * height_ * sizeof( unsigned int ) );

		if( ihdr.ColorType == 2 && ihdr.BitDepth == 8 )
			processPngIdat24Bpp( buffer );
		else if( ihdr.ColorType == 6 && ihdr.BitDepth == 8 )
			processPngIdat32Bpp( buffer );
	}
	else
	{
		cout << "Unknown PNG format (ColorType = " << ihdr.ColorType
			<< ", BitDepth = " << ihdr.BitDepth << ") in: " << path << endl;
		setLoaded( false );
		return;
	}

	setLoaded( true );
}

/** Special predictor used by PNG filter type 4. */
static unsigned char Paeth( short a, short b, short c )
{
	short p = a + b - c;
	short pa = abs( p - a );
	short pb = abs( p - b );
	short pc = abs( p - c );

	if( pa <= pb && pa <= pc )
		return static_cast< unsigned char >( a );
	else if( pb <= pc )
		return static_cast< unsigned char >( b );

	return static_cast< unsigned char >( c );
}

// Private.
void Texture::processPngIdat24Bpp( const std::vector< char > &uncompressed  )
{
	using namespace std;

	// Convert data one scan-line at a time.
	unsigned char *lastOut = 0;
	const int scanlineRowBytes = width_ * 3;
	const int outRowBytes = width_ * 4;

	// 1 byte/component * 3 components.
	const int bpp = 3;

	for( int row = 0; row < height_; ++row )
	{
		const unsigned char *scanline = reinterpret_cast< const unsigned char * >(
			&uncompressed[ row * ( scanlineRowBytes + 1 ) ]
		);
		unsigned char *out = reinterpret_cast< unsigned char * >(
			&data_[ row * outRowBytes ]
		);

		const unsigned char &filterType = *( scanline++ );

		unfilterPngScanline( out, scanline, lastOut, filterType, bpp, scanlineRowBytes );

		lastOut = out;
	}

	// Expand each row and insert alpha channel.
	for( int j = 0; j < height_; ++j )
	{
		unsigned char *out = reinterpret_cast< unsigned char * >( &data_[ j * width_ * 4 ] );
		for( int k = width_ * 4 - 4, l = width_ * 3 - 3; k >= 12; k -= 4, l -= 3 )
		{
			out[ k ] = out[ l ];
			out[ k + 1 ] = out[ l + 1 ];
			out[ k + 2 ] = out[ l + 2 ];
			out[ k + 3 ] = 0xff;
		}

		// Temporary location for first 4 RGB pixels
		char temp[ 12 ];
		memcpy( temp, out, sizeof( temp ) );

		// Copy the remaining pixels out of the temporary buffer to avoid
		// clobbering them when they are expanded.
		for( int k = 0, l = 0; k < 12; k += 4, l += 3 )
		{
			out[ k ] = temp[ l ];
			out[ k + 1 ] = temp[ l + 1 ];
			out[ k + 2 ] = temp[ l + 2 ];
			out[ k + 3 ] = 0xff;
		}
	}
}

// Private.
void Texture::processPngIdat32Bpp( const std::vector< char > &uncompressed  )
{
	using namespace std;

	// Convert data one scan-line at a time.
	unsigned char *lastOut = 0;
	const int rowBytes = width_ * sizeof( unsigned int );

	// 1 byte/component * 4 components.
	const int bpp = 4;

	for( int row = 0; row < height_; ++row )
	{
		const unsigned char *scanline = reinterpret_cast< const unsigned char * >(
			&uncompressed[ row * ( rowBytes + 1 ) ]
		);
		unsigned char *out = reinterpret_cast< unsigned char * >(
			&data_[ row * rowBytes ]
		);

		const unsigned char &filterType = *( scanline++ );

		unfilterPngScanline( out, scanline, lastOut, filterType, 4, rowBytes );

		lastOut = out;
	}
}

void Texture::unfilterPngScanline( unsigned char *out, const unsigned char *scanline,
	const unsigned char *lastOut, char filterType, int bpp, int scanlineRowBytes )
{
	switch( filterType )
	{
	case 0:	// None.
		memcpy( out, scanline, scanlineRowBytes );
		break;
	case 1: // Sub.
		// Copy the starting data into our decoded scan-line.
		for( int k = 0; k < bpp; ++ k )
			out[ k ] = scanline[ k ];

		// Un-sub the data.
		for( int k = bpp; k < scanlineRowBytes; ++k )
			out[ k ] = scanline[ k ] + out[ k - bpp ];

		break;
	case 2: // Up.
		if( lastOut )
		{
			for( int k = 0; k < scanlineRowBytes; ++k )
				out[ k ] = scanline[ k ] + lastOut[ k ];
		}
		else
			memcpy( out, scanline, scanlineRowBytes );
		break;
	case 3: // Average.
		if( lastOut )
		{
			// Copy the starting data into our decoded scan-line.
			for( int k = 0; k < bpp; ++k )
				out[ k ] = scanline[ k ] + lastOut[ k ] / 2;

			// Un-average the data.
			for( int k = bpp; k < scanlineRowBytes; ++k )
				out[ k ] = scanline[ k ] + ( out[ k - bpp ] + lastOut[ k ] ) / 2;
		}
		else
		{
			// Copy the starting data into our decoded scan-line.
			for( int k = 0; k < bpp; ++k )
				out[ k ] = scanline[ k ];

			// Un-average the data.
			for( int k = bpp; k < scanlineRowBytes; ++k )
				out[ k ] = scanline[ k ] + out[ k - bpp ] / 2;
		}
		break;
	case 4: // Paeth.
		if( lastOut )
		{
			// Copy the starting data into our decoded scan-line.
			for( int k = 0; k < bpp; ++k )
				out[ k ] = scanline[ k ] + lastOut[ k ];

			// Un-average the data.
			for( int k = bpp; k < scanlineRowBytes; ++k )
				out[ k ] = scanline[ k ] + Paeth( out[ k - bpp ], lastOut[ k ], lastOut[ k - bpp ] );
		}
		else
		{
			// Copy the starting data into our decoded scan-line.
			for( int k = 0; k < bpp; ++k )
				out[ k ] = scanline[ k ];

			// Un-average the data.
			for( int k = bpp; k < scanlineRowBytes; ++k )
				out[ k ] = scanline[ k ] + out[ k - bpp ];
		}
		break;
	default:
		assert( !"Unknown filter type!" );
		break;
	}
}

bool Texture::uncompress( const std::vector< char > &compressed, std::vector< char > &uncompressed )
{
	using namespace std;

	z_stream stream;
	int err;

	stream.next_in = const_cast< Bytef * >(
		reinterpret_cast< const Bytef * >( &compressed[ 0 ] )
		);
	stream.avail_in = compressed.size();

	stream.next_out = reinterpret_cast< Bytef * >( &uncompressed[ 0 ] );
	stream.avail_out = uncompressed.size();

	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;

	err = inflateInit( &stream );
	if( err != Z_OK )
	{
		cout << "PNG: Failed to initialize de-compressor" << endl;
		return false;
	}

	err = inflate( &stream, Z_FINISH );

	if( err != Z_STREAM_END )
	{
		inflateEnd( &stream );
		if( err == Z_NEED_DICT
			|| ( err == Z_BUF_ERROR && stream.avail_in == 0 ) )
		{
			cout << "PNG: Data inflation error" << endl;
			return false;
		}
		return false;
	}

	err = stream.avail_out;
	err = inflateEnd( &stream );

	return true;
}
