#ifndef STARTLEVELMENU
#define STARTLEVELMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	struct LevelItem : public MenuItem
	{
	
		int StartLevel, MenuIndex;

		LevelItem( const std::shared_ptr<EzText> &Text, int StartLevel, int MenuIndex, bool Locked );
	};

	struct StartLevelMenu : public CkBaseMenu
	{
	
		struct GameReturnProxy : public LambdaFunc<bool>
		{
		
			std::shared_ptr<StartLevelMenu> slm;

		
			GameReturnProxy( const std::shared_ptr<StartLevelMenu> &slm );

			bool Apply();
		};

	
		struct LaunchHelper : public Lambda
		{
		
			std::shared_ptr<StartLevelMenu> slm;
			std::shared_ptr<LevelItem> litem;

		
			LaunchHelper( const std::shared_ptr<StartLevelMenu> &slm, const std::shared_ptr<LevelItem> &litem );

			void Apply();
		};

	
		struct LaunchProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<StartLevelMenu> slm;

		
			LaunchProxy( const std::shared_ptr<StartLevelMenu> &slm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

		/// <summary>
		/// The last difficulty selected via the difficulty select menu
		/// </summary>
	
		static int PreviousMenuIndex;

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	
		std::shared_ptr<Lambda_1<std::shared_ptr<LevelItem> > > StartFunc;
		std::shared_ptr<Lambda> ReturnFunc;

	
		virtual void Launch( const std::shared_ptr<MenuItem> &item );

		virtual bool GameReturn();

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		std::vector<int> Levels;
		//string[] LevelStr = { "Normal", "Advanced", "Expert", "Master" };
	
		virtual std::vector<std::wstring> GetNames();

		int HighestLevel;
		StartLevelMenu();
		StartLevelMenu( int HighestLevel );

		int IndexCutoff;

		void Initialize();

	
		void SetPos();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STARTLEVELMENU
