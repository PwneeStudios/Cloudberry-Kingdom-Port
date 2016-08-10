#ifndef _PATH_H_
#define _PATH_H_

struct Path
{
	
	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath )
	{
		return Path + std::wstring( L"/" ) + Subpath;
	}

	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath1, const std::wstring &Subpath2 )
	{
		return Path + std::wstring( L"/" ) + Subpath1 + std::wstring( L"/" ) + Subpath2;
	}

	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath1, const std::wstring &Subpath2, const std::wstring &Subpath3 )
	{
		return Path + std::wstring( L"/" ) + Subpath1 + std::wstring( L"/" ) + Subpath2 + std::wstring( L"/" ) + Subpath3;
	}

	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath1, const std::wstring &Subpath2, const std::wstring &Subpath3, const std::wstring &Subpath4 )
	{
		return Path + std::wstring( L"/" ) + Subpath1 + std::wstring( L"/" ) + Subpath2 + std::wstring( L"/" ) + Subpath3  + std::wstring( L"/" ) + Subpath4;
	}

	static std::wstring GetDirectoryName( const std::wstring &Path )
	{ 
		return std::wstring( L"" );
	}

	static std::wstring RootDirection;

};

#endif
