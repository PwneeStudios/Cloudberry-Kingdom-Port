#ifndef CHARSELECTMANAGER
#define CHARSELECTMANAGER

#include <global_header.h>

#include "Hacks/XNA/SignedInEventArgs.h"

namespace CloudberryKingdom
{

	struct CharacterSelectManager
	{
	
		static void InitializeStatics();
	
		struct SignInGamerLambda : public Lambda
		{
		
			boost::shared_ptr<SignedInEventArgs> e;
		
			SignInGamerLambda( const boost::shared_ptr<SignedInEventArgs> &e );

			void Apply();
		};
	
		struct _StartAllProxy : public Lambda
		{
		
			void Apply();
		};

	
		struct NullLambda : public LambdaFunc_1<boost::shared_ptr<CharacterSelect> , bool>
		{
		
			NullLambda();

			bool Apply( const boost::shared_ptr<CharacterSelect> &select );
		};

	
		struct AfterFinishedHelper : public Lambda
		{
			void Apply();
		};

		struct QuickJoinFinishHelper : public Lambda
		{
			void Apply();
		};
	
		static boost::shared_ptr<Lambda> OnBack, OnDone;

		static boost::shared_ptr<GUI_Panel> ParentPanel;

	
		static boost::shared_ptr<CharacterSelectManager> instance;
	
		const static boost::shared_ptr<CharacterSelectManager> &getInstance();

		static std::vector<boost::shared_ptr<CharacterSelect> > CharSelect;
		static bool IsShowing;

	
		static boost::shared_ptr<FancyVector2> CamPos;
	
		static boost::shared_ptr<EzText> ChooseYourHero_Text;
	
		static bool Show_ChooseYourHero;

		static int ChooseYourHero_LerpLength;

		static Vector2 HidePos, ShowPos;

	
		CharacterSelectManager();

#if defined(XBOX) || defined(XBOX_SIGNIN)
	
		void SignedInGamer_SignedIn( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<SignedInEventArgs> &e );

#endif

	
		static boost::shared_ptr<Set<boost::shared_ptr<Hat> > > AvailableHats;
		static void UpdateAvailableHats();

		static boost::shared_ptr<Set<boost::shared_ptr<Hat> > > AvailableBeards;
	
		static void UpdateAvailableBeards();

		static boost::shared_ptr<CharSelectBackdrop> Backdrop;
		static bool QuickJoin;
	
		static void Start( const boost::shared_ptr<GUI_Panel> &Parent, bool QuickJoin);

	
		static void _StartAll();

		static void Start( int PlayerIndex, bool QuickJoin );

	
		static void FinishAll();

		static void Finish( int PlayerIndex, bool Join );

	
		static void EndCharSelect( int DelayOnReturn, int DelayKillCharSelect );

		static void Cleanup();

		static bool AllExited();

		static bool FakeHide;
		static bool AllFinished();

		static bool AllNull();

		static boost::shared_ptr<NullLambda> NullLambda_static;
	
		static int DrawLayer;
		static float BobZoom;
		static float ZoomMod;
		static void Draw();

	
		static void AfterFinished();

		static bool Active;
	
		static void PhsxStep();

		static void QuickJoinFinish();
	};
}


#endif	//#ifndef CHARSELECTMANAGER
