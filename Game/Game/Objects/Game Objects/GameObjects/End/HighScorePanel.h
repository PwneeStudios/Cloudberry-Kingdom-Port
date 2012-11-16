#ifndef HIGHSCOREPANEL
#define HIGHSCOREPANEL

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class ScoreList;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class HighScorePanel : public CkBaseMenu
	{
	private:
		class HighScoreReturnToCallerLambda : public Lambda
		{
		private:
			std::shared_ptr<HighScorePanel> hsp;
		public:
			HighScoreReturnToCallerLambda( const std::shared_ptr<HighScorePanel> &hsp );

			void Apply();
		};

	private:
		class HighScorePanelEndGameHelper : public Lambda
		{
		private:
			std::shared_ptr<HighScorePanel> hsp;
			bool param;

		public:
			HighScorePanelEndGameHelper( const std::shared_ptr<HighScorePanel> &hsp, bool param );

			void Apply();
		};

	private:
		class Action_DoneProxy1 : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<HighScorePanel> hsp;

		public:
			Action_DoneProxy1( const std::shared_ptr<HighScorePanel> &hsp );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	private:
		class Action_PlayAgainProxy1 : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<HighScorePanel> hsp;

		public:
			Action_PlayAgainProxy1( const std::shared_ptr<HighScorePanel> &hsp );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	public:
		std::shared_ptr<ScoreList> MyScoreList;

	protected:
		virtual void ReleaseBody();

	public:
		HighScorePanel( const std::shared_ptr<ScoreList> &Scores );

	private:
		bool Instant;
	public:
		void Constructor( const std::shared_ptr<ScoreList> &Scores );


	private:
		static std::vector<std::wstring> TextureName;
		std::vector<HighScorePanel*> Panels;

	public:
//ORIGINAL LINE: public HighScorePanel(params ScoreList[] Scores)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		HighScorePanel( ... );
//ORIGINAL LINE: public HighScorePanel(bool Instant, params ScoreList[] Scores)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		HighScorePanel( bool Instant, ... );
//ORIGINAL LINE: public void MultiInit(bool Instant, params ScoreList[] Scores)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		void MultiInit( bool Instant, ... );

	private:
		void SwapPanels();

	public:
		virtual void Init();

		virtual void OnAdd();

		static Vector4 ScoreColor;
		static Vector4 CurrentScoreColor;
		std::shared_ptr<QuadClass> Backdrop;
	private:
		void Create();

		void SetPos();

		std::shared_ptr<EzText> SwapText;
		void MakeSwapText();

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	private:
		void MakeMenu();

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	private:
		void Action_Done();

		void Action_PlayAgain();

	protected:
		virtual void MyPhsxStep();

	public:
		virtual bool HitTest( Vector2 pos );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HIGHSCOREPANEL
