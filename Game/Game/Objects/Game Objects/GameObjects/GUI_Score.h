#ifndef GUI_SCORE
#define GUI_SCORE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct PlayerData;
}

namespace CloudberryKingdom
{
	struct EzText;
}




namespace CloudberryKingdom
{
	struct GUI_Score : public GUI_Panel
	{
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

		std::shared_ptr<EzText> ScoreText;
		void UpdateScoreText();

		bool DoSlideIn;
	
		GUI_Score();
		GUI_Score( bool SlideIn );

	
		void DoInit( bool SlideIn );

	
		virtual void MyDraw();

		bool UpdateAfterLevelFinish;
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

	struct GUI_CampaignScore : public GUI_Score
	{
	
		struct RunningCampaignScoreLambda : public PlayerIntLambda
		{
		
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	
		GUI_CampaignScore();

	
		virtual int GetScore();

	};
}


#endif	//#ifndef GUI_SCORE
