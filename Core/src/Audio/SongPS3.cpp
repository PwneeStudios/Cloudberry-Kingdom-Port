#include <Audio/Song.h>

#include <Audio/PS3/mscommon.h>
#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

#include "SongInternalPS3.h"

float GetMP3Length( const std::string &path )
{
	long size;

	int handle = OpenFile( path.c_str(), &size );

	if( handle < 0 )
	{
		LOG.Write( "Couldn't get length: %s\n", path.c_str() );
		return 0.f;
	}

	LOG.Write( "Buffer %d bytes\n", size );
	long buffer = reinterpret_cast< long >( memalign( 128, size ) );
	long data = buffer;

	LoadFile( handle, data, size, 0, 0 );

	unsigned int tSize = 0;
	float time = 0.f;
	unsigned int offset = 0;

	while( true )
	{
		CellMSMP3FrameHeader hdr;

		int ret = cellMSMP3GetFrameInfo( reinterpret_cast< void * >( data ), &hdr );
		if( ret == -1 )
		{
			LOG.Write( "Invalid MP3 header\n" );
			time = 0.f;
			break;
		}

		tSize += hdr.PacketSize;
		if( hdr.ID3 == 0 && hdr.Tag == 0 )
			time += hdr.PacketTime;
		data += hdr.PacketSize;
		offset += hdr.PacketSize;
		
		if( tSize == size )
		{
			LOG.Write( "MP3 loaded\n" );
			LOG.Write( "Playback time at %d Hz: %f s\n", hdr.Frequency, time );
			break;
		}
		else if( tSize > size )
		{
			LOG.Write( "Passed the end of file!\n ");
			time = 0.f;
			break;
		}
	}

	free( reinterpret_cast< void * >( buffer ) );
	cellFsClose( handle );

	return time;
}

Song::Song() :
	internal_( new SongInternal )
{
	Duration.TotalSeconds = 0.f;
}

Song::~Song() 
{
	delete internal_;
}

void Song::Load( const std::string &path )
{
	internal_->Path = "/app_home/ContentPS3/" + path;
	Duration.TotalSeconds = GetMP3Length( internal_->Path );
}
