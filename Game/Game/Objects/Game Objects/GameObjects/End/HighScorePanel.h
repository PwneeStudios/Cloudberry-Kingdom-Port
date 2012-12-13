#ifndef HIGHSCOREPANEL
#define HIGHSCOREPANEL

#include <global_header.h>

namespace CloudberryKingdom
{

	struct HighScorePanel : public CkBaseMenu
	{
	
		using GUI_Panel::SlideIn;

	
		struct HighScoreReturnToCallerLambda : public Lambda
		{
		
			std::shared_ptr<HighScorePanel> hsp;
		
			HighScoreReturnToCallerLambda( const std::shared_ptr<HighScorePanel> &hsp );

			void Apply();
		};

	
		struct HighScorePanelEndGameHelper : public Lambda
		{
		
			std::shared_ptr<HighScorePanel> hsp;
			bool param;

		
			HighScorePanelEndGameHelper( const std::shared_ptr<HighScorePanel> &hsp, bool param );

			void Apply();
		};

	
		struct Action_DoneProxy1 : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<HighScorePanel> hsp;

		
			Action_DoneProxy1( const std::shared_ptr<HighScorePanel> &hsp );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	
		struct Action_PlayAgainProxy1 : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<HighScorePanel> hsp;

		
			Action_PlayAgainProxy1( const std::shared_ptr<HighScorePanel> &hsp );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	
		std::shared_ptr<ScoreList> MyScoreList;

	
		virtual void ReleaseBody();

	
		HighScorePanel( const std::shared_ptr<ScoreList> &Scores );
		std::shared_ptr<HighScorePanel> HighScorePanel_Construct( const std::shared_ptr<ScoreList> &Scores );

	
		bool Instant;
	
		void Constructor( const std::shared_ptr<ScoreList> &Scores );


	
		static std::vector<std::wstring> TextureName;
		std::vector<std::shared_ptr<HighScorePanel> > Panels;

	
		HighScorePanel( std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist );
		std::shared_ptr<HighScorePanel> HighScorePanel_Construct( std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist );
		HighScorePanel( bool Instant, std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist );
		std::shared_ptr<HighScorePanel> HighScorePanel_Construct( bool Instant, std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist );
		void MultiInit( bool Instant, std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist );

	
		void SwapPanels();

	
		virtual void Init();

		virtual void OnAdd();

		static Vector4 ScoreColor;
		static Vector4 CurrentScoreColor;
		std::shared_ptr<QuadClass> Backdrop;
	
		void Create();

		void SetPos();

		std::shared_ptr<EzText> SwapText;
		void MakeSwapText();

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	
		void MakeMenu();

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		void Action_Done();

		void Action_PlayAgain();

	
		virtual void MyPhsxStep();

	
		virtual bool HitTest( Vector2 pos );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HIGHSCOREPANEL
