#ifndef HERORUSH_TUTORIAL
#define HERORUSH_TUTORIAL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct HeroRush_Tutorial : public GameObject
	{

	
		static void InitializeStatics();

	
		struct StartMusicHelper : public Lambda
		{
		
			void Apply();
		};

	
		struct TutorialOrSkipProxy : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> tutorial;

		
			TutorialOrSkipProxy( const boost::shared_ptr<HeroRush_Tutorial> &tutorial );

			void Apply();
		};

	
		struct ListenerHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> tutorial;
			boost::shared_ptr<GUI_Text> text;

		
			ListenerHelper( const boost::shared_ptr<HeroRush_Tutorial> &tutorial, const boost::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct AddGameObjectHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> tutorial;
			boost::shared_ptr<GUI_Text> text;

		
			AddGameObjectHelper( const boost::shared_ptr<HeroRush_Tutorial> &tutorial, const boost::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct TitleProxy : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;

		
			TitleProxy( const boost::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct TitleNextTutorialHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;
			boost::shared_ptr<GUI_Text> text;

		
			TitleNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct HeroRushTimerShowHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;

		
			HeroRushTimerShowHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct PointAtDoorNextTutorialHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;
			boost::shared_ptr<Arrow> arrow;
			boost::shared_ptr<GUI_Text> text;

		
			PointAtDoorNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<Arrow> &arrow, const boost::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct PointAtTimerProxy : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;

		
			PointAtTimerProxy( const boost::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct PointAtTimerNextTutorialHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;
			boost::shared_ptr<Arrow> arrow;
			boost::shared_ptr<GUI_Text> text;
			boost::shared_ptr<GUI_Text> text2;

		
			PointAtTimerNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<Arrow> &arrow, const boost::shared_ptr<GUI_Text> &text, const boost::shared_ptr<GUI_Text> &text2 );

			void Apply();
		};

	
		struct PointAtCoinsNextTutorialHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;
			boost::shared_ptr<GUI_Text> text;
			std::vector<boost::shared_ptr<Arrow> > arrows;

		
			PointAtCoinsNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<GUI_Text> &text, std::vector<boost::shared_ptr<Arrow> > &arrows );

			void Apply();
		};

	
		struct PointAtScoreNextTutorialHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;
			boost::shared_ptr<Arrow> arrow;
			boost::shared_ptr<GUI_Text> text;

		
			PointAtScoreNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<Arrow> &arrow, const boost::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct ReadyProxy : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;

		
			ReadyProxy( const boost::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct ReadyTutorialHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;

		
			ReadyTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct PauseHeroRushTimerHelper : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;

		
			PauseHeroRushTimerHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct EndProxy : public Lambda
		{
		
			boost::shared_ptr<HeroRush_Tutorial> hrt;

		
			EndProxy( const boost::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

		/// <summary>
		/// Whether the Hero Rush introduction has been watched before.
		/// </summary>
	
		static bool HasWatchedOnce;
		static void WatchedOnce();

		/// <summary>
		/// When true the tutorial will skip the long version.
		/// The bool is then set to false.
		/// </summary>
		static bool TemporarySkip;

		static bool ShowTitle;

		/// <summary>
		/// Whether text makes a popping sound when we kill it
		/// </summary>
	
		bool SoundOnKill;

	
		boost::shared_ptr<Challenge_HeroRush> HeroRush;
	
		HeroRush_Tutorial( const boost::shared_ptr<Challenge_HeroRush> &HeroRush );

		virtual void OnAdd();

	
		void TutorialOrSkip();

	
		void StartTutorial();

	
		virtual void Title();

	
		void PointAtDoor();

		void PointAtTimer();

		void PointAtCoins();

		void PointAtScore();

		void Ready();

		void End();

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HERORUSH_TUTORIAL
