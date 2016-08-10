#ifndef CAMPAIGNHELPER
#define CAMPAIGNHELPER

#include <small_header.h>

#include "Game/Localization.h"
//#include "Core/Text/EzText.h"


namespace CloudberryKingdom
{
	struct CampaignHelper
	{

		static void InitializeStatics();

		static std::wstring GetName( int difficulty );
		static std::vector<Color> DifficultyColor;
		static std::vector<Localization::Words> DifficultyNames;

	};
}


#endif	//#ifndef CAMPAIGNHELPER
