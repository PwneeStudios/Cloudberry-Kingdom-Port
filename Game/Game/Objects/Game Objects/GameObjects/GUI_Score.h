#ifndef GUI_SCORE
#define GUI_SCORE

#include "../Game/Player/PlayerManager.h"
#include "GUI_Panel.h"
#include <string>
#include <tchar.h>
#include "stringconverter.h"

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class GUI_CampaignScore : public GUI_Score
	{
	private:
		class RunningCampaignScoreLambda : public PlayerIntLambda
		{
		public:
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};
	public:
		GUI_CampaignScore();

	protected:
		virtual int GetScore();

	};

	class GUI_Score : public GUI_Panel
	{
		/// <summary>
		/// Return a string representation of the score
		/// </summary>
	public:
		virtual std::wstring ToString();

	private:
		bool AddedOnce;
	public:
		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

		virtual int GetScore();

	private:
		int Score;
		void SetScore( int Score );

		std::shared_ptr<EzText> ScoreText;
		void UpdateScoreText();

		bool DoSlideIn;
	public:
		GUI_Score();
		GUI_Score( bool SlideIn );

	private:
		void DoInit( bool SlideIn );

	protected:
		virtual void MyDraw();

		bool UpdateAfterLevelFinish;
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_SCORE
