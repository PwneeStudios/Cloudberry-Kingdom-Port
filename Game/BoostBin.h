#include <iostream>

template <typename T> void OnAssignment( const boost::shared_ptr<T> * p )
{
	if ( dynamic_cast< Level * >( p ) != 0 )
	{
		CloudberryKingdom::Tools::Nothing();
	}
}

std::vector< GenericBoostBin * > MetaBoostBin;

std::map< int, std::vector< int > > PrevMetaBoostBinCount;

void MakeLocks()
{
	for ( std::vector< GenericBoostBin * >::const_iterator bin = MetaBoostBin.begin(); bin != MetaBoostBin.end(); ++bin )
	{
		( *bin )->MakeMutex();
	}	
}

void Stats()
{
	CloudberryKingdom::Tools::Write( L"\n" );
	CloudberryKingdom::Tools::Write( L"---------------------------------------------------------" );
	CloudberryKingdom::Tools::Write( L"----------------------- Stats ---------------------------" );
	CloudberryKingdom::Tools::Write( L"---------------------------------------------------------" );

	int count = 0;
	for ( std::vector< GenericBoostBin * >::const_iterator bin = MetaBoostBin.begin(); bin != MetaBoostBin.end(); ++bin )
	{
		int n = ( *bin )->Count();
		std::wstring name = Utf8ToWstring( ( *bin )->ClassName );
		Replace( name, L"struct CloudberryKingdom::", L"" );

		if ( PrevMetaBoostBinCount[ count ].size() == 0 )
		{
			PrevMetaBoostBinCount[ count ].push_back( 0 );
		}

		PrevMetaBoostBinCount[ count ].push_back( n - PrevMetaBoostBinCount[ count ][0] );
		PrevMetaBoostBinCount[ count ][0] = n;


		std::wstring Line = name + L"\t";
		for ( int i = 0; i < PrevMetaBoostBinCount[ count ].size(); ++i)
		{
			Line += ToString( PrevMetaBoostBinCount[ count ][i] ) + L"\t";
		}

		CloudberryKingdom::Tools::Write( Line.c_str() );

		count++;
	}
	CloudberryKingdom::Tools::Write( L"---------------------------------------------------------" );
	CloudberryKingdom::Tools::Write( L"\n" );
}

//std::vector< GenericBoostBin * > MetaBoostBin_Cleaned;
//
//void MakeClean()
//{
//	for ( std::vector< GenericBoostBin * >::const_iterator bin = MetaBoostBin.begin(); bin != MetaBoostBin.end(); ++bin )
//	{
//		( *bin )->ClassName
//	}
//}