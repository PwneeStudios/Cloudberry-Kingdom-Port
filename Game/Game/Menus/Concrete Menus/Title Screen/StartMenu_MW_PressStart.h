#ifndef STARTMENU_MW_PRESSSTART
#define STARTMENU_MW_PRESSSTART

#include <global_header.h>

namespace CloudberryKingdom
{
	struct StartMenu_MW_PressStart : public CkBaseMenu
	{
	
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_PressStart( const std::shared_ptr<TitleGameData_MW> &Title );
		void StartMenu_MW_PressStart_Construct( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

		virtual void OnAdd();

	
		std::shared_ptr<EzText> Text;
		int DelayToAllowInput;
	
		virtual void Init();

	
		void SetPos();

	
		virtual void MyPhsxStep();

	
		float t;
	
		virtual void MyDraw();

	
		virtual void OnReturnTo();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STARTMENU_MW_PRESSSTART
