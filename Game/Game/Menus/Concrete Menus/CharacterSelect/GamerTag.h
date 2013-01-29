#ifndef GAMERTAG
#define GAMERTAG

#include <global_header.h>

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif

namespace CloudberryKingdom
{

	struct GamerTag : public CkBaseMenu
	{

		virtual ~GamerTag() { }
	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		GamerTag( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
		boost::shared_ptr<GamerTag> GamerTag_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );

	
		virtual void ReleaseBody();

	
		boost::shared_ptr<EzText> Text;
	
		virtual void Init();

//C# TO C++ CONVERTER NOTE: The parameter GamerTag was renamed since it is named the same as a user-defined type:
		static void ScaleGamerTag( const boost::shared_ptr<EzText> &GamerTag_Renamed );

		bool ShowGamerTag;
	
		void SetGamerTag();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GAMERTAG
