#ifndef STRINGWORLD_ENDURANCE
#define STRINGWORLD_ENDURANCE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct StringWorldEndurance : public StringWorldGameData
	{
	
		struct OnSwapLambda : public Lambda_1<std::shared_ptr<LevelSeedData> >
		{
		
			std::shared_ptr<StringWorldEndurance> ch;
		
			OnSwapLambda( const std::shared_ptr<StringWorldEndurance> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};

	
		std::shared_ptr<GUI_Score> MyGUI_Score;
		std::shared_ptr<GUI_Level> MyGUI_Level;

		std::shared_ptr<GUI_LivesLeft> Gui_LivesLeft;
		std::shared_ptr<GUI_Lives> Gui_Lives;
		std::shared_ptr<GUI_NextLife> Gui_NextLife;
		std::shared_ptr<CoinScoreMultiplierObject> MyCoinScoreMultiplier;

	
		StringWorldEndurance( const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed, const std::shared_ptr<GUI_LivesLeft> &Gui_LivesLeft, int NextLife );

		virtual void Release();

		virtual void AdditionalSwapToLevelProcessing( const std::shared_ptr<GameData> &game );
	};
}


#endif	//#ifndef STRINGWORLD_ENDURANCE
