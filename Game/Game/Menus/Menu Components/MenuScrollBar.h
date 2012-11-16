#ifndef MENUSCROLLBAR
#define MENUSCROLLBAR

#include <global_header.h>

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
