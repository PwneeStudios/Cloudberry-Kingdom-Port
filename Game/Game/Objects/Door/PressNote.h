#ifndef PRESSNOTE
#define PRESSNOTE

#include <global_header.h>

namespace CloudberryKingdom
{
	class Door;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;



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
