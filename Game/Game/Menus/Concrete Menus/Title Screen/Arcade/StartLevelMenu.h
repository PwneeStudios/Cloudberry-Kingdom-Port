#ifndef STARTLEVELMENU
#define STARTLEVELMENU

#include "../Game/Menus/Menu Components/MenuItem.h"
#include "../Game/Menus/CkBaseMenu.h"
#include "../Core/Lambdas/LambdaFunc.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Core/Lambdas/Lambda_1.h"
#include <string>
#include <tchar.h>

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
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class Lambda;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class LevelItem : public MenuItem
	{
	public:
		int StartLevel, MenuIndex;

		LevelItem( const std::shared_ptr<EzText> &Text, int StartLevel, int MenuIndex, bool Locked );
	};

	class StartLevelMenu : public CkBaseMenu
	{
	private:
		class GameReturnProxy : public LambdaFunc<bool>
		{
		private:
			std::shared_ptr<StartLevelMenu> slm;

		public:
			GameReturnProxy( const std::shared_ptr<StartLevelMenu> &slm );

			bool Apply();
		};

	private:
		class LaunchHelper : public Lambda
		{
		private:
			std::shared_ptr<StartLevelMenu> slm;
			std::shared_ptr<LevelItem> litem;

		public:
			LaunchHelper( const std::shared_ptr<StartLevelMenu> &slm, const std::shared_ptr<LevelItem> &litem );

			void Apply();
		};

	private:
		class LaunchProxy : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<StartLevelMenu> slm;

		public:
			LaunchProxy( const std::shared_ptr<StartLevelMenu> &slm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

		/// <summary>
		/// The last difficulty selected via the difficulty select menu
		/// </summary>
	public:
		static int PreviousMenuIndex;

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	public:
		std::shared_ptr<Lambda_1<LevelItem*> > StartFunc;
		std::shared_ptr<Lambda> ReturnFunc;

	protected:
		virtual void Launch( const std::shared_ptr<MenuItem> &item );

		virtual bool GameReturn();

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	private:
		std::vector<int> Levels;
		//string[] LevelStr = { "Normal", "Advanced", "Expert", "Master" };
	public:
		virtual std::vector<std::wstring> GetNames();

		int HighestLevel;
		StartLevelMenu();
		StartLevelMenu( int HighestLevel );

		int IndexCutoff;

		void Initialize();

	private:
		void SetPos();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STARTLEVELMENU
