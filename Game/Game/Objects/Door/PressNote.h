#ifndef PRESSNOTE
#define PRESSNOTE

#include "../Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "../Core/Text/EzText.h"
#include <cmath>
#include <tchar.h>

namespace CloudberryKingdom
{
	class Door;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class PressNote : public GUI_Text
	{
	public:
		static const int ButtonScale = 87;
		static const float TextScale;

	private:
		std::shared_ptr<Door> Parent;

#if defined(PC_VERSION)
	public:
		PressNote( const std::shared_ptr<Door> &Parent );
	#else
		PressNote( const std::shared_ptr<Door> &Parent );
#endif

	private:
		int Life;

	public:
		int LifeSpeed; //9;
		void FadeIn();

		int DelayToFadeOut; //80;
	private:
		int Count;
	public:
		void FadeOut();

	protected:
		virtual void MyPhsxStep();

	public:
		virtual void Draw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PRESSNOTE
