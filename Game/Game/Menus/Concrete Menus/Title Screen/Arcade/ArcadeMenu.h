#ifndef ARCADEMENU
#define ARCADEMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ArcadeItem : public MenuItem
	{
	
		boost::shared_ptr<Challenge> MyChallenge;
		boost::shared_ptr<Awardment> MyPrereq;
		bool IsLocked();

		ArcadeItem( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<Challenge> &MyChallenge, const boost::shared_ptr<Awardment> &MyPrereq );
		boost::shared_ptr<ArcadeItem> ArcadeItem_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<Challenge> &MyChallenge, const boost::shared_ptr<Awardment> &MyPrereq );

	};

	struct ArcadeBaseMenu : public CkBaseMenu
	{

		virtual ~ArcadeBaseMenu() { }
	
		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;

		struct PlayGameProxy : public Lambda
		{
		
			boost::shared_ptr<ArcadeBaseMenu> abm;

		
			PlayGameProxy( const boost::shared_ptr<ArcadeBaseMenu> &abm );

			void Apply();
		};

	
		struct StartFuncProxy : public Lambda_1<boost::shared_ptr<LevelItem> >
		{
		
			boost::shared_ptr<ArcadeBaseMenu> abm;

		
			StartFuncProxy( const boost::shared_ptr<ArcadeBaseMenu> &abm );

			void Apply( const boost::shared_ptr<LevelItem> &levelitem );
		};

	
		boost::shared_ptr<LevelItem> SelectedItem;
		boost::shared_ptr<ArcadeItem> MyArcadeItem;

		boost::shared_ptr<ArcadeBaseMenu> ArcadeBaseMenu_Construct();

		virtual void OnAdd();

	
		virtual void StartFunc( const boost::shared_ptr<LevelItem> &item );

		virtual void PlayGame();

	
		virtual void Release();
	};


	struct ArcadeMenu : public ArcadeBaseMenu
	{

		virtual ~ArcadeMenu() { }

		struct OnSelectProxy : public Lambda
		{
		
			boost::shared_ptr<ArcadeMenu> am;
		
			OnSelectProxy( const boost::shared_ptr<ArcadeMenu> &am );

			void Apply();
		};

		struct GoProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ArcadeMenu> am;

		
			GoProxy( const boost::shared_ptr<ArcadeMenu> &am );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		bool Long;

		static void CheckForArcadeUnlocks(boost::shared_ptr<ScoreEntry> score);

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void OnReturnTo();

	
		void SetLockColors();

        static boost::shared_ptr<BobPhsx> JetpackWheelie;
        static boost::shared_ptr<BobPhsx> BigBouncy;
        static boost::shared_ptr<BobPhsx> Ultimate;

        static std::vector<std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > > HeroArcadeList;
	
		ArcadeMenu();
		boost::shared_ptr<ArcadeMenu> ArcadeMenu_Construct();

		static void StaticInit();

        boost::shared_ptr<EzText> RequiredText, RequiredText2;
        boost::shared_ptr<QuadClass> TextBack;

		virtual void Init();

	
		void SetParams();

		Vector2 GetGoalPos();

		boost::shared_ptr<MenuItem> AddChallenge( const boost::shared_ptr<Challenge> &challenge, const boost::shared_ptr<Awardment> &prereq, const std::wstring &itemname );

		void UpdateAfterPlaying();
        bool Lock;
        void OnSelect();
	
		virtual void Go( const boost::shared_ptr<MenuItem> &item );

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ARCADEMENU
