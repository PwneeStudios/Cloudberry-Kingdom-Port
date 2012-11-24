#ifndef GUI_LIVESLEFT
#define GUI_LIVESLEFT

#include <global_header.h>

namespace CloudberryKingdom
{
	/// <summary>
	/// A GUI element that tracks how many lives are left.
	/// Element also shows how many lives are left, displayed after all players die and the level resets.
	/// </summary>
	class GUI_LivesLeft : public GUI_Panel
	{
	private:
		class BringStartDelayHelper : public Lambda
		{
		private:
			std::shared_ptr<GUI_LivesLeft> guiLl;

		public:
			BringStartDelayHelper( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	private:
		class BringShowLengthHelper : public Lambda
		{
		private:
			std::shared_ptr<GUI_LivesLeft> guiLl;

		public:
			BringShowLengthHelper( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	private:
		class BringInitialDelayHelper : public Lambda
		{
		private:
			std::shared_ptr<GUI_LivesLeft> guiLl;

		public:
			BringInitialDelayHelper( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	private:
		class OnResetProxy : public Lambda
		{
		private:
			std::shared_ptr<GUI_LivesLeft> guiLl;

		public:
			OnResetProxy( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	private:
		class OnDoneDyingProxy : public Lambda
		{
		private:
			std::shared_ptr<GUI_LivesLeft> guiLl;

		public:
			OnDoneDyingProxy( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	private:
		class OnDeathProxy : public Lambda
		{
		private:
			std::shared_ptr<GUI_LivesLeft> guiLl;

		public:
			OnDeathProxy( const std::shared_ptr<GUI_LivesLeft> &guiLl );

			void Apply();
		};

	public:
		std::shared_ptr<Multicaster_1<GUI_LivesLeft*> > OnOutOfLives;

	private:
		int _NumLives;
	public:
		const int &getNumLives() const;
		void setNumLives( const int &value );

		/// <summary>
		/// Returns a string representation of the number of lives left
		/// </summary>
		virtual std::wstring ToString();

	private:
		std::shared_ptr<EzText> LivesLeftText;
		void UpdateLivesLeftText();

	public:
		GUI_LivesLeft( int Lives );

	private:
		void SetPos();

		bool UseBlackBack;
		float FadeInVel, FadeOutVel;
		int InitialDelay, ShowLength, StartDelay;
		void SetParams();

		bool PauseOnShow;
	public:
		void Bring();


		virtual void Reset( bool BoxesOnly );

		virtual void OnAdd();

	private:
		int LastLife;
		void OnReset();

		void PreventResetOnLastLife( const std::shared_ptr<Level> &level );

		void OnDoneDying();

		void OnDeath();

	protected:
		virtual void MyPhsxStep();

		virtual void MyDraw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_LIVESLEFT
