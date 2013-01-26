#ifndef STARTMENU_MW_CINEMATICS
#define STARTMENU_MW_CINEMATICS

#include <global_header.h>

namespace CloudberryKingdom
{
	
	struct CinematicsLevelItem : public MenuItem
	{
	
		std::wstring Movie;

		CinematicsLevelItem( const boost::shared_ptr<EzText> &Text, const std::wstring &Movie );
		boost::shared_ptr<CinematicsLevelItem> CinematicsLevelItem_Construct( const boost::shared_ptr<EzText> &Text, const std::wstring &Movie );
	
		void InitializeInstanceFields();

	};

	struct StartMenu_MW_Cinematics : public StartMenu
	{

		virtual ~StartMenu_MW_Cinematics() { }

		using StartMenu::SlideOut;
		using StartMenu::SlideIn;
		using StartMenu::Call;

		struct CinematicsGoLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartMenu_MW_Cinematics> cine;
		
			CinematicsGoLambda( const boost::shared_ptr<StartMenu_MW_Cinematics> &cine );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		boost::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_Cinematics( const boost::shared_ptr<TitleGameData_MW> &Title );
		boost::shared_ptr<StartMenu_MW_Cinematics> StartMenu_MW_Cinematics_Construct( const boost::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		void SetText( const boost::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

		virtual void Init();

	
		virtual void CreateMenu();

		void MakeHeader();

	
		void Go( const boost::shared_ptr<MenuItem> &item );

	
		void SetPos();
	};
}


#endif	//#ifndef STARTMENU_MW_CINEMATICS
