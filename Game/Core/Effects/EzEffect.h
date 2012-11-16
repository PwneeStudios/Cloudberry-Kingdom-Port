#ifndef EZEFFECT
#define EZEFFECT

#include <string>

namespace CloudberryKingdom
{
	class EzEffectWad;
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

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class EffectParameter;
			}
		}
	}
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class EffectTechnique;
			}
		}
	}
}

namespace CloudberryKingdom
{
	class EzTexture;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;

namespace CloudberryKingdom
{
	class EzEffect
	{
	public:
		std::shared_ptr<EzEffectWad> MyWad;

		std::shared_ptr<Effect> effect;
		std::wstring Name;
		std::shared_ptr<EffectParameter> xFlip, yFlip, FlipCenter, xTexture, ExtraTexture1_Param, ExtraTexture2_Param, Illumination, FlipVector, t, xCameraAspect, xCameraPos, Hsl;
		std::shared_ptr<EffectTechnique> Simplest;

		float CurrentIllumination;

		/// <summary>
		/// Whether the effect has the up-to-date parameters set
		/// </summary>
		bool IsUpToDate;
		Vector4 MySetCameraPosition;

		void SetCameraParameters();

		std::shared_ptr<EzTexture> ExtraTexture1;
		void SetExtraTexture1( const std::shared_ptr<EzTexture> &texture );

		std::shared_ptr<EzTexture> ExtraTexture2;
		void SetExtraTexture2( const std::shared_ptr<EzTexture> &texture );

	private:
		void InitializeInstanceFields();

public:
		EzEffect()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef EZEFFECT
