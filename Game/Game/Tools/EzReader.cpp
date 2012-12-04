#include <global_header.h>

namespace CloudberryKingdom
{

	EzReader::EzReader( const std::wstring &FileName )
	{
		this->FileName = FileName;

		Tools::UseInvariantCulture();
		//stream = File->Open( FileName, FileMode::Open, FileAccess::Read, FileShare::None );
		//reader = std::make_shared<BinaryReader>( stream, Encoding::UTF8 );
		//
		reader = std::make_shared<BinaryReader>( FileName );
	}

	EzReader::~EzReader()
	{
		reader->Close();
		//stream->Close();
	}
}
