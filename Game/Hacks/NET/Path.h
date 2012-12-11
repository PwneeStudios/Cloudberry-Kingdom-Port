#ifndef _PATH_H_
#define _PATH_H_

struct Path
{


	
	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath ) { return _T( "" ); }
	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath1, const std::wstring &Subpath2 ) { return _T( "" ); }
	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath1, const std::wstring &Subpath2, const std::wstring &Subpath3 ) { return _T( "" ); }
	static std::wstring Combine( const std::wstring &Path, const std::wstring &Subpath1, const std::wstring &Subpath2, const std::wstring &Subpath3, const std::wstring &Subpath4 ) { return _T( "" ); }
	static std::wstring GetDirectoryName( const std::wstring &Path ) { return _T( "" ); }
	static std::wstring RootDirection;

};

#endif
