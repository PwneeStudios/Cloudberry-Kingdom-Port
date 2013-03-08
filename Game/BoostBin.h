#include <iostream>

#include <Game/Level/Level.h>





int UseCountCutoff = 0;

std::vector< GenericBoostBin * > MetaBoostBin;

std::map< int, std::vector< int > > PrevMetaBoostBinCount;

/** Codes :
		10, assignment
		0, make_shared constructor
		1, static_pointer_cast
		3, dynamic_pointer_cast
**/

void OnNew( int address )
{
	if ( CloudberryKingdom::CloudberryKingdomGame::address == address && address != 0 )
	{
		CloudberryKingdom::Tools::Nothing();
	}
}

void OnDestructor( std::string class_name )
{
}

void _OnAssignment( std::string class_name, int address, int origin_code )
{

	if ( origin_code != 10 && origin_code != 0 && origin_code != 1 && origin_code != 3 )
	{
		return;
	}

	if ( std::string::npos != class_name.find( "JoinText" ) )
	{

		CloudberryKingdom::Tools::Nothing();
		//if ( CloudberryKingdom::CloudberryKingdomGame::address == 0 )
		//	CloudberryKingdom::CloudberryKingdomGame::address = address;

	}

	if ( CloudberryKingdom::CloudberryKingdomGame::address == address && address != 0 )
	{
		CloudberryKingdom::Tools::Nothing();
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
	for ( std::vector< GenericBoostBin * >::iterator bin = MetaBoostBin.begin(); bin != MetaBoostBin.end(); ++bin )
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

		//if ( name == L"Quad" )
		//{
		//	std::vector< int > vec = PrevMetaBoostBinCount[ count ];

		//	int m = vec[ vec.size() - 1 ];
		//	if ( m > 0 )
		//	{
		//		CloudberryKingdom::Tools::Write( L"" );
		//	}
		//}

		std::wstring Line = name + L"\t";
		for ( int i = 0; i < PrevMetaBoostBinCount[ count ].size(); ++i )
		{
			Line += ToString( PrevMetaBoostBinCount[ count ][i] ) + L"\t";
		}

		// Search for 'address'
		BoostBin<CloudberryKingdom::JoinText>* _bin = reinterpret_cast<BoostBin<CloudberryKingdom::JoinText>* >( *bin );
		std::vector<int> addresses = ( *bin )->GetAddress();
		for ( int i = 0; i < addresses.size(); i++)
		{
			int ref_count = 0;
			if ( addresses[ i ] == CloudberryKingdom::CloudberryKingdomGame::address )
			{
				ref_count++;

				//boost::shared_ptr<CloudberryKingdom::JoinText>* ptrptr =
				//	reinterpret_cast<boost::shared_ptr<CloudberryKingdom::JoinText>*>( addresses[ i ] );

				CloudberryKingdom::JoinText* ptrptr =
					reinterpret_cast<CloudberryKingdom::JoinText*>( addresses[ i ] );

				std::wstring ref = name + L" : ref count = " + ToString( _bin->MyVec[ i ].pn.use_count() ); //ToString( ref_count );
				CloudberryKingdom::Tools::Write( ref.c_str() );
			}
		}

		// Loop through all memory
		//int _a = CloudberryKingdom::CloudberryKingdomGame::address;
		//for ( int i = _a - 0x10000000; i < _a + 0x10000000; i += 4 )
		//{
		//	int _address = *reinterpret_cast<int*>( i );
		//	if ( CloudberryKingdom::CloudberryKingdomGame::address == _address )
		//	{
		//		CloudberryKingdom::Tools::Nothing();

		//		boost::shared_ptr<CloudberryKingdom::JoinText>* ptrptr =
		//			reinterpret_cast<boost::shared_ptr<CloudberryKingdom::JoinText>*>( i );

		//		boost::shared_ptr<CloudberryKingdom::JoinText>* ptrptr2 =
		//			reinterpret_cast<boost::shared_ptr<CloudberryKingdom::JoinText>*>( i - 4 );

		//	}
		//}

		// Print a specific class
		//if ( name == L"GameObject::OnCameraChangeProxy" )
		//{
		//	CloudberryKingdom::Tools::Write( Line.c_str() );
		//}

		// Print every class
		//CloudberryKingdom::Tools::Write( Line.c_str() );

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