#ifndef SCORESCREEN
#define SCORESCREEN

#include <global_header.h>

namespace CloudberryKingdom
{
	class ScoreScreen : public CkBaseMenu
	{
	private:
		class OnAddHelper : public Lambda
		{
		private:
			std::shared_ptr<ScoreScreen> ss;

		public:
			OnAddHelper( const std::shared_ptr<ScoreScreen> &ss );

			void Apply();
		};

	private:
		class VariableCoinsLambda : public PlayerIntLambda
		{
		private:
			StatGroup MyStats;
		public:
			VariableCoinsLambda( StatGroup MyStats );

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	private:
		class VariableTotalCoinsLambda : public PlayerIntLambda
		{
		private:
			StatGroup MyStats;
		public:
			VariableTotalCoinsLambda( StatGroup MyStats );

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	private:
		class VariableBlobsLambda : public PlayerIntLambda
		{
		private:
			StatGroup MyStats;
		public:
			VariableBlobsLambda( StatGroup MyStats );

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	private:
		class VariableTotalBlobsLambda : public PlayerIntLambda
		{
		private:
			StatGroup MyStats;
		public:
			VariableTotalBlobsLambda( StatGroup MyStats );

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	private:
		class ScoreScreenEndGameHelper : public Lambda
		{
		private:
			std::shared_ptr<ScoreScreen> ss;
			bool parameter;

		public:
			ScoreScreenEndGameHelper( const std::shared_ptr<ScoreScreen> &ss, bool parameter );

			void Apply();
		};

	private:
		class MenuGo_NewLevelProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<ScoreScreen> ss;

		public:
			MenuGo_NewLevelProxy( const std::shared_ptr<ScoreScreen> &ss );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class MenuGo_ContinueProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<ScoreScreen> ss;

		public:
			MenuGo_ContinueProxy( const std::shared_ptr<ScoreScreen> &ss );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class MenuGo_WatchReplayHelper : public Lambda
		{
		private:
			std::shared_ptr<ScoreScreen> ss;

		public:
			MenuGo_WatchReplayHelper( const std::shared_ptr<ScoreScreen> &ss );

			void Apply();
		};

	private:
		class MenuGo_WatchReplayProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<ScoreScreen> ss;

		public:
			MenuGo_WatchReplayProxy( const std::shared_ptr<ScoreScreen> &ss );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class MenuGo_SaveProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<ScoreScreen> ss;

		public:
			MenuGo_SaveProxy( const std::shared_ptr<ScoreScreen> &ss );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		bool _Add_Watch, _Add_Save;
	protected:
		virtual void MakeMenu();

	private:
		std::shared_ptr<EzSound> ScoreSound, BonusSound;

	public:
		int DelayPhsx;

		ScoreScreen( bool CallBaseConstructor );

		ScoreScreen( StatGroup group, const std::shared_ptr<GameData> &game );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

// Whether to make a menu, or a static text with key bindings
#if defined(PC_VERSION)
	private:
		static bool AsMenu;
#else
		static bool AsMenu;
#endif

	protected:
		std::shared_ptr<QuadClass> LevelCleared;
	private:
		Vector2 ShiftAll;
	public:
		virtual void Init();

	private:
		void SetPos();

		std::shared_ptr<FancyVector2> zoom;
	public:
		static bool UseZoomIn;

	protected:
		StatGroup MyStatGroup;
	public:
		virtual void OnAdd();

	protected:
		virtual void MyDraw();

		virtual void MyPhsxStep();

		/// <summary>
		/// Play another level with the same seed
		/// </summary>
		void MenuGo_NewLevel( const std::shared_ptr<MenuItem> &item );

		/// <summary>
		/// Called when 'Continue' is selected from the menu.
		/// The Score Screen slides out and the current game's EndGame function is called.
		/// </summary>
		virtual void MenuGo_Continue( const std::shared_ptr<MenuItem> &item );

		/// <summary>
		/// Called when 'Exit Freeplay' is selected from the menu.
		/// The Score Screen slides out and the current game's EndGame function is called.
		/// </summary>
		virtual bool MenuGo_ExitFreeplay( const std::shared_ptr<Menu> &menu );

		void MenuGo_Stats( const std::shared_ptr<MenuItem> &item );

		/// <summary>
		/// Called when 'Watch Replay' is selected from the menu.
		/// The level's replay is loaded, with the level's current information saved.
		/// </summary>
		void MenuGo_WatchReplay( const std::shared_ptr<MenuItem> &item );

		void MenuGo_Save( const std::shared_ptr<MenuItem> &item );

	private:
		int LastActive;
		bool ShouldSkip();

	public:
		void GUI_Phsx();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SCORESCREEN
