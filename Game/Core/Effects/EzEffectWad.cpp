#include <global_header.h>

#include "Hacks/String.h"

namespace CloudberryKingdom
{

	const Vector4 &EzEffectWad::getCameraPosition() const
	{
		return _CameraPosition;
	}

	void EzEffectWad::setCameraPosition( const Vector4 &value )
	{
		_CameraPosition = value;
	}

	void EzEffectWad::SetCameraPosition( Vector4 CameraPosition )
	{
		//CameraPosition.Z *= -1;
		CameraPosition.Z *= ModZoom.X;
		CameraPosition.W *= ModZoom.Y;

		this->setCameraPosition( CameraPosition );

		for ( EffectVec::const_iterator effect = EffectList.begin(); effect != EffectList.end(); ++effect )
			( *effect )->IsUpToDate = false;
	}

	void EzEffectWad::SetDefaultZoom()
	{
		HoldCamPos = getCameraPosition();
		SetCameraPosition( Vector4( getCameraPosition().X, getCameraPosition().Y, 0.001f, 0.001f ) );
	}

	void EzEffectWad::ResetCameraPos()
	{
		SetCameraPosition( HoldCamPos );
	}

	EzEffectWad::EzEffectWad()
	{
		InitializeInstanceFields();
		EffectList = EffectVec();
	}

	std::shared_ptr<EzEffect> EzEffectWad::FindByName( const std::wstring &name )
	{
		for ( EffectVec::const_iterator effect = EffectList.begin(); effect != EffectList.end(); ++effect )
			if ( ( *effect )->Name.compare( name ) == 0 )
				return *effect;
		return Tools::BasicEffect;
	}

	void EzEffectWad::AddEffect( const std::shared_ptr<Effect> &effect, const std::wstring &Name )
	{
		for ( EffectVec::const_iterator e = EffectList.begin(); e != EffectList.end(); ++e )
		{
			// FIXME: This "should" compare while disregarding case.
			if ( CompareIgnoreCase( Name, ( *e )->Name ) == 0 )
			{
				( *e )->effect = effect;
				return;
			}
		}

		std::shared_ptr<EzEffect> Neweffect = std::make_shared<EzEffect>();
		Neweffect->Name = Name;
		Neweffect->effect = effect;

		Neweffect->FlipVector = effect->Parameters( "u_flipVector" );
		Neweffect->FlipCenter = effect->Parameters( "u_flipCenter" );
		Neweffect->xTexture = effect->Parameters( "u_texture" );
		Neweffect->Illumination = effect->Parameters( "u_illumination" );
		Neweffect->t = effect->Parameters( "t" );
		Neweffect->xCameraAspect = effect->Parameters( "u_cameraAspect" );
		Neweffect->xCameraPos = effect->Parameters("u_cameraPos" );

		Neweffect->ExtraTexture1_Param = effect->Parameters( "ExtraTexture1" );
		Neweffect->ExtraTexture2_Param = effect->Parameters( "ExtraTexture2" );

		Neweffect->Hsl = effect->Parameters( "ColorMatrix" );

		Neweffect->Simplest = effect->Techniques( "Simplest" );

		Neweffect->MyWad = shared_from_this();

		EffectList.push_back( Neweffect );
	}

	void EzEffectWad::InitializeInstanceFields()
	{
		ModZoom = Vector2(1);
	}
}
