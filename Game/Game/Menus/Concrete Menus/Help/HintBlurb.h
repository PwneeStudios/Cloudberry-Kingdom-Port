#ifndef HINTBLURB
#define HINTBLURB

#include <global_header.h>

namespace CloudberryKingdom
{

	struct HintBlurb : public CkBaseMenu
	{
	
		std::shared_ptr<QuadClass> Backdrop;

	
		HintBlurb();
		void HintBlurb_Construct();

	
		virtual void MakeBackdrop();

	
		virtual void OnAdd();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		std::shared_ptr<EzText> Text;
	
		void SetText( const std::wstring &text );

	
		virtual void SizeAndPosition();

		int Step;
		virtual void MyPhsxStep();

		virtual bool ShouldDie();

	
		void Kill();
		void Kill( bool sound );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HINTBLURB
