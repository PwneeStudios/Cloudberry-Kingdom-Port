#ifndef _FILEREADER_H_
#define _FILEREADER_H_

struct FileReader
{


	FileReader( std::wstring path ) { }
	~FileReader() { } // FIXME: make sure to close the file.

	std::wstring ReadLine() { return _T( "" ); }

};

#endif