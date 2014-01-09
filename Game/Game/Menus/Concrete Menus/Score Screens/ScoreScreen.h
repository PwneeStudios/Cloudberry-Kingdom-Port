#ifndef SCORESCREEN
#define SCORESCREEN

#include <small_header.h>

//#include "Core/FancyVector2.h"
//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Sound/EzSound.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Core/Tools/CoreMath.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Games/GameType.h"
//#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Tools/EzStorage.h"
#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/SaveLoadSeedMenu.h"
//#include "Game/Menus/Concrete Menus/Score Screens/StatsScreen.h"
//#include "Game/Objects/Door/Door.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Player/Stats.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct ScoreScreen : public CkBaseMenu
	{

		virtual ~ScoreScreen()
		{
#ifdef BOOST_BIN
			OnDestructor( "ScoreScreen" );
#endif
		}


		struct EOL_WaitThenDoEndActionWaitProxy : public Lambda
		{
		
			boost::shared_ptr<StringWorldGameData> sw;
			boost::shared_ptr<Door> door;

			EOL_WaitThenDoEndActionWaitProxy( const boost::shared_ptr<StringWorldGameData> &sw, const boost::shared_ptr<Door> &door );

			void Apply();
		};


		struct EOL_WaitThenDoEndActionProxy : public Lambda_1<boost::shared_ptr<Door> >
		{
			boost::shared_ptr<ScoreScreen> ss;

			EOL_WaitThenDoEndActionProxy( boost::shared_ptr<ScoreScreen> ss );
			void Apply( const boost::shared_ptr<Door> &door );
		};


		struct OnAddHelper : public Lambda
		{
		
			boost::shared_ptr<ScoreScreen> ss;

		
			OnAddHelper( const boost::shared_ptr<ScoreScreen> &ss );

			void Apply();
		};

	
		struct VariableCoinsLambda : public PlayerIntLambda
		{
		
			virtual ~VariableCoinsLambda()
			{
#ifdef BOOST_BIN
				OnDestructor( "VariableCoinsLambda" );
#endif
			}


			StatGroup MyStats;
		
			VariableCoinsLambda( StatGroup MyStats );

			virtual int Apply( const boost::shared_ptr<PlayerData> &p );
		};
	
		struct VariableTotalCoinsLambda : public PlayerIntLambda
		{
		
			virtual ~VariableTotalCoinsLambda()
			{
#ifdef BOOST_BIN
				OnDestructor( "VariableTotalCoinsLambda" );
#endif
			}


			StatGroup MyStats;
		
			VariableTotalCoinsLambda( StatGroup MyStats );

			virtual int Apply( const boost::shared_ptr<PlayerData> &p );
		};
	
		struct VariableBlobsLambda : public PlayerIntLambda
		{
		
			virtual ~VariableBlobsLambda()
			{
#ifdef BOOST_BIN
				OnDestructor( "VariableBlobsLambda" );
#endif
			}


			StatGroup MyStats;
		
			VariableBlobsLambda( StatGroup MyStats );

			virtual int Apply( const boost::shared_ptr<PlayerData> &p );
		};
	
		struct VariableTotalBlobsLambda : public PlayerIntLambda
		{
		
			virtual ~VariableTotalBlobsLambda()
			{
#ifdef BOOST_BIN
				OnDestructor( "VariableTotalBlobsLambda" );
#endif
			}


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

		struct MenuGo_ExitCampaignProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ScoreScreen> ss;

		
			MenuGo_ExitCampaignProxy( const boost::shared_ptr<ScoreScreen> &ss );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

		struct MenuGo_ExitFreeplayProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ScoreScreen> ss;

		
			MenuGo_ExitFreeplayProxy( const boost::shared_ptr<ScoreScreen> &ss );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};
	
		bool _Add_Watch, _Add_Save;
	
		virtual void MakeMenu();

	
		boost::shared_ptr<EzSound> ScoreSound, BonusSound;

	
		int DelayPhsx;
		bool InCampaign;

		ScoreScreen( bool CallBaseConstructor );
		boost::shared_ptr<ScoreScreen> ScoreScreen_Construct( bool CallBaseConstructor );

		ScoreScreen( StatGroup group, const boost::shared_ptr<GameData> &game, const bool InCampaign );
		boost::shared_ptr<ScoreScreen> ScoreScreen_Construct( StatGroup group, const boost::shared_ptr<GameData> &game, const bool InCampaign );
	
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

		void EOL_WaitThenDoEndAction( boost::shared_ptr<Door> door );

		/// <summary>
		/// Called when 'Exit Freeplay' is selected from the menu.
		/// The Score Screen slides out and the current game's EndGame function is called.
		/// </summary>
		virtual void MenuGo_ExitFreeplay( const boost::shared_ptr<MenuItem> &item );

		void MenuGo_ExitCampaign( boost::shared_ptr<MenuItem> item );

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
