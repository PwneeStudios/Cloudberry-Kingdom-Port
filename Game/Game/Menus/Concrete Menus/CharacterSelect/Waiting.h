#ifndef WAITING
#define WAITING

#include "../Game/Menus/CkBaseMenu.h"

namespace CloudberryKingdom
{
	class CharacterSelect;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Waiting : public CkBaseMenu
	{
	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	public:
		Waiting( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	protected:
		virtual void ReleaseBody();

	public:
		virtual void Init();

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef WAITING
