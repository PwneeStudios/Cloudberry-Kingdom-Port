#ifndef GUI_SCORE
#define GUI_SCORE

#include <global_header.h>

namespace CloudberryKingdom
{
	
	struct GUI_Score : public GUI_Panel
	{

		virtual ~GUI_Score() { }

		/// <summary>
		/// Return a string representation of the score
		/// </summary>
		virtual std::wstring ToString();
	
		bool AddedOnce;
	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

		virtual int GetScore();

	
		int Score;
		void SetScore( int Score );

		boost::shared_ptr<EzText> ScoreText;
		void UpdateScoreText();

		bool DoSlideIn;
	
		GUI_Score();
		boost::shared_ptr<GUI_Score> GUI_Score_Construct();
		GUI_Score( bool SlideIn );
		boost::shared_ptr<GUI_Score> GUI_Score_Construct( bool SlideIn );

	
		void DoInit( bool SlideIn );

	
		virtual void MyDraw();

		bool UpdateAfterLevelFinish;
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

	struct GUI_CampaignScore : public GUI_Score
	{
	
		virtual ~GUI_CampaignScore() { }

		struct RunningCampaignScoreLambda : public PlayerIntLambda
		{
		
			virtual int Apply( const boost::shared_ptr<PlayerData> &p );
		};
	
		GUI_CampaignScore();
		boost::shared_ptr<GUI_CampaignScore> GUI_CampaignScore_Construct();
	
		virtual int GetScore();

	};
}


#endif	//#ifndef GUI_SCORE
