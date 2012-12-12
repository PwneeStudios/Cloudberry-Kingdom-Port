#ifndef _PATH_H_
#define _PATH_H_

struct Path
{
	
	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath )
	{
		return Path + _T( "/" ) + Subpath;
	}

	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath1, const std::wstring &Subpath2 )
	{
		return Path + _T( "/" ) + Subpath1 + _T( "/" ) + Subpath2;
	}

	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath1, const std::wstring &Subpath2, const std::wstring &Subpath3 )
	{
		return Path + _T( "/" ) + Subpath1 + _T( "/" ) + Subpath2 + _T( "/" ) + Subpath3;
	}

	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath1, const std::wstring &Subpath2, const std::wstring &Subpath3, const std::wstring &Subpath4 )
	{
		return Path + _T( "/" ) + Subpath1 + _T( "/" ) + Subpath2 + _T( "/" ) + Subpath3  + _T( "/" ) + Subpath4;
	}

	static std::wstring GetDirectoryName( const std::wstring &Path )
	{ 
		return _T( "" );
	}

	static std::wstring RootDirection;

};

#endif
