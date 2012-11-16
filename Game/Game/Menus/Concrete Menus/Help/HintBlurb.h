#ifndef HINTBLURB
#define HINTBLURB

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class EzText;
}




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
