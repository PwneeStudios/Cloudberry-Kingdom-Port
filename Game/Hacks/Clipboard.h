#ifndef _CLIPBOARD_H_
#define _CLIPBOARD_H_

class Clipboard
{

public:
	static std::wstring GetText() { return _T( "" ); }
	static void SetText( std::wstring text ) { }

};

#endif