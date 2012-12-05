#ifndef STARTMENU_MW_CINEMATICS
#define STARTMENU_MW_CINEMATICS

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class TitleGameData_MW;
}




namespace CloudberryKingdom
{
	class CinematicsLevelItem : public MenuItem
	{
	public:
		std::wstring Movie;

		CinematicsLevelItem( const std::shared_ptr<EzText> &Text, const std::wstring &Movie );

	private:
		void InitializeInstanceFields();
	};

	class StartMenu_MW_Cinematics : public StartMenu
	{
	private:
		class CinematicsGoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<StartMenu_MW_Cinematics> cine;
		public:
			CinematicsGoLambda( const std::shared_ptr<StartMenu_MW_Cinematics> &cine );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	public:
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_Cinematics( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

	protected:
		void SetText( const std::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void OnAdd();

		virtual void Init();

	protected:
		virtual void CreateMenu();

		void MakeHeader();

	public:
		void Go( const std::shared_ptr<MenuItem> &item );

	private:
		void SetPos();
	};
}


#endif	//#ifndef STARTMENU_MW_CINEMATICS
