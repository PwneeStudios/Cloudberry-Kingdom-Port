#ifndef EZEFFECT
#define EZEFFECT

#include <global_header.h>

#include "Hacks/XNA/Effect.h"
#include "Hacks/XNA/EffectTechnique.h"

namespace CloudberryKingdom
{
	struct EzEffect
	{
	
		// FIXME: Pointer to the parent; should be weak_ptr.
		EzEffectWad *MyWad;

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

	
		void InitializeInstanceFields();


		EzEffect()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef EZEFFECT
