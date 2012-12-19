#ifndef ARCADEMENU
#define ARCADEMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ArcadeItem : public MenuItem
	{
	
		boost::shared_ptr<Challenge> MyChallenge;
		boost::shared_ptr<Awardment> MyPrereq;
		bool Locked;

		ArcadeItem( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<Challenge> &MyChallenge, const boost::shared_ptr<Awardment> &MyPrereq );
	};

	struct ArcadeBaseMenu : public CkBaseMenu
	{
	
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
	
		struct GoProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ArcadeMenu> am;

		
			GoProxy( const boost::shared_ptr<ArcadeMenu> &am );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		bool Long;

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void OnReturnTo();

	
		void SetLockColors();

	
		ArcadeMenu();
		boost::shared_ptr<ArcadeMenu> ArcadeMenu_Construct();

		virtual void Init();

	
		void SetParams();

		Vector2 GetGoalPos();

		boost::shared_ptr<MenuItem> AddChallenge( const boost::shared_ptr<Challenge> &challenge, const boost::shared_ptr<Awardment> &prereq, const boost::shared_ptr<Awardment> &goal, const std::wstring &itemname );

	
		virtual void Go( const boost::shared_ptr<MenuItem> &item );

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ARCADEMENU
