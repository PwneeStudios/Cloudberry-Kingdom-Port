#ifndef CONTROLSCREEN
#define CONTROLSCREEN

#include "../Game/Menus/CkBaseMenu.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class QuadClass;
}


using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Input;

namespace CloudberryKingdom
{
	class ControlScreen : public CkBaseMenu
	{
	private:
		std::shared_ptr<QuadClass> BackgroundQuad;

	public:
		ControlScreen( int Control );

#if defined(PC_VERSION)
	private:
		std::shared_ptr<QuadClass> MakeQuad( Keys key );
#endif
	public:
		virtual void Init();

#if defined(PC_VERSION)
	private:
		void SetPos();
#endif

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef CONTROLSCREEN
