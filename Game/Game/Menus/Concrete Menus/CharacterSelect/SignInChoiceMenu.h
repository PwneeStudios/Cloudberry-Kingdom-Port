#ifndef SIGNINCHOICEMENU
#define SIGNINCHOICEMENU

#include <global_header.h>

namespace CloudberryKingdom
{

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	class SignInMenu : public CkBaseMenu
	{
	private:
		class SignInNoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<SignInMenu> sim;
		public:
			SignInNoLambda( const std::shared_ptr<SignInMenu> &sim );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class SignInYesLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<SignInMenu> sim;
		public:
			SignInYesLambda( const std::shared_ptr<SignInMenu> &sim );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	public:
		SignInMenu( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect );

	protected:
		virtual void ReleaseBody();

	public:
		virtual void Init();

	private:
		void MakeSignInChoiceMenu();

		void SetPos();

#if defined(XBOX) || defined(XBOX_SIGNIN)
		bool GamerGuideUp;
		bool GuideUpPhsxStep();
#endif

	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
#endif
}


#endif	//#ifndef SIGNINCHOICEMENU
