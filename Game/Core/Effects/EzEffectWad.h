#ifndef EZEFFECTWAD
#define EZEFFECTWAD

#include <global_header.h>

#include "Hacks/XNA/Effect.h"
#include "Hacks/XNA/EffectParameter.h"

namespace CloudberryKingdom
{

	struct EzEffectWad : std::enable_shared_from_this<EzEffectWad>
	{
	
		Vector2 ModZoom;

		typedef std::vector<std::shared_ptr<EzEffect> > EffectVec;
		EffectVec EffectList;

	
		Vector4 _CameraPosition;
	
		const Vector4 &getCameraPosition() const;
		void setCameraPosition( const Vector4 &value );
		void SetCameraPosition( Vector4 CameraPosition );

	
		Vector4 HoldCamPos;
	
		void SetDefaultZoom();

		void ResetCameraPos();

		EzEffectWad();

		std::shared_ptr<EzEffect> FindByName( const std::wstring &name );

		void AddEffect( const std::shared_ptr<Effect> &effect, const std::wstring &Name );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EZEFFECTWAD
