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
		
			std::shared_ptr<HeroRush_Tutorial> tutorial;

		
			TutorialOrSkipProxy( const std::shared_ptr<HeroRush_Tutorial> &tutorial );

			void Apply();
		};

	
		struct ListenerHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> tutorial;
			std::shared_ptr<GUI_Text> text;

		
			ListenerHelper( const std::shared_ptr<HeroRush_Tutorial> &tutorial, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct AddGameObjectHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> tutorial;
			std::shared_ptr<GUI_Text> text;

		
			AddGameObjectHelper( const std::shared_ptr<HeroRush_Tutorial> &tutorial, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct TitleProxy : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;

		
			TitleProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct TitleNextTutorialHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<GUI_Text> text;

		
			TitleNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct HeroRushTimerShowHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;

		
			HeroRushTimerShowHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct PointAtDoorNextTutorialHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<Arrow> arrow;
			std::shared_ptr<GUI_Text> text;

		
			PointAtDoorNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<Arrow> &arrow, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct PointAtTimerProxy : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;

		
			PointAtTimerProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct PointAtTimerNextTutorialHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<Arrow> arrow;
			std::shared_ptr<GUI_Text> text;
			std::shared_ptr<GUI_Text> text2;

		
			PointAtTimerNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<Arrow> &arrow, const std::shared_ptr<GUI_Text> &text, const std::shared_ptr<GUI_Text> &text2 );

			void Apply();
		};

	
		struct PointAtCoinsNextTutorialHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<GUI_Text> text;
			std::vector<std::shared_ptr<Arrow> > arrows;

		
			PointAtCoinsNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<GUI_Text> &text, std::vector<std::shared_ptr<Arrow> > &arrows );

			void Apply();
		};

	
		struct PointAtScoreNextTutorialHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<Arrow> arrow;
			std::shared_ptr<GUI_Text> text;

		
			PointAtScoreNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<Arrow> &arrow, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct ReadyProxy : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;

		
			ReadyProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct ReadyTutorialHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;

		
			ReadyTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct PauseHeroRushTimerHelper : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;

		
			PauseHeroRushTimerHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	
		struct EndProxy : public Lambda
		{
		
			std::shared_ptr<HeroRush_Tutorial> hrt;

		
			EndProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt );

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

	
		std::shared_ptr<Challenge_HeroRush> HeroRush;
	
		HeroRush_Tutorial( const std::shared_ptr<Challenge_HeroRush> &HeroRush );

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
