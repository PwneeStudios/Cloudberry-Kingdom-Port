#ifndef LOADINGSCREEN
#define LOADINGSCREEN

#include <small_header.h>

//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Core/Graphics/Draw/Quads/BaseQuad.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/Concrete Menus/Loading Screen/ILoadingScreen.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Player/Hero Physics/Box.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/CkColorHelper.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


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
