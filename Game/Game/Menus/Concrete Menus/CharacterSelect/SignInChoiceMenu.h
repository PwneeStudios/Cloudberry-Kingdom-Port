#ifndef SIGNINCHOICEMENU
#define SIGNINCHOICEMENU

#include <global_header.h>

namespace CloudberryKingdom
{

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	struct SignInMenu : public CkBaseMenu
	{

		virtual ~SignInMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "SignInMenu" );
#endif
		}


		struct SignInNoLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SignInMenu> sim;
		
			SignInNoLambda( const boost::shared_ptr<SignInMenu> &sim );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct SignInYesLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SignInMenu> sim;
		
			SignInYesLambda( const boost::shared_ptr<SignInMenu> &sim );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		SignInMenu( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
		boost::shared_ptr<SignInMenu> SignInMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
	
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
