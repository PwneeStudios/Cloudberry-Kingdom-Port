#ifndef SCORESCREEN
#define SCORESCREEN

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ScoreScreen : public CkBaseMenu
	{
	
		struct OnAddHelper : public Lambda
		{
		
			std::shared_ptr<ScoreScreen> ss;

		
			OnAddHelper( const std::shared_ptr<ScoreScreen> &ss );

			void Apply();
		};

	
		struct VariableCoinsLambda : public PlayerIntLambda
		{
		
			StatGroup MyStats;
		
			VariableCoinsLambda( StatGroup MyStats );

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	
		struct VariableTotalCoinsLambda : public PlayerIntLambda
		{
		
			StatGroup MyStats;
		
			VariableTotalCoinsLambda( StatGroup MyStats );

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	
		struct VariableBlobsLambda : public PlayerIntLambda
		{
		
			StatGroup MyStats;
		
			VariableBlobsLambda( StatGroup MyStats );

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	
		struct VariableTotalBlobsLambda : public PlayerIntLambda
		{
		
			StatGroup MyStats;
		
			VariableTotalBlobsLambda( StatGroup MyStats );

			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	
		struct ScoreScreenEndGameHelper : public Lambda
		{
		
			std::shared_ptr<ScoreScreen> ss;
			bool parameter;

		
			ScoreScreenEndGameHelper( const std::shared_ptr<ScoreScreen> &ss, bool parameter );

			void Apply();
		};

	
		struct MenuGo_NewLevelProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<ScoreScreen> ss;

		
			MenuGo_NewLevelProxy( const std::shared_ptr<ScoreScreen> &ss );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct MenuGo_ContinueProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<ScoreScreen> ss;

		
			MenuGo_ContinueProxy( const std::shared_ptr<ScoreScreen> &ss );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct MenuGo_WatchReplayHelper : public Lambda
		{
		
			std::shared_ptr<ScoreScreen> ss;

		
			MenuGo_WatchReplayHelper( const std::shared_ptr<ScoreScreen> &ss );

			void Apply();
		};

	
		struct MenuGo_WatchReplayProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<ScoreScreen> ss;

		
			MenuGo_WatchReplayProxy( const std::shared_ptr<ScoreScreen> &ss );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct MenuGo_SaveProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<ScoreScreen> ss;

		
			MenuGo_SaveProxy( const std::shared_ptr<ScoreScreen> &ss );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		bool _Add_Watch, _Add_Save;
	
		virtual void MakeMenu();

	
		std::shared_ptr<EzSound> ScoreSound, BonusSound;

	
		int DelayPhsx;

		ScoreScreen( bool CallBaseConstructor );
		void ScoreScreen_Construct( bool CallBaseConstructor );

		ScoreScreen( StatGroup group, const std::shared_ptr<GameData> &game );
		void ScoreScreen_Construct( StatGroup group, const std::shared_ptr<GameData> &game );
	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

// Whether to make a menu, or a static text with key bindings
#if defined(PC_VERSION)
	
		static bool AsMenu;
#else
		static bool AsMenu;
#endif

	
		std::shared_ptr<QuadClass> LevelCleared;
	
		Vector2 ShiftAll;
	
		virtual void Init();

	
		void SetPos();

		std::shared_ptr<FancyVector2> zoom;
	
		static bool UseZoomIn;

	
		StatGroup MyStatGroup;
	
		virtual void OnAdd();

	
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

	
		int LastActive;
		bool ShouldSkip();

	
		void GUI_Phsx();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SCORESCREEN
