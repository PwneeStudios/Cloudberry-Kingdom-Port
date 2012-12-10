#ifndef STARTMENU_MW_CAMPAIGN
#define STARTMENU_MW_CAMPAIGN

#include <global_header.h>

namespace CloudberryKingdom
{
	struct PlayerData;
}

namespace CloudberryKingdom
{
	struct EzText;
}

namespace CloudberryKingdom
{
	struct MenuItem;
}

namespace CloudberryKingdom
{
	struct TitleGameData_MW;
}




namespace CloudberryKingdom
{
	struct CampaignChapterItem : public MenuItem
	{
	
		struct CampaignLevelsLambda : public PlayerIntLambda
		{
		
			CampaignLevelsLambda();

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	
		int Chapter;

		CampaignChapterItem( const std::shared_ptr<EzText> &Text, int Chapter );


	
		void InitializeInstanceFields();
	};

	struct StartMenu_MW_Campaign : public StartMenu
	{
	
		struct CampaignGoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<StartMenu_MW_Campaign> cine;
		
			CampaignGoLambda( const std::shared_ptr<StartMenu_MW_Campaign> &cine );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct GoLambda : public Lambda
		{
		
			std::shared_ptr<StartMenu_MW_Campaign> sm;
		
			GoLambda( const std::shared_ptr<StartMenu_MW_Campaign> &sm );

			void Apply();
		};

	
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_Campaign( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		void SetText( const std::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

		virtual void Init();

	
		virtual void CreateMenu();

		void MakeHeader();

	
		void Go( const std::shared_ptr<MenuItem> &item );

		int _StartLevel;
		void Go( int StartLevel );

		void SetPos_NoCinematic();

		void SetPos_WithCinematic();
	};
}


#endif	//#ifndef STARTMENU_MW_CAMPAIGN
