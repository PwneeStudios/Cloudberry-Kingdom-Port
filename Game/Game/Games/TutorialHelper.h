#ifndef TUTORIALHELPER
#define TUTORIALHELPER

#include <global_header.h>

namespace CloudberryKingdom
{
	class GUI_Text;
}

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class Lambda;
}


using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{
	class TutorialHelper
	{
	private:
		class TextKillerHelper : public Lambda
		{
		private:
			std::shared_ptr<GUI_Text> text;

		public:
			TextKillerHelper( const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	private:
		class ReadyGo_GoProxy : public Lambda
		{
		private:
			std::shared_ptr<GameData> game;
			std::shared_ptr<Lambda> End;

		public:
			ReadyGo_GoProxy( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &End );

			void Apply();
		};

	public:
		static Vector2 ReadyGoPos;
		static void ReadyGo( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &End );

		static void ReadyGo_Go( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &End );
	};
}


#endif	//#ifndef TUTORIALHELPER
