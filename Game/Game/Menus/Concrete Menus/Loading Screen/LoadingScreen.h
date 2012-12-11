#ifndef LOADINGSCREEN
#define LOADINGSCREEN

#include <global_header.h>

namespace CloudberryKingdom
{
	struct LoadingScreen : public ILoadingScreen
	{

	
		static void InitializeStatics();

	
		static int DefaultMinLoadLength;
		static int MinLoadLength;

		bool Fake;
		void MakeFake();

	
		std::shared_ptr<QuadClass> BackgroundQuad, BlackQuad;
		std::shared_ptr<ObjectClass> CenterObject;
		std::shared_ptr<EzText> LoadingText, HintText;

		std::shared_ptr<EzText> TextObject;

		bool Fade;
		float FadeAlpha;

	
		void AddHint( const std::wstring &hint, int extra_wait );

		LoadingScreen();

	
		int MinLoading;
	
		void Start();

		void End();

		void PreDraw();

		void Draw( const std::shared_ptr<Camera> &cam );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LOADINGSCREEN
