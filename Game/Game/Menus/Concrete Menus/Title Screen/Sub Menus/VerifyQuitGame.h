#ifndef VERIFYQUITGAME
#define VERIFYQUITGAME

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

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

		//public static int Version = 0;
//C# TO C++ CONVERTER NOTE: The variable Version was renamed since it is named the same as a user-defined type:
		static int Version_Renamed;

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
