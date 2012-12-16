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
		
			boost::shared_ptr<Escalation_Tutorial> et;

		
			PreventThingsHelper( const boost::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct TitleProxy : public Lambda
		{
		
			boost::shared_ptr<Escalation_Tutorial> et;

		
			TitleProxy( const boost::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct TutorialOrSkipProxy : public Lambda
		{
		
			boost::shared_ptr<Escalation_Tutorial> et;

		
			TutorialOrSkipProxy( const boost::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct NextTutorialHelper : public Lambda
		{
		
			boost::shared_ptr<Escalation_Tutorial> et;
			boost::shared_ptr<GUI_Text> text;

		
			NextTutorialHelper( const boost::shared_ptr<Escalation_Tutorial> &et, const boost::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct TextKillHelper : public Lambda
		{
		
			boost::shared_ptr<Escalation_Tutorial> et;
			boost::shared_ptr<GUI_Text> text;

		
			TextKillHelper( const boost::shared_ptr<Escalation_Tutorial> &et, const boost::shared_ptr<GUI_Text> &text );

			void Apply();
		};

	
		struct ReadyProxy : public Lambda
		{
		
			boost::shared_ptr<Escalation_Tutorial> et;

		
			ReadyProxy( const boost::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct TutorialHelperReadyGo : public Lambda
		{
		
			boost::shared_ptr<Escalation_Tutorial> et;

		
			TutorialHelperReadyGo( const boost::shared_ptr<Escalation_Tutorial> &et );

			void Apply();
		};

	
		struct EndProxy : public Lambda
		{
		
			boost::shared_ptr<Escalation_Tutorial> et;

		
			EndProxy( const boost::shared_ptr<Escalation_Tutorial> &et );

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

	
		boost::shared_ptr<Challenge_Escalation> Escalation;
	
		Escalation_Tutorial( const boost::shared_ptr<Challenge_Escalation> &Escalation );

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
