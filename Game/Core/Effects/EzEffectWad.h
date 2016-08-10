#ifndef EZEFFECTWAD
#define EZEFFECTWAD

#include <small_header.h>

//#include "Core/Effects/EzEffect.h"
//#include "Game/Tools/Tools.h"


#include "Graphics/Effect.h"
#include "Graphics/EffectParameter.h"

namespace CloudberryKingdom
{

	struct EzEffectWad : boost::enable_shared_from_this<EzEffectWad>
	{
	
		Vector2 ModZoom;

		typedef std::vector<boost::shared_ptr<EzEffect> > EffectVec;
		EffectVec EffectList;

	
		Vector4 _CameraPosition;
	
		const Vector4 &getCameraPosition() const;
		void setCameraPosition( const Vector4 &value );
		void SetCameraPosition( Vector4 CameraPosition );

	
		Vector4 HoldCamPos;
	
		void SetDefaultZoom();

		void ResetCameraPos();

		EzEffectWad();

		boost::shared_ptr<EzEffect> FindByName( const std::wstring &name );

		void AddEffect( const boost::shared_ptr<Effect> &effect, const std::wstring &Name );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EZEFFECTWAD
