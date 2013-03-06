#ifndef EZEFFECT
#define EZEFFECT

#include <global_header.h>

#include "Graphics/Effect.h"
#include "Graphics/EffectTechnique.h"

namespace CloudberryKingdom
{

	struct EzEffect
	{
	
		// FIXME: Pointer to the parent; should be weak_ptr.
		boost::shared_ptr<EzEffectWad> MyWad;

		boost::shared_ptr<Effect> effect;
		std::wstring Name;
		boost::shared_ptr<EffectParameter> xFlip, yFlip, FlipCenter, xTexture, ExtraTexture1_Param, ExtraTexture2_Param, Illumination, FlipVector, t, xCameraAspect, xCameraPos, Hsl;
		boost::shared_ptr<EffectTechnique> Simplest;

		float CurrentIllumination;

		/// <summary>
		/// Whether the effect has the up-to-date parameters set
		/// </summary>
		bool IsUpToDate;
		Vector4 MySetCameraPosition;

		void SetCameraParameters();

		boost::shared_ptr<EzTexture> ExtraTexture1;
		void SetExtraTexture1( const boost::shared_ptr<EzTexture> &texture );

		boost::shared_ptr<EzTexture> ExtraTexture2;
		void SetExtraTexture2( const boost::shared_ptr<EzTexture> &texture );

	
		void InitializeInstanceFields();

		EzEffect();

	};
}


#endif	//#ifndef EZEFFECT
