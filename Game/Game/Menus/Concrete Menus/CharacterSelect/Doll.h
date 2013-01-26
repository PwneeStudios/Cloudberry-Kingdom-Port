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

		virtual ~Doll() { }
	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		Doll( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
		boost::shared_ptr<Doll> Doll_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
	
		virtual void ReleaseBody();
	
		boost::shared_ptr<Bob> MyDoll;
		virtual void Init();
	
		void MakeDoll();
	
		void UpdateColorScheme();

	
		int FindClrIndex( std::vector<boost::shared_ptr<MenuListItem> > &list, boost::shared_ptr<ClrTextFx> clr );

		int FindHatIndex( std::vector<boost::shared_ptr<Hat> > &list, const boost::shared_ptr<Hat> &hat );

	
		void GetIndices( std::vector<int> ItemIndex, std::vector<std::vector<boost::shared_ptr<MenuListItem> > > &ItemList );


		void MyDraw();
		virtual void MyPhsxStep();

	
		bool ShowBob;
		void DrawBob();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef DOLL
