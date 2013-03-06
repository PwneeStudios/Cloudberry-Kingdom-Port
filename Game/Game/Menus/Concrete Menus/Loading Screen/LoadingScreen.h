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

		int DrawCount;
		static const int DrawCount_Max;

		bool Fake;
		void MakeFake();

	
		boost::shared_ptr<QuadClass> BackgroundQuad, BlackQuad;
		boost::shared_ptr<ObjectClass> CenterObject;
		boost::shared_ptr<EzText> LoadingText, HintText;

		boost::shared_ptr<EzText> TextObject;

		bool Fade;
		float FadeAlpha;

	
		void AddHint( const std::wstring &hint, int extra_wait );

		LoadingScreen();

	
		int MinLoading;
	
		void Start();

		void End();

		void PreDraw();

		void Draw( const boost::shared_ptr<Camera> &cam );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LOADINGSCREEN
