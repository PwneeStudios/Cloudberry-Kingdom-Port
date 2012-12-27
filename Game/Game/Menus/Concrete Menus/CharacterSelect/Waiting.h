#ifndef WAITING
#define WAITING

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Waiting : public CkBaseMenu
	{
	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
		bool CanGoBack;
	
		Waiting( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect, bool _CanGoBack );
		boost::shared_ptr<Waiting> Waiting_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect, bool _CanGoBack );
	
		virtual void ReleaseBody();
	
		virtual void Init();

		void MyDraw();
	
		virtual void MyPhsxStep();

	};
}


#endif	//#ifndef WAITING
