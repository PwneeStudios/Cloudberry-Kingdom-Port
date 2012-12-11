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
		
			std::shared_ptr<SignedInEventArgs> e;
		
			SignInGamerLambda( const std::shared_ptr<SignedInEventArgs> &e );

			void Apply();
		};
	
		struct _StartAllProxy : public Lambda
		{
		
			void Apply();
		};

	
		struct NullLambda : public LambdaFunc_1<std::shared_ptr<CharacterSelect> , bool>
		{
		
			NullLambda();

			bool Apply( const std::shared_ptr<CharacterSelect> &select );
		};

	
		struct AfterFinishedHelper : public Lambda
		{
		
			void Apply();
		};

	
		static std::shared_ptr<Lambda> OnBack, OnDone;

		static std::shared_ptr<GUI_Panel> ParentPanel;

	
		static std::shared_ptr<CharacterSelectManager> instance;
	
		const static std::shared_ptr<CharacterSelectManager> &getInstance();

		static std::vector<std::shared_ptr<CharacterSelect> > CharSelect;
		static bool IsShowing;

	
		static std::shared_ptr<FancyVector2> CamPos;
	
		static std::shared_ptr<EzText> ChooseYourHero_Text;
	
		static bool Show_ChooseYourHero;

		static int ChooseYourHero_LerpLength;

		static Vector2 HidePos, ShowPos;

	
		CharacterSelectManager();

#if defined(XBOX) || defined(XBOX_SIGNIN)
	
		void SignedInGamer_SignedIn( const std::shared_ptr<Object> &sender, const std::shared_ptr<SignedInEventArgs> &e );

#endif

	
		static std::shared_ptr<Set<std::shared_ptr<Hat> > > AvailableHats;
		static void UpdateAvailableHats();

		static std::shared_ptr<Set<std::shared_ptr<Hat> > > AvailableBeards;
	
		static void UpdateAvailableBeards();

		static std::shared_ptr<CharSelectBackdrop> Backdrop;
	
		static void Start( const std::shared_ptr<GUI_Panel> &Parent );

	
		static void _StartAll();

		static void Start( int PlayerIndex, bool QuickJoin );

	
		static void FinishAll();

		static void Finish( int PlayerIndex, bool Join );

	
		static void EndCharSelect( int DelayOnReturn, int DelayKillCharSelect );

		static void Cleanup();

		static bool AllExited();

		static bool AllFinished();

		static bool AllNull();

		static std::shared_ptr<NullLambda> NullLambda_static;
	
		static int DrawLayer;
		static float BobZoom;
		static float ZoomMod;
		static void Draw();

	
		static void AfterFinished();

		static bool Active;
	
		static void PhsxStep();
	};
}


#endif	//#ifndef CHARSELECTMANAGER
