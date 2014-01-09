#ifndef EZREADER
#define EZREADER

#include <small_header.h>

//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct EzReader
	{
	
		std::wstring FileName;

	
		//boost::shared_ptr<FileStream> stream;
	
		boost::shared_ptr<BinaryReader> reader;

		EzReader( const std::wstring &FileName );

		~EzReader();
	};
}


#endif	//#ifndef EZREADER
