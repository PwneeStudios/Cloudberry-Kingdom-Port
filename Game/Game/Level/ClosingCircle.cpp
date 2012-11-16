#include <global_header.h>





namespace CloudberryKingdom
{

	ClosingCircle::ClosingCircle( const std::shared_ptr<Camera> &camera, float Frames )
	{
		InitializeInstanceFields();
		Init( camera, Frames );
	}

	ClosingCircle::ClosingCircle( const std::shared_ptr<Camera> &camera, float Frames, const std::shared_ptr<IPos> &Center )
	{
		InitializeInstanceFields();
		Init( camera, Frames );

		CenterObj = Center;
	}

	ClosingCircle::ClosingCircle( const std::shared_ptr<Camera> &camera, float Frames, Vector2 Center )
	{
		InitializeInstanceFields();
		Init( camera, Frames );

		CenterPos = Center;
	}

	void ClosingCircle::Init( const std::shared_ptr<Camera> &camera, float Frames )
	{
		MyCamera = camera;

		Circle = std::make_shared<QuadClass>();
		Circle->Quad_Renamed->MyEffect = Tools::EffectWad->FindByName( _T( "Circle" ) );
		Circle->Quad_Renamed->MyTexture = Tools::TextureWad->FindByName( _T( "White" ) );

		//Circle.TextureName = "Star";
		//Circle.TextureName = "SpikeBlob";

		Circle->FullScreen( MyCamera );
		Circle->Scale( 1.3f * static_cast<float>( pow( 2,.5f ) ) );
		Circle->Base.e2.Y = Circle->Base.e1.X;

		Speed = Circle->Base.e1.X / Frames;
	}

	void ClosingCircle::UpdateCircle()
	{
		if ( CenterObj == 0 )
			Circle->Base.Origin = CenterPos;
		else
			Circle->Base.Origin = CenterObj->getPos();

		if ( !Tools::StepControl )
		{
			Circle->Base.e1.X -= Speed;
			Circle->Base.e2.Y -= Speed;

			angle += .015f;
			Circle->PointxAxisTo( angle );

			if ( Circle->getSize().X < Speed + 1 )
				Done = true;
			Circle->setSize( Circle->getSize() - Vector2(Speed) );
		}
	}

	void ClosingCircle::Draw()
	{
		if ( !Done )
		{
			UpdateCircle();
			Circle->Draw();
		}
		else
			FinishedCount++;
	}

	void ClosingCircle::InitializeInstanceFields()
	{
		FinishedCount = 0;
		angle = 0;
		Done = false;
	}
}
