#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

struct Directory
{


	
	static std::wstring GetCurrentDirectory()
	{
		return std::wstring();
	}

	static std::vector<std::wstring> GetFiles( const std::wstring &path )
	{
		return std::vector<std::wstring>();
	}

	static std::vector<std::wstring> GetDirectories( const std::wstring &path )
	{
		return std::vector<std::wstring>();
	}

};

#endif
