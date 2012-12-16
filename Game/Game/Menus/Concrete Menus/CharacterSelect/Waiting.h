#ifndef WAITING
#define WAITING

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Waiting : public CkBaseMenu
	{
	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		Waiting( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
		boost::shared_ptr<Waiting> Waiting_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
	
		virtual void ReleaseBody();
	
		virtual void Init();
	
		virtual void MyPhsxStep();

	};
}


#endif	//#ifndef WAITING
