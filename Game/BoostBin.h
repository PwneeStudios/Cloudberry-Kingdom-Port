#include <iostream>

#include <Game/Level/Level.h>



std::vector< GenericBoostBin * > MetaBoostBin;

std::map< int, std::vector< int > > PrevMetaBoostBinCount;

/** Codes :
		10, assignment
		0, make_shared constructor
		1, static_pointer_cast
		3, dynamic_pointer_cast
**/

void OnDestructor( std::string class_name )
{

}

void _OnAssignment( std::string class_name, int origin_code )
{

	if ( origin_code != 10 && origin_code != 0 && origin_code != 1 && origin_code != 3 )
	{
		return;
	}

	if ( std::string::npos != class_name.find( "FireSpinner_Parameters" ) )
	{

		CloudberryKingdom::Tools::Write( L"" );

	}

}

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