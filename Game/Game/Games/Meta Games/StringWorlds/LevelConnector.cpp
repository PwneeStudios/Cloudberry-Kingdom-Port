#include <global_header.h>

namespace CloudberryKingdom
{

	void LevelConnector::InitializeStatics()
	{
		LevelConnector::EndOfLevelCode = _T( "End of Level Connector" );
		LevelConnector::StartOfLevelCode = _T( "Start of Level Connector" );
	}

	// Statics
	std::wstring LevelConnector::EndOfLevelCode;
	std::wstring LevelConnector::StartOfLevelCode;

}
