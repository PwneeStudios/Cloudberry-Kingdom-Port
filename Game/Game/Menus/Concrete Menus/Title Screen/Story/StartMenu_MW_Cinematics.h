#ifndef STARTMENU_MW_CINEMATICS
#define STARTMENU_MW_CINEMATICS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct CinematicsLevelItem : public MenuItem
	{
	
		std::wstring Movie;

		CinematicsLevelItem( const std::shared_ptr<EzText> &Text, const std::wstring &Movie );

	
		void InitializeInstanceFields();
	};

	struct StartMenu_MW_Cinematics : public StartMenu
	{
	
		struct CinematicsGoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<StartMenu_MW_Cinematics> cine;
		
			CinematicsGoLambda( const std::shared_ptr<StartMenu_MW_Cinematics> &cine );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_Cinematics( const std::shared_ptr<TitleGameData_MW> &Title );
		std::shared_ptr<StartMenu_MW_Cinematics> StartMenu_MW_Cinematics_Construct( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		void SetText( const std::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

		virtual void Init();

	
		virtual void CreateMenu();

		void MakeHeader();

	
		void Go( const std::shared_ptr<MenuItem> &item );

	
		void SetPos();
	};
}


#endif	//#ifndef STARTMENU_MW_CINEMATICS
