#ifndef _STORAGECONTAINER_H_
#define _STORAGECONTAINER_H_

struct StorageContainer
{



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
