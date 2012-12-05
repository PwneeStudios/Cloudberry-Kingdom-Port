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



#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

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
		int FindClrIndex( std::vector<std::shared_ptr<MenuListItem> > &list, std::shared_ptr<ClrTextFx> clr );

		int FindHatIndex( std::vector<std::shared_ptr<Hat> > &list, const std::shared_ptr<Hat> &hat );

	public:
		void GetIndices( std::vector<int> ItemIndex, std::vector<std::vector<std::shared_ptr<MenuListItem> > > &ItemList );

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
