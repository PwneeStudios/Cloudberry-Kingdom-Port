#ifndef ARCADEMENU
#define ARCADEMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Challenge;
}

namespace CloudberryKingdom
{
	struct Awardment;
}

namespace CloudberryKingdom
{
	struct EzText;
}

namespace CloudberryKingdom
{
	struct LevelItem;
}

namespace CloudberryKingdom
{
	struct MenuItem;
}




namespace CloudberryKingdom
{
	struct ArcadeItem : public MenuItem
	{
	
		std::shared_ptr<Challenge> MyChallenge;
		std::shared_ptr<Awardment> MyPrereq;
		bool Locked;

		ArcadeItem( const std::shared_ptr<EzText> &Text, const std::shared_ptr<Challenge> &MyChallenge, const std::shared_ptr<Awardment> &MyPrereq );
	};

	struct ArcadeBaseMenu : public CkBaseMenu
	{
	
		struct PlayGameProxy : public Lambda
		{
		
			std::shared_ptr<ArcadeBaseMenu> abm;

		
			PlayGameProxy( const std::shared_ptr<ArcadeBaseMenu> &abm );

			void Apply();
		};

	
		struct StartFuncProxy : public Lambda_1<std::shared_ptr<LevelItem> >
		{
		
			std::shared_ptr<ArcadeBaseMenu> abm;

		
			StartFuncProxy( const std::shared_ptr<ArcadeBaseMenu> &abm );

			void Apply( const std::shared_ptr<LevelItem> &levelitem );
		};

	
		std::shared_ptr<LevelItem> SelectedItem;
		std::shared_ptr<ArcadeItem> MyArcadeItem;

		virtual void OnAdd();

	
		virtual void StartFunc( const std::shared_ptr<LevelItem> &item );

		virtual void PlayGame();

	
		virtual void Release();
	};


	struct ArcadeMenu : public ArcadeBaseMenu
	{
	
		struct GoProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<ArcadeMenu> am;

		
			GoProxy( const std::shared_ptr<ArcadeMenu> &am );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		bool Long;

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void OnReturnTo();

	
		void SetLockColors();

	
		ArcadeMenu();

		virtual void Init();

	
		void SetParams();

		Vector2 GetGoalPos();

		std::shared_ptr<MenuItem> AddChallenge( const std::shared_ptr<Challenge> &challenge, const std::shared_ptr<Awardment> &prereq, const std::shared_ptr<Awardment> &goal, const std::wstring &itemname );

	
		virtual void Go( const std::shared_ptr<MenuItem> &item );

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ARCADEMENU
