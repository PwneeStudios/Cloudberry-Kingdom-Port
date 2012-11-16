#ifndef DOLL
#define DOLL

#include <global_header.h>

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class MenuListItem;
}

namespace CloudberryKingdom
{
	class Hat;
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
	class Doll : public CkBaseMenu
	{
	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	public:
		Doll( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	protected:
		virtual void ReleaseBody();

	public:
		std::shared_ptr<Bob> MyDoll;
		virtual void Init();

	private:
		void MakeDoll();

	public:
		void UpdateColorScheme();

	private:
		int FindClrIndex( std::vector<MenuListItem*> &list, ClrTextFx clr );

		int FindHatIndex( std::vector<Hat*> &list, const std::shared_ptr<Hat> &hat );

	public:
		void GetIndices( std::vector<int> ItemIndex, std::vector<std::vector<MenuListItem*>&> ItemList );

	protected:
		virtual void MyPhsxStep();

	public:
		bool ShowBob;
		void DrawBob();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef DOLL
