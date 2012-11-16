#ifndef JOINTEXT
#define JOINTEXT

#include <global_header.h>

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class EzText;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)
using namespace Microsoft::Xna::Framework::GamerServices;
#endif



namespace CloudberryKingdom
{
	class JoinText : public CkBaseMenu
	{
	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	public:
		JoinText( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	protected:
		virtual void ReleaseBody();

	private:
		std::shared_ptr<EzText> Text;
	public:
		virtual void Init();

//C# TO C++ CONVERTER NOTE: The parameter GamerTag was renamed since it is named the same as a user-defined type:
		static void ScaleGamerTag( const std::shared_ptr<EzText> &GamerTag_Renamed );

	private:
		void SetGamerTag();

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef JOINTEXT
