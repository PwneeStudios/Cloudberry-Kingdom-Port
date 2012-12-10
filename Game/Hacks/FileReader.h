#ifndef _FILEREADER_H_
#define _FILEREADER_H_

class FileReader
{

public:
	FileReader( std::wstring path ) { }
	~FileReader() { } // FIXME: make sure to close the file.

	std::wstring ReadLine() { return _T( "" ); }

};

#endif