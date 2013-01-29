#ifndef HIGHSCOREPANEL
#define HIGHSCOREPANEL

#include <global_header.h>

namespace CloudberryKingdom
{

	struct HighScorePanel : public CkBaseMenu
	{

		virtual ~HighScorePanel() { }
	
		using GUI_Panel::SlideIn;

	
		struct HighScoreReturnToCallerLambda : public Lambda
		{
		
			boost::shared_ptr<HighScorePanel> hsp;
		
			HighScoreReturnToCallerLambda( const boost::shared_ptr<HighScorePanel> &hsp );

			void Apply();
		};

	
		struct HighScorePanelEndGameHelper : public Lambda
		{
		
			boost::shared_ptr<HighScorePanel> hsp;
			bool param;

		
			HighScorePanelEndGameHelper( const boost::shared_ptr<HighScorePanel> &hsp, bool param );

			void Apply();
		};

	
		struct Action_DoneProxy1 : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<HighScorePanel> hsp;

		
			Action_DoneProxy1( const boost::shared_ptr<HighScorePanel> &hsp );

			void Apply( const boost::shared_ptr<MenuItem> &dummy );
		};

	
		struct Action_PlayAgainProxy1 : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<HighScorePanel> hsp;

		
			Action_PlayAgainProxy1( const boost::shared_ptr<HighScorePanel> &hsp );

			void Apply( const boost::shared_ptr<MenuItem> &dummy );
		};

	
		boost::shared_ptr<ScoreList> MyScoreList;

	
		virtual void ReleaseBody();

	
		HighScorePanel( const boost::shared_ptr<ScoreList> &Scores );
		boost::shared_ptr<HighScorePanel> HighScorePanel_Construct( const boost::shared_ptr<ScoreList> &Scores );

	
		bool Instant;
	
		void Constructor( const boost::shared_ptr<ScoreList> &Scores );


	
		std::vector<boost::shared_ptr<HighScorePanel> > Panels;

	
		HighScorePanel( boost::shared_ptr<ScoreList> scorelist, boost::shared_ptr<ScoreList> levellist );
		boost::shared_ptr<HighScorePanel> HighScorePanel_Construct( boost::shared_ptr<ScoreList> scorelist, boost::shared_ptr<ScoreList> levellist );
		HighScorePanel( bool Instant, boost::shared_ptr<ScoreList> scorelist, boost::shared_ptr<ScoreList> levellist );
		boost::shared_ptr<HighScorePanel> HighScorePanel_Construct( bool Instant, boost::shared_ptr<ScoreList> scorelist, boost::shared_ptr<ScoreList> levellist );
		void MultiInit( bool Instant, boost::shared_ptr<ScoreList> scorelist, boost::shared_ptr<ScoreList> levellist );

	
		void SwapPanels();

	
		virtual void Init();

		virtual void OnAdd();

		static Vector4 ScoreColor;
		static Vector4 CurrentScoreColor;
		boost::shared_ptr<QuadClass> Backdrop;
	
		void Create();

		void SetPos();

		boost::shared_ptr<EzText> SwapText;
		void MakeSwapText();

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

	
		void MakeMenu();

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		void Action_Done();

		void Action_PlayAgain();

	
		virtual void MyPhsxStep();

	
		virtual bool HitTest( Vector2 pos );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef HIGHSCOREPANEL
