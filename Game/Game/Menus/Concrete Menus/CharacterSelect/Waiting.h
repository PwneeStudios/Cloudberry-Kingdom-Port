#ifndef WAITING
#define WAITING

#include <global_header.h>

namespace CloudberryKingdom
{
	struct CharacterSelect;
}



namespace CloudberryKingdom
{
	struct Waiting : public CkBaseMenu
	{
	
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		Waiting( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	
		virtual void ReleaseBody();

	
		virtual void Init();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef WAITING
