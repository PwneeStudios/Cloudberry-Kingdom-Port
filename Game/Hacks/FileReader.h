#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <memory>
#include <string>

class File;

struct FileReader
{

	std::shared_ptr<File> file_;

	FileReader( const std::wstring &path );
	~FileReader();

	std::wstring ReadLine();

};

#endif