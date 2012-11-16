#ifndef EZEFFECTWAD
#define EZEFFECTWAD

#include <string>
#include <vector>
#include <tchar.h>

namespace CloudberryKingdom
{
	class EzEffect;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class Effect;
			}
		}
	}
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;

namespace CloudberryKingdom
{
	class EzEffectWad
	{
	public:
		Vector2 ModZoom;

		std::vector<EzEffect*> EffectList;

	private:
		Vector4 _CameraPosition;
	public:
		const Vector4 &getCameraPosition() const;
		void setCameraPosition( const Vector4 &value );
		void SetCameraPosition( Vector4 CameraPosition );

	private:
		Vector4 HoldCamPos;
	public:
		void SetDefaultZoom();

		void ResetCameraPos();

		EzEffectWad();

		std::shared_ptr<EzEffect> FindByName( const std::wstring &name );

		void AddEffect( const std::shared_ptr<Effect> &effect, const std::wstring &Name );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EZEFFECTWAD
