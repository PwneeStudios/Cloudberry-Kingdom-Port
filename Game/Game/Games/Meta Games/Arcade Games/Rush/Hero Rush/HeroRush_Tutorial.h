#ifndef HERORUSH_TUTORIAL
#define HERORUSH_TUTORIAL

#include <global_header.h>

namespace CloudberryKingdom
{
	class GUI_Text;
}

namespace CloudberryKingdom
{
	class Arrow;
}

namespace CloudberryKingdom
{
	class Challenge_HeroRush;
}








namespace CloudberryKingdom
{
	class HeroRush_Tutorial : public GameObject
	{
	private:
		class StartMusicHelper : public Lambda
		{
		public:
			void Apply();
		};

	private:
		class TutorialOrSkipProxy : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> tutorial;

		public:
			TutorialOrSkipProxy( const std::shared_ptr<HeroRush_Tutorial> &tutorial );

			void Apply();
		};

	private:
		class ListenerHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> tutorial;
			std::shared_ptr<GUI_Text> text;

		public:
			ListenerHelper( const std::shared_ptr<HeroRush_Tutorial> &tutorial, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	public:
		class AddGameObjectHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> tutorial;
			std::shared_ptr<GUI_Text> text;

		public:
			AddGameObjectHelper( const std::shared_ptr<HeroRush_Tutorial> &tutorial, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	private:
		class TitleProxy : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;

		public:
			TitleProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	private:
		class TitleNextTutorialHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<GUI_Text> text;

		public:
			TitleNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	private:
		class HeroRushTimerShowHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;

		public:
			HeroRushTimerShowHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	private:
		class PointAtDoorNextTutorialHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<Arrow> arrow;
			std::shared_ptr<GUI_Text> text;

		public:
			PointAtDoorNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<Arrow> &arrow, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	private:
		class PointAtTimerProxy : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;

		public:
			PointAtTimerProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	private:
		class PointAtTimerNextTutorialHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<Arrow> arrow;
			std::shared_ptr<GUI_Text> text;
			std::shared_ptr<GUI_Text> text2;

		public:
			PointAtTimerNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<Arrow> &arrow, const std::shared_ptr<GUI_Text> &text, const std::shared_ptr<GUI_Text> &text2 );

			void Apply();
		};

	private:
		class PointAtCoinsNextTutorialHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<GUI_Text> text;
			std::vector<Arrow*> arrows;

		public:
			PointAtCoinsNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<GUI_Text> &text, std::vector<Arrow*> &arrows );

			void Apply();
		};

	private:
		class PointAtScoreNextTutorialHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;
			std::shared_ptr<Arrow> arrow;
			std::shared_ptr<GUI_Text> text;

		public:
			PointAtScoreNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<Arrow> &arrow, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	private:
		class ReadyProxy : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;

		public:
			ReadyProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	private:
		class ReadyTutorialHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;

		public:
			ReadyTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	private:
		class PauseHeroRushTimerHelper : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;

		public:
			PauseHeroRushTimerHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

	private:
		class EndProxy : public Lambda
		{
		private:
			std::shared_ptr<HeroRush_Tutorial> hrt;

		public:
			EndProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt );

			void Apply();
		};

		/// <summary>
		/// Whether the Hero Rush introduction has been watched before.
		/// </summary>
	public:
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
	protected:
		bool SoundOnKill;

	private:
		std::shared_ptr<Challenge_HeroRush> HeroRush;
	public:
		HeroRush_Tutorial( const std::shared_ptr<Challenge_HeroRush> &HeroRush );

		virtual void OnAdd();

	protected:
		void TutorialOrSkip();

	private:
		void StartTutorial();

	protected:
		virtual void Title();

	private:
		void PointAtDoor();

		void PointAtTimer();

		void PointAtCoins();

		void PointAtScore();

		void Ready();

		void End();

	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HERORUSH_TUTORIAL
