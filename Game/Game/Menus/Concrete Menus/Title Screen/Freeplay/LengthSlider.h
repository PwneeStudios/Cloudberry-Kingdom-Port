#ifndef LENGTHSLIDER
#define LENGTHSLIDER

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class ProgressBar;
}

namespace CloudberryKingdom
{
	class Camera;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;

namespace CloudberryKingdom
{
	class LengthSlider : public MenuSliderBase
	{
	public:
		LengthSlider();
		LengthSlider( const std::shared_ptr<EzText> &Text );
		LengthSlider( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

		int PerceivedMin;

	private:
		std::shared_ptr<ProgressBar> LengthBar;
	protected:
		virtual void InitializeSlider();

	public:
		const virtual Vector2 &getBL() const;
		const virtual Vector2 &getTR() const;
		const virtual Vector2 &getSlider_TR() const;

		virtual void SetCallback();

	protected:
		virtual void CalcEndPoints();

	public:
		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LENGTHSLIDER
