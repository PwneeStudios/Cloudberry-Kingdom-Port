#include <global_header.h>

namespace CloudberryKingdom
{

	const float &BackgroundFloater::getSpinVelocity() const
	{
		return _SpinVelocity;
	}

	void BackgroundFloater::setSpinVelocity( const float &value )
	{
		if ( MyQuad != 0 && MyQuad->FancyAngle == 0 )
			MyQuad->FancyAngle = std::make_shared<FancyVector2>();
		_SpinVelocity = value;
	}

	const Vector2 &BackgroundFloater::getPos() const
	{
		return Data.Position;
	}

	void BackgroundFloater::SetPos( Vector2 pos )
	{
		Data.Position = StartData.Position = pos;
	}

	void BackgroundFloater::Release()
	{
		MyLevel.reset();
		MyQuad->Release();
	}

	void BackgroundFloater::SetLevel( const std::shared_ptr<Level> &level )
	{
		MyLevel = level;
	}

	void BackgroundFloater::SetBackground( const std::shared_ptr<Background> &b )
	{
		//MyBackground = b;
	}

	void BackgroundFloater::Reset()
	{
		Data.Position = StartData.Position;
		MyQuad->Quad_Renamed.setUV_Offset( uv_offset );

		InitialUpdate();
	}

	void BackgroundFloater::ChangeParallax( float Prev, float New )
	{
		float ratio = Prev / New;
		Vector2 cam = MyLevel->getMainCamera()->getPos();

		Data.Position = ( Data.Position - cam ) * ratio + cam;
		StartData.Position = ( StartData.Position - cam ) * ratio + cam;
		MyQuad->setSize( MyQuad->getSize() * ratio );

		InitialUpdate();
	}

	void BackgroundFloater::Move( Vector2 shift )
	{
		Data.Position += shift;
		StartData.Position += shift;

		InitialUpdate();
	}

	BackgroundFloater::BackgroundFloater( const std::shared_ptr<BackgroundFloater> &source ) :
		_SpinVelocity( 0 ),
		Data( source->Data ),
		StartData( source->StartData ),
		MyLevel( source->MyLevel ),
		MyQuad( std::make_shared<QuadClass>( source->MyQuad ) ),
		Name( source->Name )
	{
		InitializeInstanceFields();
	}

	BackgroundFloater::BackgroundFloater() :
		_SpinVelocity( 0 )
	{
		InitializeInstanceFields();
		MyQuad = std::make_shared<QuadClass>();
	}

	BackgroundFloater::BackgroundFloater( const std::shared_ptr<Level> &level ) :
		_SpinVelocity( 0 )
	{
		InitializeInstanceFields();
		MyLevel = level;

		MyQuad = std::make_shared<QuadClass>();
	}

	void BackgroundFloater::InitialUpdate()
	{
		MyQuad->Base.Origin = Data.Position = StartData.Position;
		MyQuad->Update();
		MyQuad->UpdateShift_Precalc();

		// If we are repeating more than once, or have UV speed, use texture wrapping.
		MyQuad->Quad_Renamed.U_Wrap = MyQuad->Quad_Renamed.V_Wrap = false;
		if ( uv_speed.X != 0 || MyQuad->Quad_Renamed.getUV_Repeat().X > 1 )
			MyQuad->Quad_Renamed.U_Wrap = true;
		if ( uv_speed.Y != 0 || MyQuad->Quad_Renamed.getUV_Repeat().Y > 1 )
			MyQuad->Quad_Renamed.V_Wrap = true;
	}

	void BackgroundFloater::PhsxStep( const std::shared_ptr<BackgroundFloaterList> &list )
	{
		MyQuad->Quad_Renamed.UV_Phsx( uv_speed );

		Data.Position += Data.Velocity;

		if ( MyQuad->Quad_Renamed.getRight() < list->BL.X - 100 )
			Data.Position.X = list->TR.X + MyQuad->Quad_Renamed.getWidth() / 2 + 50;
		else if ( MyQuad->Quad_Renamed.getLeft() > list->TR.X + 100 )
			Data.Position.X = list->BL.X - MyQuad->Quad_Renamed.getHeight() / 2 - 50;

		MyQuad->Base.Origin = Data.Position;
		//if (MyQuad.TextureName.Contains("chan"))
		//{
		//    MyQuad.PointxAxisTo(CoreMath.Periodic(.005f, -.005f, 300, MyLevel.CurPhsxStep));
		//    InitialUpdate();
		//}
		//else
			MyQuad->PointxAxisTo( 0 );
		MyQuad->Update();

		if ( getSpinVelocity() != 0 )
		{
			MyQuad->setAngle( MyQuad->getAngle() + getSpinVelocity() );
			MyQuad->Update();
		}
		else
		{
			MyQuad->UpdateShift();
		}
	}

	void BackgroundFloater::Draw()
	{
		Tools::QDrawer->DrawQuad( MyQuad->Quad_Renamed );
	}

	void BackgroundFloater::InitializeInstanceFields()
	{
		Name = _T( "" );
		uv_speed = Vector2();
		uv_offset = Vector2();
	}
}
