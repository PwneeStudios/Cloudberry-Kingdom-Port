#ifndef GAMEOVERPANEL
#define GAMEOVERPANEL

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Player/LeaderboardView.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreDatabase.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreEntry.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreList.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_TextBox.h"
//#include "Game/Objects/Game Objects/GameObjects/End/HighScorePanel.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Stats.h"
//#include "Game/Player/Awardments/Awardment.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct GameOverPanel : public CkBaseMenu
	{

		virtual ~GameOverPanel()
		{
#ifdef BOOST_BIN
			OnDestructor( "GameOverPanel" );
#endif
		}

		
		using GUI_Panel::Call;
	
		struct MenuActiveHelper : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			MenuActiveHelper( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};
	
		struct TextBoxActiveHelper : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			TextBoxActiveHelper( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct OnAddHelper : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			OnAddHelper( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct MakeTextBoxHelper : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			MakeTextBoxHelper( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct OnEnterLambda : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			OnEnterLambda( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_DoneHelper : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			Action_DoneHelper( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_DoneProxy : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			Action_DoneProxy( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_PlayAgainHelper : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			Action_PlayAgainHelper( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_PlayAgainProxy : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			Action_PlayAgainProxy( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_ShowHighScoresProxy : public Lambda
		{
		
			boost::shared_ptr<GameOverPanel> gop;

		
			Action_ShowHighScoresProxy( const boost::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		int GameId_Score, GameId_Level;

		/// <summary>
		/// A High Scores list for the game just played.
		/// </summary>
		boost::shared_ptr<ScoreList> MyHighScoreList, MyHighLevelList;

		boost::shared_ptr<GUI_TextBox> MyTextBox;
		Vector2 MenuPos;

		boost::shared_ptr<ScoreEntry> HighScoreEntry, HighLevelEntry;
	
		int Score, Levels, Attempts, Time, Date;

		int DelayPhsx;

		virtual void Init();

		virtual void OnAdd();

	
		void Create();

		void SetPos();

#if defined(PC_VERSION)
		virtual void ReleaseBody();

	
		void MakeTextBox();
#else
		virtual void ReleaseBody();
#endif

		void AddScore();

		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

		void MakeMenu();

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );
	
		void Action_Done();

		void Action_PlayAgain();

		void Action_ShowHighScores();
	
		GameOverPanel();
		GameOverPanel( int GameId_Score, int GameId_Level );

		boost::shared_ptr<GameOverPanel> GameOverPanel_Construct();
		boost::shared_ptr<GameOverPanel> GameOverPanel_Construct( int GameId_Score, int GameId_Level );

		virtual void MyDraw();
	
		void InitializeInstanceFields();

	};

}


#endif	//#ifndef GAMEOVERPANEL
