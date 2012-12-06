#ifndef STARTLEVELMENU
#define STARTLEVELMENU

#include <global_header.h>

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
		class LaunchProxy : public Lambda_1<std::shared_ptr<MenuItem> >
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
		std::shared_ptr<Lambda_1<std::shared_ptr<LevelItem> > > StartFunc;
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
