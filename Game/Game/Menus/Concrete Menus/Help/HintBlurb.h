#ifndef HINTBLURB
#define HINTBLURB

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Menus/CkBaseMenu.h"


namespace CloudberryKingdom
{

	struct HintBlurb : public CkBaseMenu
	{

		virtual ~HintBlurb()
		{
#ifdef BOOST_BIN
			OnDestructor( "HintBlurb" );
#endif
		}


		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;

		boost::shared_ptr<QuadClass> Backdrop;
	
		HintBlurb();
		boost::shared_ptr<HintBlurb> HintBlurb_Construct();
	
		virtual void MakeBackdrop();
	
		virtual void OnAdd();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
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
