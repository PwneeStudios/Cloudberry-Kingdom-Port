#ifndef VERSION
#define VERSION
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
