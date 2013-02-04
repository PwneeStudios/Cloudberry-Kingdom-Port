#ifndef _STORAGECONTAINER_H_
#define _STORAGECONTAINER_H_

#include <string>

struct StorageContainer
{

	// This is the name of the container in case some platforms want to bypass
	// the storage container system and write directly to the
	// requested directory.
	std::string Name;

	bool FileExists( const std::wstring &name )
	{
		return false;
	}

	void DeleteFile( const std::wstring &name )
	{
		
	}

	boost::shared_ptr<BinaryWriter> CreateFile( const std::wstring &name )
	{
		return boost::shared_ptr<BinaryWriter>();
	}

};

#endif
