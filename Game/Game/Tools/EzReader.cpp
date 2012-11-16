#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace CloudberryKingdom
{

	EzReader::EzReader( const std::wstring &FileName )
	{
		this->FileName = FileName;

		Tools::UseInvariantCulture();
		stream = File->Open( FileName, FileMode::Open, FileAccess::Read, FileShare::None );
		reader = std::make_shared<BinaryReader>( stream, Encoding::UTF8 );
	}

	EzReader::~EzReader()
	{
		reader->Close();
		stream->Close();
	}
}
