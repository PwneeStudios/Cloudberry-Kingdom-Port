#include <global_header.h>

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	void CampaignHelper::InitializeStatics()
	{
		Color tempVector[] = { bColor( 44, 44, 44 ), bColor( 144, 200, 225 ), bColor( 44, 203, 48 ), bColor( 248, 136, 8 ), bColor( 90, 90, 90 ), bColor( 0, 255, 255 ) };
		CampaignHelper::DifficultyColor = VecFromArray( tempVector );
		Localization::Words tempVector2[] = { Localization::Words_CUSTOM, Localization::Words_TRAINING, Localization::Words_UNPLEASANT, Localization::Words_ABUSIVE, Localization::Words_HARDCORE, Localization::Words_MASOCHISTIC };
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
