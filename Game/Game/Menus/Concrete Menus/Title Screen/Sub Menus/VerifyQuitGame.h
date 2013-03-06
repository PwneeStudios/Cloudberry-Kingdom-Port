#ifndef VERIFYQUITGAME
#define VERIFYQUITGAME

#include <global_header.h>

namespace CloudberryKingdom
{
	struct VerifyQuitGameMenu2 : public VerifyBaseMenu
	{

		virtual ~VerifyQuitGameMenu2()
		{
#ifdef BOOST_BIN
			OnDestructor( "VerifyQuitGameMenu2" );
#endif
		}

	
		struct InitTextureNameSetter : public Lambda
		{
		
			boost::shared_ptr<QuadClass> Berry;
			std::wstring textureName;

		
			InitTextureNameSetter( const boost::shared_ptr<QuadClass> &Berry, const std::wstring &textureName );

			void Apply();
		};

	
		VerifyQuitGameMenu2( int Control );
		boost::shared_ptr<VerifyQuitGameMenu2> VerifyQuitGameMenu2_Construct( int Control );
	
		boost::shared_ptr<QuadClass> Berry;
	
		virtual void MakeBackdrop();

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

	
		virtual void Init();

	
		void SetPosition();
	};
}


#endif	//#ifndef VERIFYQUITGAME
