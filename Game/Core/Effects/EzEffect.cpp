#include <global_header.h>

namespace CloudberryKingdom
{

	EzEffect::EzEffect() :
		IsUpToDate( false )
	{
		InitializeInstanceFields();
	}

	void EzEffect::SetCameraParameters()
	{
		Vector4 CameraPosition = MyWad->getCameraPosition();

		if ( CameraPosition != MySetCameraPosition )
		{
			xCameraPos->SetValue( CameraPosition );
			MySetCameraPosition = CameraPosition;
		}

		IsUpToDate = true;
	}

	void EzEffect::SetExtraTexture1( const boost::shared_ptr<EzTexture> &texture )
	{
		if ( ExtraTexture1 == texture )
			return;

		ExtraTexture1 = texture;

		if ( texture != 0 )
			ExtraTexture1_Param->SetValue( texture->getTex() );
	}

	void EzEffect::SetExtraTexture2( const boost::shared_ptr<EzTexture> &texture )
	{
		if ( ExtraTexture2 == texture )
			return;

		ExtraTexture2 = texture;

		if ( texture != 0 )
			ExtraTexture2_Param->SetValue( texture->getTex() );
	}

	void EzEffect::InitializeInstanceFields()
	{
		CurrentIllumination = 0;
	}
}
