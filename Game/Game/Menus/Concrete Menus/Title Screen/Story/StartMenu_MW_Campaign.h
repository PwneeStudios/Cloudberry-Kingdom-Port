#ifndef STARTMENU_MW_CAMPAIGN
#define STARTMENU_MW_CAMPAIGN

#include <global_header.h>

namespace CloudberryKingdom
{
	struct CampaignChapterItem : public MenuItem
	{
	
		struct CampaignLevelsLambda : public PlayerIntLambda
		{
		
			virtual ~CampaignLevelsLambda() { }

			CampaignLevelsLambda();

			virtual int Apply( const boost::shared_ptr<PlayerData> &p );
		};
	
		int Chapter;
		bool Locked;

		CampaignChapterItem( const boost::shared_ptr<EzText> &Text, int Chapter );
		boost::shared_ptr<CampaignChapterItem> CampaignChapterItem_Construct( const boost::shared_ptr<EzText> &Text, int Chapter );

		void InitializeInstanceFields();

		void UpdateLock();
	};

	struct StartMenu_MW_Campaign : public StartMenu
	{

		virtual ~StartMenu_MW_Campaign() { }

		using StartMenu::SlideOut;
		using StartMenu::SlideIn;
		using StartMenu::Call;

		void OnReturnTo();
		void Update();

		struct OnReturnFromGameLambda : public Lambda
		{
		
			boost::shared_ptr<StartMenu_MW_Campaign> sm;
		
			OnReturnFromGameLambda( const boost::shared_ptr<StartMenu_MW_Campaign> &sm );

			void Apply();
		};


		struct CampaignGoLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartMenu_MW_Campaign> cine;
		
			CampaignGoLambda( const boost::shared_ptr<StartMenu_MW_Campaign> &cine );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct GoLambda : public Lambda
		{
		
			boost::shared_ptr<StartMenu_MW_Campaign> sm;
		
			GoLambda( const boost::shared_ptr<StartMenu_MW_Campaign> &sm );

			void Apply();
		};

	
		boost::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_Campaign( const boost::shared_ptr<TitleGameData_MW> &Title );
		boost::shared_ptr<StartMenu_MW_Campaign> StartMenu_MW_Campaign_Construct( const boost::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		void SetText( const boost::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

		virtual void Init();

	
		virtual void CreateMenu();

		void MakeHeader();

	
		void Go( const boost::shared_ptr<MenuItem> &item );

		int _StartLevel;
		void Go( int StartLevel );

		void OnReturnFromGame();

		void SetPos_NoCinematic();

		void SetPos_WithCinematic();
	};
}


#endif	//#ifndef STARTMENU_MW_CAMPAIGN
