#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


namespace CloudberryKingdom
{

	Version::Version( int Major, int Minor, int Sub )
	{
		MajorVersion = Major;
		MinorVersion = Minor;
		SubVersion = Sub;
	}

	int Version::CompareTo( const std::shared_ptr<Object> &o )
	{
		Version v = static_cast<Version>( o );

		if ( v.MajorVersion == MajorVersion )
		{
			if ( v.MinorVersion == MinorVersion )
				return this->SubVersion.compare( v.SubVersion );
			else
				return this->MinorVersion.compare( v.MinorVersion );
		}
		else
			return this->MajorVersion.compare( v.MajorVersion );
	}

	bool Version::operator > ( Version v2 )
	{
		return this->compare( v2 ) > 0;
	}

	bool Version::operator >= ( Version v2 )
	{
		return this->compare( v2 ) >= 0;
	}

	bool Version::operator < ( Version v2 )
	{
		return this->compare( v2 ) < 0;
	}

	bool Version::operator <= ( Version v2 )
	{
		return this->compare( v2 ) <= 0;
	}
}
