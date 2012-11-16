#ifndef ARCADEMENU
#define ARCADEMENU

#include "../Game/Menus/Menu Components/MenuItem.h"
#include "../Game/Menus/CkBaseMenu.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Core/Lambdas/Lambda_1.h"
#include "../Game/Menus/Concrete Menus/CharacterSelect/CustomizeMenu.h"
#include "../Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomUpgrades_GUI.h"
#include <string>
#include <vector>
#include <tchar.h>

namespace CloudberryKingdom
{
	class Challenge;
}

namespace CloudberryKingdom
{
	class Awardment;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class LevelItem;
}

namespace CloudberryKingdom
{
	class MenuItem;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class ArcadeItem : public MenuItem
	{
	public:
		std::shared_ptr<Challenge> MyChallenge;
		std::shared_ptr<Awardment> MyPrereq;
		bool Locked;

		ArcadeItem( const std::shared_ptr<EzText> &Text, const std::shared_ptr<Challenge> &MyChallenge, const std::shared_ptr<Awardment> &MyPrereq );
	};

	class ArcadeBaseMenu : public CkBaseMenu
	{
	private:
		class PlayGameProxy : public Lambda
		{
		private:
			std::shared_ptr<ArcadeBaseMenu> abm;

		public:
			PlayGameProxy( const std::shared_ptr<ArcadeBaseMenu> &abm );

			void Apply();
		};

	protected:
		class StartFuncProxy : public Lambda_1<LevelItem*>
		{
		private:
			std::shared_ptr<ArcadeBaseMenu> abm;

		public:
			StartFuncProxy( const std::shared_ptr<ArcadeBaseMenu> &abm );

			void Apply( const std::shared_ptr<LevelItem> &levelitem );
		};

	public:
		std::shared_ptr<LevelItem> SelectedItem;
		std::shared_ptr<ArcadeItem> MyArcadeItem;

		virtual void OnAdd();

	protected:
		virtual void StartFunc( const std::shared_ptr<LevelItem> &item );

		virtual void PlayGame();

	public:
		virtual void Release();
	};


	class ArcadeMenu : public ArcadeBaseMenu
	{
	private:
		class GoProxy : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<ArcadeMenu> am;

		public:
			GoProxy( const std::shared_ptr<ArcadeMenu> &am );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		bool Long;

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void OnReturnTo();

	private:
		void SetLockColors();

	public:
		ArcadeMenu();

		virtual void Init();

	private:
		void SetParams();

		Vector2 GetGoalPos();

		std::shared_ptr<MenuItem> AddChallenge( const std::shared_ptr<Challenge> &challenge, const std::shared_ptr<Awardment> &prereq, const std::shared_ptr<Awardment> &goal, const std::wstring &itemname );

	public:
		virtual void Go( const std::shared_ptr<MenuItem> &item );

	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ARCADEMENU
