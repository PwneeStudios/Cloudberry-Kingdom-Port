#ifndef EZREADER
#define EZREADER

#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace CloudberryKingdom
{
	class EzReader
	{
	public:
		std::wstring FileName;

	private:
		std::shared_ptr<FileStream> stream;
	public:
		std::shared_ptr<BinaryReader> reader;

		EzReader( const std::wstring &FileName );

		~EzReader();
	};
}


#endif	//#ifndef EZREADER
