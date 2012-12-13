#ifndef JOINTEXT
#define JOINTEXT

#include <global_header.h>

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif

namespace CloudberryKingdom
{
	struct JoinText : public CkBaseMenu
	{
	
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		JoinText( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );
		void JoinText_Construct( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

		virtual void ReleaseBody();
	
		std::shared_ptr<EzText> Text;
	
		virtual void Init();

		static void ScaleGamerTag( const std::shared_ptr<EzText> &GamerTag_Renamed );
	
		void SetGamerTag();
	
		virtual void MyPhsxStep();

	};
}


#endif	//#ifndef JOINTEXT
