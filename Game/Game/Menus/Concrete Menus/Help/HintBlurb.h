#ifndef HINTBLURB
#define HINTBLURB

#include <global_header.h>

namespace CloudberryKingdom
{

	struct HintBlurb : public CkBaseMenu
	{
	
		boost::shared_ptr<QuadClass> Backdrop;

	
		HintBlurb();
		boost::shared_ptr<HintBlurb> HintBlurb_Construct();

	
		virtual void MakeBackdrop();

	
		virtual void OnAdd();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		boost::shared_ptr<EzText> Text;
	
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
