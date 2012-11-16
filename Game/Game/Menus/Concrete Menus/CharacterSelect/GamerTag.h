#ifndef GAMERTAG
#define GAMERTAG

#include <global_header.h>

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class EzText;
}



#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif



namespace CloudberryKingdom
{
	class GamerTag : public CkBaseMenu
	{
	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	public:
		GamerTag( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	protected:
		virtual void ReleaseBody();

	private:
		std::shared_ptr<EzText> Text;
	public:
		virtual void Init();

//C# TO C++ CONVERTER NOTE: The parameter GamerTag was renamed since it is named the same as a user-defined type:
		static void ScaleGamerTag( const std::shared_ptr<EzText> &GamerTag_Renamed );

		bool ShowGamerTag;
	private:
		void SetGamerTag();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GAMERTAG
