#include <small_header.h>
#include "Game/Games/CampaignHelper.h"

#include "Game/Localization.h"
#include "Core/Text/EzText.h"


#include <Hacks/List.h>
#include <Hacks/String.h>

namespace CloudberryKingdom
{

	void CampaignHelper::InitializeStatics()
	{
		Color tempVector[] = { bColor( 44, 44, 44 ), bColor( 144, 200, 225 ), bColor( 44, 203, 48 ), bColor( 248, 136, 8 ), bColor( 90, 90, 90 ), bColor( 0, 255, 255 ) };
		CampaignHelper::DifficultyColor = VecFromArray( tempVector );
		Localization::Words tempVector2[] = { Localization::Words_Custom, Localization::Words_Training, Localization::Words_Unpleasant, Localization::Words_Abusive, Localization::Words_Hardcore, Localization::Words_Masochistic };
		CampaignHelper::DifficultyNames = VecFromArray( tempVector2 );
	}

	// Statics
	std::vector<Color> CampaignHelper::DifficultyColor;
	std::vector<Localization::Words> CampaignHelper::DifficultyNames;


	std::wstring CampaignHelper::GetName( int difficulty )
	{
		return EzText::ColorToMarkup( DifficultyColor[ difficulty ] ) + ToLower(Localization::WordString( DifficultyNames[ difficulty ] )) + EzText::ColorToMarkup(Color::White);
	}

}
