#include <global_header.h>

namespace CloudberryKingdom
{
	Vector2 AABox::RealTR()
	{
		return Vector2::Max( TR, BL );
	}

	Vector2 AABox::RealBL()
	{
		return Vector2::Min( TR, BL );
	}

	void AABox::MakeNew()
	{
		TopOnly = false;
		NoSides = false;
		Invalidated = true;
	}

	AABox::AABox()
	{
		MakeNew();
	}

	AABox::AABox( Vector2 center, Vector2 size )
	{
		TopOnly = false;
		NoSides = false;
		Initialize( center, size );
	}

	void AABox::Move( Vector2 shift )
	{
		Current->Center += shift;
		Target->Center += shift;

		Current->CalcBounds();
		Target->CalcBounds();

		CalcBounds();
	}

	void AABox::Clone( const boost::shared_ptr<AABox> &A )
	{
		Current->Clone( A->Current );
		Target->Clone( A->Target );
		TopOnly = A->TopOnly;
		NoSides = A->NoSides;
	}

	void AABox::Write( const boost::shared_ptr<BinaryWriter> &writer )
	{
		writer->Write( TopOnly );
		Current->Write( writer );
		Target->Write( writer );

	}

	void AABox::Read( const boost::shared_ptr<BinaryReader> &reader )
	{
		TopOnly = reader->ReadBoolean();
		if ( Current == 0 )
			Current = boost::make_shared<FloatRectangle>();
		Current->Read( reader );
		if ( Target == 0 )
			Target = boost::make_shared<FloatRectangle>();
		Target->Read( reader );
	}

	void AABox::Extend( Side side, float pos )
	{
		switch ( side )
		{
			case Side_LEFT:
				Target->BL.X = pos;
				break;
			case Side_RIGHT:
				Target->TR.X = pos;
				break;
			case Side_TOP:
				Target->TR.Y = pos;
				break;
			case Side_BOTTOM:
				Target->BL.Y = pos;
				break;
		}

		Target->FromBounds();
		SwapToCurrent();
	}

	void AABox::DrawFilled( const boost::shared_ptr<QuadDrawer> &QDrawer, Color color )
	{
		QDrawer->DrawFilledBox( Current->BL, Current->TR, color );
		QDrawer->Flush();
	}

	void AABox::Draw( Color color, float Width )
	{
		Draw( Tools::QDrawer, color, Width, true );
	}

	void AABox::Draw( const boost::shared_ptr<QuadDrawer> &QDrawer, Color color, float Width )
	{
		Draw( QDrawer, color, Width, false );
	}

	void AABox::Draw( const boost::shared_ptr<QuadDrawer> &QDrawer, Color color, float Width, bool DisregardTopOnly )
	{
		Vector2 BR, TL;
		BR = Vector2( Current->TR.X, Current->BL.Y );
		TL = Vector2( Current->BL.X, Current->TR.Y );
		if ( !TopOnly || DisregardTopOnly )
		{
			QDrawer->DrawLine( Current->BL, BR, color, Width );
			QDrawer->DrawLine( Current->TR, BR, color, Width );
			QDrawer->DrawLine( Current->BL, TL, color, Width );
		}
		QDrawer->DrawLine( Current->TR, TL, color, Width );
		QDrawer->Flush();
	}

	void AABox::DrawT( Color color, float Width )
	{
		DrawT( Tools::QDrawer, color, Width );
	}

	void AABox::DrawT( const boost::shared_ptr<QuadDrawer> &QDrawer, Color color, float Width )
	{
		Vector2 BR, TL;
		BR = Vector2( Target->TR.X, Target->BL.Y );
		TL = Vector2( Target->BL.X, Target->TR.Y );
		QDrawer->DrawLine( Target->BL, BR, color, Width );
		QDrawer->DrawLine( Target->TR, BR, color, Width );
		QDrawer->DrawLine( Target->BL, TL, color, Width );
		QDrawer->DrawLine( Target->TR, TL, color, Width );
		QDrawer->Flush();
	}

	void AABox::Initialize( Vector2 center, Vector2 size )
	{
		if ( Current == 0 )
			Current = boost::make_shared<FloatRectangle>( center, size );
		else
			Current->Set( center, size );
		if ( Target == 0 )
			Target = boost::make_shared<FloatRectangle>( center, size );
		else
			Target->Set( center, size );

		Invalidated = true;
	}

	Vector2 AABox::GetTR()
	{
		Validate();
		return TR;
	}

	Vector2 AABox::GetBL()
	{
		Validate();
		return BL;
	}

	float AABox::BoxSize()
	{
		return Tools::BoxSize( TR, BL );
	}

	void AABox::CalcBounds()
	{
		TR = Vector2::Max( Current->TR, Target->TR );
		BL = Vector2::Min( Current->BL, Target->BL );

		if ( TopOnly )
			BL.Y = TR.Y;
	}

	void AABox::CalcBounds_Full()
	{
		Current->CalcBounds();
		Target->CalcBounds();

		TR = Vector2::Max( Current->TR, Target->TR );
		BL = Vector2::Min( Current->BL, Target->BL );

		if ( TopOnly )
			BL.Y = TR.Y;
	}

	void AABox::Validate()
	{
		if ( Invalidated )
		{
			CalcBounds();

			Invalidated = false;
		}
	}

	void AABox::SetCurrent( Vector2 center, Vector2 size )
	{
		Current->Set( center, size );

		Invalidated = true;
	}

	void AABox::SetTarget( Vector2 center, Vector2 size )
	{
		Target->Set( center, size );

		Invalidated = true;
	}

	void AABox::SwapToCurrent()
	{
		Current->Set( Target->Center, Target->Size );

		Invalidated = true;
	}

	float AABox::xSpeed()
	{
		return ( Target->TR.X - Current->TR.X + Target->BL.X - Current->BL.X ) / 2;
	}

	float AABox::RightSpeed()
	{
		return Target->TR.X - Current->TR.X;
	}

	float AABox::LeftSpeed()
	{
		return Target->BL.X - Current->BL.X;
	}

	void AABox::Scale( float scale )
	{
		Current->Scale( scale );
		Target->Scale( scale );
	}

	void AABox::Invalidate()
	{
		Invalidated = true;
	}
}
