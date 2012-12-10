#ifndef _STORAGECONTAINER_H_
#define _STORAGECONTAINER_H_

class StorageContainer
{

public:

	bool FileExists( const std::wstring &name )
	{
		return false;
	}

	void DeleteFile( const std::wstring &name )
	{
		
	}

	std::shared_ptr<BinaryWriter> CreateFile( const std::wstring &name )
	{
		return std::shared_ptr<BinaryWriter>();
	}

};

#endif
