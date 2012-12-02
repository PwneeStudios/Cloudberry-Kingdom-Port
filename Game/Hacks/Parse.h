#ifndef _PARSE_H_
#define _PARSE_H_

#include <sstream>

inline int ParseInt( const std::wstring &s )
{
	using namespace std;

	int num = 0;
	wstringstream converter;

	converter << s;
	converter >> num;

	return num;
}

// FIXME: do we need to specify precision or anything here?
inline float ParseFloat( const std::wstring &s )
{
	using namespace std;

	float num = 0;
	wstringstream converter;

	converter << s;
	converter >> num;

	return num;
}

#endif
