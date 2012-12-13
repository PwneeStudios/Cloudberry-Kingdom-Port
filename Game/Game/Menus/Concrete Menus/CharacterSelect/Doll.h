#ifndef DOLL
#define DOLL

#include <global_header.h>

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif

namespace CloudberryKingdom
{

	struct Doll : public CkBaseMenu
	{
	
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		Doll( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );
		std::shared_ptr<Doll> Doll_Construct( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );
	
		virtual void ReleaseBody();
	
		std::shared_ptr<Bob> MyDoll;
		virtual void Init();
	
		void MakeDoll();
	
		void UpdateColorScheme();

	
		int FindClrIndex( std::vector<std::shared_ptr<MenuListItem> > &list, std::shared_ptr<ClrTextFx> clr );

		int FindHatIndex( std::vector<std::shared_ptr<Hat> > &list, const std::shared_ptr<Hat> &hat );

	
		void GetIndices( std::vector<int> ItemIndex, std::vector<std::vector<std::shared_ptr<MenuListItem> > > &ItemList );

	
		virtual void MyPhsxStep();

	
		bool ShowBob;
		void DrawBob();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef DOLL
