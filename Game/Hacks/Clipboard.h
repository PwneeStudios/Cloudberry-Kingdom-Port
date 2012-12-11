#ifndef _CLIPBOARD_H_
#define _CLIPBOARD_H_

struct Clipboard
{


	static std::wstring GetText() { return _T( "" ); }
	static void SetText( std::wstring text ) { }

};

#endif