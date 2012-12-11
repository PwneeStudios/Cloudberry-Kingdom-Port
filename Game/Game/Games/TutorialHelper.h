#ifndef TUTORIALHELPER
#define TUTORIALHELPER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GUI_Text;
}

namespace CloudberryKingdom
{
	struct GameData;
}

namespace CloudberryKingdom
{
	struct Lambda;
}



namespace CloudberryKingdom
{
	struct TutorialHelper
	{
	
		struct TextKillerHelper : public Lambda
		{
		
			std::shared_ptr<GUI_Text> text;

		
			TextKillerHelper( const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct ReadyGo_GoProxy : public Lambda
		{
		
			std::shared_ptr<GameData> game;
			std::shared_ptr<Lambda> End;

		
			ReadyGo_GoProxy( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &End );

			void Apply();
		};

	
		static Vector2 ReadyGoPos;
		static void ReadyGo( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &End );

		static void ReadyGo_Go( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &End );
	};
}


#endif	//#ifndef TUTORIALHELPER
