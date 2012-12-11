#ifndef ESCALATION_TUTORIAL
#define ESCALATION_TUTORIAL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GUI_Text;
}

namespace CloudberryKingdom
{
	struct Challenge_Escalation;
}



namespace CloudberryKingdom
{
	struct Escalation_Tutorial : public GameObject
	{
	
		struct ConfigureSongsHelper : public Lambda
		{
		
			void Apply();
		};

	
		struct PreventThingsHelper : public Lambda
		{
		
			std::shared_ptr<Escalation_Tutorial> et;

		
			PreventThingsHelper( const std::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct TitleProxy : public Lambda
		{
		
			std::shared_ptr<Escalation_Tutorial> et;

		
			TitleProxy( const std::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct TutorialOrSkipProxy : public Lambda
		{
		
			std::shared_ptr<Escalation_Tutorial> et;

		
			TutorialOrSkipProxy( const std::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct NextTutorialHelper : public Lambda
		{
		
			std::shared_ptr<Escalation_Tutorial> et;
			std::shared_ptr<GUI_Text> text;

		
			NextTutorialHelper( const std::shared_ptr<Escalation_Tutorial> &et, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct TextKillHelper : public Lambda
		{
		
			std::shared_ptr<Escalation_Tutorial> et;
			std::shared_ptr<GUI_Text> text;

		
			TextKillHelper( const std::shared_ptr<Escalation_Tutorial> &et, const std::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct ReadyProxy : public Lambda
		{
		
			std::shared_ptr<Escalation_Tutorial> et;

		
			ReadyProxy( const std::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct TutorialHelperReadyGo : public Lambda
		{
		
			std::shared_ptr<Escalation_Tutorial> et;

		
			TutorialHelperReadyGo( const std::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct EndProxy : public Lambda
		{
		
			std::shared_ptr<Escalation_Tutorial> et;

		
			EndProxy( const std::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

		/// <summary>
		/// Whether the Escalation introduction has been watched before.
		/// </summary>
	
		const static bool &getWatchedOnce();
		static void setWatchedOnce( const bool &value );
	
		static bool _WatchedOnce;

	
		static bool ShowTitle;

		/// <summary>
		/// Whether text makes a popping sound when we kill it
		/// </summary>
	
		bool SoundOnKill;

	
		std::shared_ptr<Challenge_Escalation> Escalation;
	
		Escalation_Tutorial( const std::shared_ptr<Challenge_Escalation> &Escalation );

		virtual void OnAdd();

	
		void TutorialOrSkip();

		virtual void Title();

	
		void Ready();

		void End();

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ESCALATION_TUTORIAL
