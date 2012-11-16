#ifndef LOADINGSCREEN
#define LOADINGSCREEN

#include "ILoadingScreen.h"
#include <string>
#include <vector>
#include <tchar.h>

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class ObjectClass;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class Camera;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class LoadingScreen : public ILoadingScreen
	{
	public:
		static int DefaultMinLoadLength;
		static int MinLoadLength;

		bool Fake;
		void MakeFake();

	private:
		std::shared_ptr<QuadClass> BackgroundQuad, BlackQuad;
		std::shared_ptr<ObjectClass> CenterObject;
		std::shared_ptr<EzText> LoadingText, HintText;

		std::shared_ptr<EzText> TextObject;

		bool Fade;
		float FadeAlpha;

	public:
		void AddHint( const std::wstring &hint, int extra_wait );

		LoadingScreen();

	private:
		int MinLoading;
	public:
		void Start();

		void End();

		void PreDraw();

		void Draw( const std::shared_ptr<Camera> &cam );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LOADINGSCREEN
