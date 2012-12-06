#ifndef VERIFYQUITGAME
#define VERIFYQUITGAME

#include <global_header.h>

namespace CloudberryKingdom
{
	class VerifyQuitGameMenu2 : public VerifyBaseMenu
	{
	private:
		class InitTextureNameSetter : public Lambda
		{
		private:
			std::shared_ptr<QuadClass> Berry;
			std::wstring textureName;

		public:
			InitTextureNameSetter( const std::shared_ptr<QuadClass> &Berry, const std::wstring &textureName );

			void Apply();
		};

	public:
		VerifyQuitGameMenu2( int Control );

	private:
		std::shared_ptr<QuadClass> Berry;
	public:
		virtual void MakeBackdrop();

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	public:
		virtual void Init();

	private:
		void SetPosition();
	};
}


#endif	//#ifndef VERIFYQUITGAME
