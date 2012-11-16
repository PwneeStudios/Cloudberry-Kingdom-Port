#ifndef MENUSCROLLBAR
#define MENUSCROLLBAR

#include "MenuSlider.h"
#include "../Game/Tools/Resources.h"
#include "../Properties/Resources.Designer.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class Camera;
}


using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Input;

namespace CloudberryKingdom
{
	class MenuScrollBar : public MenuSlider
	{
	public:
		MenuScrollBar();

		std::shared_ptr<EzTexture> Normal, Held;
	protected:
		virtual void InitializeSlider();

	public:
		Vector2 StartPlus;
		Vector2 EndPlus;
		bool DrawEnds;
		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUSCROLLBAR
