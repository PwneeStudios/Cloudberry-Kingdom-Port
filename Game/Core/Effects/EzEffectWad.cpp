#include <global_header.h>








namespace CloudberryKingdom
{

	const Microsoft::Xna::Framework::Vector4 &EzEffectWad::getCameraPosition() const
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

		for ( std::vector<EzEffect*>::const_iterator effect = EffectList.begin(); effect != EffectList.end(); ++effect )
			( *effect )->IsUpToDate = false;
	}

	void EzEffectWad::SetDefaultZoom()
	{
		HoldCamPos = getCameraPosition();
		SetCameraPosition( Vector4( getCameraPosition().X, getCameraPosition().Y,.001f,.001f ) );
	}

	void EzEffectWad::ResetCameraPos()
	{
		SetCameraPosition( HoldCamPos );
	}

	EzEffectWad::EzEffectWad()
	{
		InitializeInstanceFields();
		EffectList = std::vector<EzEffect*>();
	}

	std::shared_ptr<EzEffect> EzEffectWad::FindByName( const std::wstring &name )
	{
		for ( std::vector<EzEffect*>::const_iterator effect = EffectList.begin(); effect != EffectList.end(); ++effect )
			if ( ( *effect )->Name->compare( name ) == 0 )
				return effect;
		return Tools::BasicEffect;
	}

	void EzEffectWad::AddEffect( const std::shared_ptr<Effect> &effect, const std::wstring &Name )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<EzEffect*>::const_iterator e = EffectList.begin(); e != EffectList.end(); ++e )
		{
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( Name, ( *e )->Name, StringComparison::OrdinalIgnoreCase ) == 0 )
			{
				( *e )->effect = effect;
				return;
			}
		}

		std::shared_ptr<EzEffect> Neweffect = std::make_shared<EzEffect>();
		Neweffect->Name = Name;
		Neweffect->effect = effect;

		Neweffect->FlipVector = effect->Parameters[ _T( "FlipVector" ) ];
		Neweffect->FlipCenter = effect->Parameters[ _T( "FlipCenter" ) ];
		Neweffect->xTexture = effect->Parameters[ _T( "xTexture" ) ];
		Neweffect->Illumination = effect->Parameters[ _T( "Illumination" ) ];
		Neweffect->t = effect->Parameters[ _T( "t" ) ];
		Neweffect->xCameraAspect = effect->Parameters[ _T( "xCameraAspect" ) ];
		Neweffect->xCameraPos = effect->Parameters[ _T( "xCameraPos" ) ];

		Neweffect->ExtraTexture1_Param = effect->Parameters[ _T( "ExtraTexture1" ) ];
		Neweffect->ExtraTexture2_Param = effect->Parameters[ _T( "ExtraTexture2" ) ];

		Neweffect->Hsl = effect->Parameters[ _T( "ColorMatrix" ) ];

		Neweffect->Simplest = effect->Techniques[ _T( "Simplest" ) ];

		Neweffect->MyWad = this;

		EffectList.push_back( Neweffect );
	}

	void EzEffectWad::InitializeInstanceFields()
	{
		ModZoom = Vector2::One;
	}
}
