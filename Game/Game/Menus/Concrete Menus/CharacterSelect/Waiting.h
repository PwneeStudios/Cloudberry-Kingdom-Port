#ifndef WAITING
#define WAITING

#include <global_header.h>

namespace CloudberryKingdom
{
	class CharacterSelect;
}



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
