#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;

namespace CloudberryKingdom
{

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

	void EzEffect::SetExtraTexture1( const std::shared_ptr<EzTexture> &texture )
	{
		if ( ExtraTexture1 == texture )
			return;

		ExtraTexture1 = texture;

		if ( texture != 0 )
			ExtraTexture1_Param->SetValue( texture->getTex() );
	}

	void EzEffect::SetExtraTexture2( const std::shared_ptr<EzTexture> &texture )
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
