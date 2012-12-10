#ifndef CAMPAIGNHELPER
#define CAMPAIGNHELPER

#include <global_header.h>

namespace CloudberryKingdom
{
	class CampaignHelper
	{

	public:
		static void InitializeStatics();

		static std::wstring GetName( int difficulty );
		static std::vector<Color> DifficultyColor;
		static std::vector<Localization::Words> DifficultyNames;
	};
}


#endif	//#ifndef CAMPAIGNHELPER
