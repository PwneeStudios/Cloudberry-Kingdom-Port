#ifndef SIGNINCHOICEMENU
#define SIGNINCHOICEMENU

#include <global_header.h>

namespace CloudberryKingdom
{

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	struct SignInMenu : public CkBaseMenu
	{
	
		struct SignInNoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<SignInMenu> sim;
		
			SignInNoLambda( const std::shared_ptr<SignInMenu> &sim );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct SignInYesLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<SignInMenu> sim;
		
			SignInYesLambda( const std::shared_ptr<SignInMenu> &sim );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		SignInMenu( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );
		void SignInMenu_Construct( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );
	
		virtual void ReleaseBody();

	
		virtual void Init();

	
		void MakeSignInChoiceMenu();

		void SetPos();

#if defined(XBOX) || defined(XBOX_SIGNIN)
		bool GamerGuideUp;
		bool GuideUpPhsxStep();
#endif

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
#endif
}


#endif	//#ifndef SIGNINCHOICEMENU
