#include <small_header.h>
#include "Game/Tools/EzReader.h"

#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	EzReader::EzReader( const std::wstring &FileName )
	{
		this->FileName = FileName;

		Tools::UseInvariantCulture();
		//stream = File->Open( FileName, FileMode::Open, FileAccess::Read, FileShare::None );
		//reader = boost::make_shared<FileBinaryReader>( stream, Encoding::UTF8 );
		//
		reader = boost::make_shared<FileBinaryReader>( FileName );
	}

	EzReader::~EzReader()
	{
		reader->Close();
		//stream->Close();
	}
}
