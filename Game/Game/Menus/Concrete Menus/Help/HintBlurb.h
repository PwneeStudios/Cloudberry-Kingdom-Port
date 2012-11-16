#ifndef HINTBLURB
#define HINTBLURB

#include "../Game/Menus/CkBaseMenu.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include <string>
#include <vector>
#include <tchar.h>

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class HintBlurb : public CkBaseMenu
	{
	protected:
		std::shared_ptr<QuadClass> Backdrop;

	public:
		HintBlurb();

	protected:
		virtual void MakeBackdrop();

	public:
		virtual void OnAdd();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

	protected:
		std::shared_ptr<EzText> Text;
	public:
		void SetText( const std::wstring &text );

	protected:
		virtual void SizeAndPosition();

		int Step;
		virtual void MyPhsxStep();

		virtual bool ShouldDie();

	public:
		void Kill();
		void Kill( bool sound );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HINTBLURB
