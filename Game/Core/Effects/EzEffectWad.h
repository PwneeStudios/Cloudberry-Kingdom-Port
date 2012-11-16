#ifndef EZEFFECTWAD
#define EZEFFECTWAD

#include <global_header.h>

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
