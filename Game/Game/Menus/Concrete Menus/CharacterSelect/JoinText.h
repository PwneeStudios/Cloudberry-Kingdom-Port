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
	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		JoinText( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
		boost::shared_ptr<JoinText> JoinText_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );

		virtual void ReleaseBody();
	
		boost::shared_ptr<EzText> Text;
	
		virtual void Init();

		static void ScaleGamerTag( const boost::shared_ptr<EzText> &GamerTag_Renamed );
	
		void SetGamerTag();

		void MyDraw();
		virtual void MyPhsxStep();

	};
}


#endif	//#ifndef JOINTEXT
