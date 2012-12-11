#ifndef GUI_LIVESLEFT
#define GUI_LIVESLEFT

#include <global_header.h>

namespace CloudberryKingdom
{
	/// <summary>
	/// A GUI element that tracks how many lives are left.
	/// Element also shows how many lives are left, displayed after all players die and the level resets.
	/// </summary>
	struct GUI_LivesLeft : public GUI_Panel
	{
	
		struct BringStartDelayHelper : public Lambda
		{
		
			std::shared_ptr<GUI_LivesLeft> guiLl;

		
			BringStartDelayHelper( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	
		struct BringShowLengthHelper : public Lambda
		{
		
			std::shared_ptr<GUI_LivesLeft> guiLl;

		
			BringShowLengthHelper( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	
		struct BringInitialDelayHelper : public Lambda
		{
		
			std::shared_ptr<GUI_LivesLeft> guiLl;

		
			BringInitialDelayHelper( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	
		struct OnResetProxy : public Lambda
		{
		
			std::shared_ptr<GUI_LivesLeft> guiLl;

		
			OnResetProxy( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	
		struct OnDoneDyingProxy : public Lambda
		{
		
			std::shared_ptr<GUI_LivesLeft> guiLl;

		
			OnDoneDyingProxy( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	
		struct OnDeathProxy : public Lambda
		{
		
			std::shared_ptr<GUI_LivesLeft> guiLl;

		
			OnDeathProxy( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	
		std::shared_ptr<Multicaster_1<std::shared_ptr<GUI_LivesLeft> > > OnOutOfLives;

	
		int _NumLives;
	
		const int &getNumLives() const;
		void setNumLives( const int &value );

		/// <summary>
		/// Returns a string representation of the number of lives left
		/// </summary>
		virtual std::wstring ToString();

	
		std::shared_ptr<EzText> LivesLeftText;
		void UpdateLivesLeftText();

	
		GUI_LivesLeft( int Lives );

	
		void SetPos();

		bool UseBlackBack;
		float FadeInVel, FadeOutVel;
		int InitialDelay, ShowLength, StartDelay;
		void SetParams();

		bool PauseOnShow;
	
		void Bring();


		virtual void Reset( bool BoxesOnly );

		virtual void OnAdd();

	
		int LastLife;
		void OnReset();

		void PreventResetOnLastLife( const std::shared_ptr<Level> &level );

		void OnDoneDying();

		void OnDeath();

	
		virtual void MyPhsxStep();

		virtual void MyDraw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_LIVESLEFT
