#include <global_header.h>

namespace CloudberryKingdom
{

	void LevelConnector::InitializeStatics()
	{
		LevelConnector::EndOfLevelCode = std::wstring( L"End of Level Connector" );
		LevelConnector::StartOfLevelCode = std::wstring( L"Start of Level Connector" );
	}

	// Statics
	std::wstring LevelConnector::EndOfLevelCode;
	std::wstring LevelConnector::StartOfLevelCode;

}
