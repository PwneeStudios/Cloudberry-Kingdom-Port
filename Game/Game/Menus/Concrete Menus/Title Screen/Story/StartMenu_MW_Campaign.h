#ifndef STARTMENU_MW_CAMPAIGN
#define STARTMENU_MW_CAMPAIGN

#include <global_header.h>

namespace CloudberryKingdom
{
	class PlayerData;
}

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
	class CampaignChapterItem : public MenuItem
	{
	private:
		class CampaignLevelsLambda : public PlayerIntLambda
		{
		public:
			CampaignLevelsLambda();

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	public:
		int Chapter;

		CampaignChapterItem( const std::shared_ptr<EzText> &Text, int Chapter );


	private:
		void InitializeInstanceFields();
	};

	class StartMenu_MW_Campaign : public StartMenu
	{
	private:
		class CampaignGoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<StartMenu_MW_Campaign> cine;
		public:
			CampaignGoLambda( const std::shared_ptr<StartMenu_MW_Campaign> &cine );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class GoLambda : public Lambda
		{
		private:
			std::shared_ptr<StartMenu_MW_Campaign> sm;
		public:
			GoLambda( const std::shared_ptr<StartMenu_MW_Campaign> &sm );

			void Apply();
		};

	public:
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_Campaign( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	protected:
		void SetText( const std::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void OnAdd();

		virtual void Init();

	protected:
		virtual void CreateMenu();

		void MakeHeader();

	private:
		void Go( const std::shared_ptr<MenuItem> &item );

		int _StartLevel;
		void Go( int StartLevel );

		void SetPos_NoCinematic();

		void SetPos_WithCinematic();
	};
}


#endif	//#ifndef STARTMENU_MW_CAMPAIGN
