#ifndef INGAMESTARTMENU
#define INGAMESTARTMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct InGameStartMenu : public CkBaseMenu
	{
	
		struct MakeListenerHelper : public LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> >
		{
		
			boost::shared_ptr<GUI_Panel> Apply( const boost::shared_ptr<Listener> &listener );
		};

	
		struct PreventMenuHelper : public Lambda
		{
		
			boost::shared_ptr<Listener> listener;
			boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > Make;

		
			PreventMenuHelper( const boost::shared_ptr<Listener> &listener, const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > &Make );

			void Apply();
		};

	
		struct GoRemoveProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoRemoveProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoControlsHelper : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoControlsHelper( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoControlsProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoControlsProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoOptionsProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoOptionsProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoSaveLoadProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoSaveLoadProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct GoStatsProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			GoStatsProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		struct VerifyExitProxy : public Lambda
		{
		
			boost::shared_ptr<InGameStartMenu> igsm;

		
			VerifyExitProxy( const boost::shared_ptr<InGameStartMenu> &igsm );

			void Apply();
		};

	
		static bool PreventMenu;

		InGameStartMenu( int Control );
		boost::shared_ptr<InGameStartMenu> InGameStartMenu_Construct( int Control );

		static boost::shared_ptr<GameObject> MakeListener();

		static boost::shared_ptr<GameObject> MakeListener_Base( const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > &Make );

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

	
		virtual void OnReturnTo();

	
		boost::shared_ptr<MenuItem> RemoveMe;
	
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
