#ifndef VERSION
#define VERSION

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Version : public IComparable
	{
	public:
		int MajorVersion, MinorVersion, SubVersion;
		Version( int Major, int Minor, int Sub );

		int CompareTo( const std::shared_ptr<Object> &o );

		bool operator > ( Version v2 );
		bool operator >= ( Version v2 );
		bool operator < ( Version v2 );
		bool operator <= ( Version v2 );
	};
}


#endif	//#ifndef VERSION
