#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

class File;

struct FileReader
{

	boost::shared_ptr<File> file_;

	FileReader( const std::wstring &path );
	~FileReader();

	std::wstring ReadLine();

};

#endif