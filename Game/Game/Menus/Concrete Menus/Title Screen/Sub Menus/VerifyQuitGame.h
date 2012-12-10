#ifndef VERIFYQUITGAME
#define VERIFYQUITGAME

#include <global_header.h>

namespace CloudberryKingdom
{
	struct VerifyQuitGameMenu2 : public VerifyBaseMenu
	{

	
		struct InitTextureNameSetter : public Lambda
		{
		
			std::shared_ptr<QuadClass> Berry;
			std::wstring textureName;

		
			InitTextureNameSetter( const std::shared_ptr<QuadClass> &Berry, const std::wstring &textureName );

			void Apply();
		};

	
		VerifyQuitGameMenu2( int Control );

	
		std::shared_ptr<QuadClass> Berry;
	
		virtual void MakeBackdrop();

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	
		virtual void Init();

	
		void SetPosition();
	};
}


#endif	//#ifndef VERIFYQUITGAME
