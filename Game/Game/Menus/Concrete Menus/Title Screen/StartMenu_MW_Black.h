#ifndef STARTMENU_MW_BLACK
#define STARTMENU_MW_BLACK

#include <global_header.h>

namespace CloudberryKingdom
{
	struct QuadClass;
}




namespace CloudberryKingdom
{
	struct StartMenu_MW_Black : public CkBaseMenu
	{
	
		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

		virtual void OnAdd();

		StartMenu_MW_Black();

	
		std::shared_ptr<QuadClass> Black;
	
		virtual void Init();

	
		void BlackBox();

	
		void SlideFromRight();

	
		virtual void MyPhsxStep();

	
		virtual void OnReturnTo();
	};
}


#endif	//#ifndef STARTMENU_MW_BLACK
