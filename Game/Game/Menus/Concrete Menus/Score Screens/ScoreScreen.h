#ifndef SCORESCREEN
#define SCORESCREEN

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ScoreScreen : public CkBaseMenu
	{
	
		struct OnAddHelper : public Lambda
		{
		
			boost::shared_ptr<ScoreScreen> ss;

		
			OnAddHelper( const boost::shared_ptr<ScoreScreen> &ss );

			void Apply();
		};

	
		struct VariableCoinsLambda : public PlayerIntLambda
		{
		
			StatGroup MyStats;
		
			VariableCoinsLambda( StatGroup MyStats );

			virtual int Apply( const boost::shared_ptr<PlayerData> &p );
		};
	
		struct VariableTotalCoinsLambda : public PlayerIntLambda
		{
		
			StatGroup MyStats;
		
			VariableTotalCoinsLambda( StatGroup MyStats );

			virtual int Apply( const boost::shared_ptr<PlayerData> &p );
		};
	
		struct VariableBlobsLambda : public PlayerIntLambda
		{
		
			StatGroup MyStats;
		
			VariableBlobsLambda( StatGroup MyStats );

			virtual int Apply( const boost::shared_ptr<PlayerData> &p );
		};
	
		struct VariableTotalBlobsLambda : public PlayerIntLambda
		{
		
			StatGroup MyStats;
		
			VariableTotalBlobsLambda( StatGroup MyStats );

			virtual int Apply( const boost::shared_ptr<PlayerData> &p );
		};

	
		struct ScoreScreenEndGameHelper : public Lambda
		{
		
			boost::shared_ptr<ScoreScreen> ss;
			bool parameter;

		
			ScoreScreenEndGameHelper( const boost::shared_ptr<ScoreScreen> &ss, bool parameter );

			void Apply();
		};

	
		struct MenuGo_NewLevelProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ScoreScreen> ss;

		
			MenuGo_NewLevelProxy( const boost::shared_ptr<ScoreScreen> &ss );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct MenuGo_ContinueProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ScoreScreen> ss;

		
			MenuGo_ContinueProxy( const boost::shared_ptr<ScoreScreen> &ss );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct MenuGo_WatchReplayHelper : public Lambda
		{
		
			boost::shared_ptr<ScoreScreen> ss;

		
			MenuGo_WatchReplayHelper( const boost::shared_ptr<ScoreScreen> &ss );

			void Apply();
		};

	
		struct MenuGo_WatchReplayProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ScoreScreen> ss;

		
			MenuGo_WatchReplayProxy( const boost::shared_ptr<ScoreScreen> &ss );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct MenuGo_SaveProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ScoreScreen> ss;

		
			MenuGo_SaveProxy( const boost::shared_ptr<ScoreScreen> &ss );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		bool _Add_Watch, _Add_Save;
	
		virtual void MakeMenu();

	
		boost::shared_ptr<EzSound> ScoreSound, BonusSound;

	
		int DelayPhsx;

		ScoreScreen( bool CallBaseConstructor );
		boost::shared_ptr<ScoreScreen> ScoreScreen_Construct( bool CallBaseConstructor );

		ScoreScreen( StatGroup group, const boost::shared_ptr<GameData> &game );
		boost::shared_ptr<ScoreScreen> ScoreScreen_Construct( StatGroup group, const boost::shared_ptr<GameData> &game );
	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

// Whether to make a menu, or a static text with key bindings
#if defined(PC_VERSION)
	
		static bool AsMenu;
#else
		static bool AsMenu;
#endif

	
		boost::shared_ptr<QuadClass> LevelCleared;
	
		Vector2 ShiftAll;
	
		virtual void Init();

	
		void SetPos();

		boost::shared_ptr<FancyVector2> zoom;
	
		static bool UseZoomIn;

	
		StatGroup MyStatGroup;
	
		virtual void OnAdd();

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

		/// <summary>
		/// Play another level with the same seed
		/// </summary>
		void MenuGo_NewLevel( const boost::shared_ptr<MenuItem> &item );

		/// <summary>
		/// Called when 'Continue' is selected from the menu.
		/// The Score Screen slides out and the current game's EndGame function is called.
		/// </summary>
		virtual void MenuGo_Continue( const boost::shared_ptr<MenuItem> &item );

		/// <summary>
		/// Called when 'Exit Freeplay' is selected from the menu.
		/// The Score Screen slides out and the current game's EndGame function is called.
		/// </summary>
		virtual bool MenuGo_ExitFreeplay( const boost::shared_ptr<Menu> &menu );

		void MenuGo_Stats( const boost::shared_ptr<MenuItem> &item );

		/// <summary>
		/// Called when 'Watch Replay' is selected from the menu.
		/// The level's replay is loaded, with the level's current information saved.
		/// </summary>
		void MenuGo_WatchReplay( const boost::shared_ptr<MenuItem> &item );

		void MenuGo_Save( const boost::shared_ptr<MenuItem> &item );

	
		int LastActive;
		bool ShouldSkip();

	
		void GUI_Phsx();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SCORESCREEN
