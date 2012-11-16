#ifndef GAMERTAG
#define GAMERTAG

#include "../Game/Menus/CkBaseMenu.h"
#include <string>
#include <tchar.h>

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class EzText;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)
using namespace Microsoft::Xna::Framework::GamerServices;
#endif



namespace CloudberryKingdom
{
	class GamerTag : public CkBaseMenu
	{
	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	public:
		GamerTag( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	protected:
		virtual void ReleaseBody();

	private:
		std::shared_ptr<EzText> Text;
	public:
		virtual void Init();

//C# TO C++ CONVERTER NOTE: The parameter GamerTag was renamed since it is named the same as a user-defined type:
		static void ScaleGamerTag( const std::shared_ptr<EzText> &GamerTag_Renamed );

		bool ShowGamerTag;
	private:
		void SetGamerTag();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GAMERTAG
