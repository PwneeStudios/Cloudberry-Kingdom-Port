#include <small_header.h>
#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"

#include "Game/Level/Make/LockableBool.h"
#include "Game/Level/Make/LevelSeedData.h"
#include "Game/Objects/Door/Door.h"

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
