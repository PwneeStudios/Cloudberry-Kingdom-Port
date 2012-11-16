#ifndef GAMEOVERPANEL
#define GAMEOVERPANEL

#include <global_header.h>

namespace CloudberryKingdom
{
	class ScoreList;
}

namespace CloudberryKingdom
{
	class GUI_TextBox;
}

namespace CloudberryKingdom
{
	class ScoreEntry;
}

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
	class GameOverPanel : public CkBaseMenu
	{
	private:
		class MenuActiveHelper : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			MenuActiveHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		class TextBoxActiveHelper : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			TextBoxActiveHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		class OnAddHelper : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			OnAddHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		class MakeTextBoxHelper : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			MakeTextBoxHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		class OnEnterLambda : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			OnEnterLambda( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		class Action_DoneHelper : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			Action_DoneHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		class Action_DoneProxy : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			Action_DoneProxy( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		class Action_PlayAgainHelper : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			Action_PlayAgainHelper( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		class Action_PlayAgainProxy : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			Action_PlayAgainProxy( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		class Action_ShowHighScoresProxy : public Lambda
		{
		private:
			std::shared_ptr<GameOverPanel> gop;

		public:
			Action_ShowHighScoresProxy( const std::shared_ptr<GameOverPanel> &gop );

			void Apply();
		};

	private:
		int GameId_Score, GameId_Level;

		/// <summary>
		/// A High Scores list for the game just played.
		/// </summary>
		std::shared_ptr<ScoreList> MyHighScoreList, MyHighLevelList;

		std::shared_ptr<GUI_TextBox> MyTextBox;
		Vector2 MenuPos;

		std::shared_ptr<ScoreEntry> HighScoreEntry, HighLevelEntry;
	public:
		int Score, Levels, Attempts, Time, Date;

		int DelayPhsx;

		virtual void Init();

		virtual void OnAdd();

	private:
		void Create();

		void SetPos();

#if defined(PC_VERSION)
	protected:
		virtual void ReleaseBody();

	private:
		void MakeTextBox();

#else
	protected:
		virtual void ReleaseBody();
#endif

	private:
		void AddScore();

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	private:
		void MakeMenu();

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	private:
		void Action_Done();

		void Action_PlayAgain();

		void Action_ShowHighScores();

	public:
		GameOverPanel();
		GameOverPanel( int GameId_Score, int GameId_Level );

	protected:
		virtual void MyDraw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GAMEOVERPANEL
