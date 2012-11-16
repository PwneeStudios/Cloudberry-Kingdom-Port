#ifndef EZREADER
#define EZREADER

#include <global_header.h>

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
