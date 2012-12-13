#ifndef INGAMESTARTMENU
#define INGAMESTARTMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct InGameStartMenu : public CkBaseMenu
	{
	
		struct MakeListenerHelper : public LambdaFunc_1<std::shared_ptr<Listener> , std::shared_ptr<GUI_Panel> >
		{
		
			std::shared_ptr<GUI_Panel> Apply( const std::shared_ptr<Listener> &listener );
		};

	
		struct PreventMenuHelper : public Lambda
		{
		
			std::shared_ptr<Listener> listener;
			std::shared_ptr<LambdaFunc_1<std::shared_ptr<Listener> , std::shared_ptr<GUI_Panel> > > Make;

		
			PreventMenuHelper( const std::shared_ptr<Listener> &listener, const std::shared_ptr<LambdaFunc_1<std::shared_ptr<Listener> , std::shared_ptr<GUI_Panel> > > &Make );

			void Apply();
		};

	
		struct GoRemoveProxy : public Lambda
		{
		
			std::shared_ptr<InGameStartMenu> igsm;

		
			GoRemoveProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoControlsHelper : public Lambda
		{
		
			std::shared_ptr<InGameStartMenu> igsm;

		
			GoControlsHelper( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoControlsProxy : public Lambda
		{
		
			std::shared_ptr<InGameStartMenu> igsm;

		
			GoControlsProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoOptionsProxy : public Lambda
		{
		
			std::shared_ptr<InGameStartMenu> igsm;

		
			GoOptionsProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoSaveLoadProxy : public Lambda
		{
		
			std::shared_ptr<InGameStartMenu> igsm;

		
			GoSaveLoadProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoStatsProxy : public Lambda
		{
		
			std::shared_ptr<InGameStartMenu> igsm;

		
			GoStatsProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct VerifyExitProxy : public Lambda
		{
		
			std::shared_ptr<InGameStartMenu> igsm;

		
			VerifyExitProxy( const std::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		static bool PreventMenu;

		InGameStartMenu( int Control );
		std::shared_ptr<InGameStartMenu> InGameStartMenu_Construct( int Control );

		static std::shared_ptr<GameObject> MakeListener();

		static std::shared_ptr<GameObject> MakeListener_Base( const std::shared_ptr<LambdaFunc_1<std::shared_ptr<Listener> , std::shared_ptr<GUI_Panel> > > &Make );

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	
		virtual void OnReturnTo();

	
		std::shared_ptr<MenuItem> RemoveMe;
	
		virtual void Init();

	
		void GoRemove();

		void GoControls();

		void GoOptions();

		void GoSaveLoad();

		void GoStats();

		void SetPos();

	
		virtual void MakeExitItem();

	
		void VerifyExit();

	
		virtual void MyDraw();
	};
}


#endif	//#ifndef INGAMESTARTMENU
