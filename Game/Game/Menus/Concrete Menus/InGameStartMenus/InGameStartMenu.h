#ifndef INGAMESTARTMENU
#define INGAMESTARTMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class InGameStartMenu : public CkBaseMenu
	{
	private:
		class MakeListenerHelper : public LambdaFunc_1<std::shared_ptr<Listener> , std::shared_ptr<GUI_Panel> >
		{
		public:
			std::shared_ptr<GUI_Panel> Apply( const std::shared_ptr<Listener> &listener );
		};

	private:
		class PreventMenuHelper : public Lambda
		{
		private:
			std::shared_ptr<Listener> listener;
			std::shared_ptr<LambdaFunc_1<std::shared_ptr<Listener> , std::shared_ptr<GUI_Panel> > > Make;

		public:
			PreventMenuHelper( const std::shared_ptr<Listener> &listener, const std::shared_ptr<LambdaFunc_1<std::shared_ptr<Listener> , std::shared_ptr<GUI_Panel> > > &Make );

			void Apply();
		};

	private:
		class GoRemoveProxy : public Lambda
		{
		private:
			std::shared_ptr<InGameStartMenu> igsm;

		public:
			GoRemoveProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	private:
		class GoControlsHelper : public Lambda
		{
		private:
			std::shared_ptr<InGameStartMenu> igsm;

		public:
			GoControlsHelper( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	private:
		class GoControlsProxy : public Lambda
		{
		private:
			std::shared_ptr<InGameStartMenu> igsm;

		public:
			GoControlsProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	private:
		class GoOptionsProxy : public Lambda
		{
		private:
			std::shared_ptr<InGameStartMenu> igsm;

		public:
			GoOptionsProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	private:
		class GoSaveLoadProxy : public Lambda
		{
		private:
			std::shared_ptr<InGameStartMenu> igsm;

		public:
			GoSaveLoadProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	private:
		class GoStatsProxy : public Lambda
		{
		private:
			std::shared_ptr<InGameStartMenu> igsm;

		public:
			GoStatsProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	private:
		class VerifyExitProxy : public Lambda
		{
		private:
			std::shared_ptr<InGameStartMenu> igsm;

		public:
			VerifyExitProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	public:
		static bool PreventMenu;

		InGameStartMenu( int Control );

		static std::shared_ptr<GameObject> MakeListener();

		static std::shared_ptr<GameObject> MakeListener_Base( const std::shared_ptr<LambdaFunc_1<std::shared_ptr<Listener> , std::shared_ptr<GUI_Panel> > > &Make );

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	public:
		virtual void OnReturnTo();

	private:
		std::shared_ptr<MenuItem> RemoveMe;
	public:
		virtual void Init();

	private:
		void GoRemove();

		void GoControls();

		void GoOptions();

		void GoSaveLoad();

		void GoStats();

		void SetPos();

	protected:
		virtual void MakeExitItem();

	private:
		void VerifyExit();

	protected:
		virtual void MyDraw();
	};
}


#endif	//#ifndef INGAMESTARTMENU
