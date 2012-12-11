#ifndef EZREADER
#define EZREADER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct EzReader
	{
	
		std::wstring FileName;

	
		//std::shared_ptr<FileStream> stream;
	
		std::shared_ptr<BinaryReader> reader;

		EzReader( const std::wstring &FileName );

		~EzReader();
	};
}


#endif	//#ifndef EZREADER
