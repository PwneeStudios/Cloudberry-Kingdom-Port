#ifndef GAMEOVERPANEL
#define GAMEOVERPANEL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GameOverPanel : public CkBaseMenu
	{
		
		using GUI_Panel::Call;
	
		std::shared_ptr<GameOverPanel> GameOverPanel_Construct();
		std::shared_ptr<GameOverPanel> GameOverPanel_Construct( int GameId_Score, int GameId_Level );

		struct MenuActiveHelper : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			MenuActiveHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct TextBoxActiveHelper : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			TextBoxActiveHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct OnAddHelper : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			OnAddHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct MakeTextBoxHelper : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			MakeTextBoxHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct OnEnterLambda : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			OnEnterLambda( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_DoneHelper : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			Action_DoneHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_DoneProxy : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			Action_DoneProxy( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_PlayAgainHelper : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			Action_PlayAgainHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_PlayAgainProxy : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			Action_PlayAgainProxy( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		struct Action_ShowHighScoresProxy : public Lambda
		{
		
			std::shared_ptr<GameOverPanel> gop;

		
			Action_ShowHighScoresProxy( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	
		int GameId_Score, GameId_Level;

		/// <summary>
		/// A High Scores list for the game just played.
		/// </summary>
		std::shared_ptr<ScoreList> MyHighScoreList, MyHighLevelList;

		std::shared_ptr<GUI_TextBox> MyTextBox;
		Vector2 MenuPos;

		std::shared_ptr<ScoreEntry> HighScoreEntry, HighLevelEntry;
	
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

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	
		void MakeMenu();

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		void Action_Done();

		void Action_PlayAgain();

		void Action_ShowHighScores();

	
		GameOverPanel();
		GameOverPanel( int GameId_Score, int GameId_Level );

	
		virtual void MyDraw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GAMEOVERPANEL
