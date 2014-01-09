#include <small_header.h>
#include "Core/Graphics/Draw/Simple/SimpleBox.h"

#include "Core/Graphics/Draw/Object/ObjectBox.h"
#include "Core/Graphics/Draw/Simple/BasePoint.h"
#include "Core/Graphics/Draw/Simple/SimpleVector.h"

#include "Core/Graphics/Draw/Quads/ObjectVector.h"

namespace CloudberryKingdom
{

	void SimpleBox::Release()
	{
		BL.Release();
		TR.Release();
	}

	void SimpleBox::SetHold()
	{
		BL.AnimData.Hold = BL.Pos;
		TR.AnimData.Hold = TR.Pos;
	}

	void SimpleBox::ReadAnim( int anim, int frame )
	{
		BL.Pos = BL.AnimData.Get( anim, frame );
		TR.Pos = TR.AnimData.Get( anim, frame );
	}

	void SimpleBox::Record( int anim, int frame )
	{
		BL.AnimData.Set( BL.Pos, anim, frame );
		TR.AnimData.Set( TR.Pos, anim, frame );
	}

	void SimpleBox::Transfer( int anim, float DestT, int AnimLength, bool Loop, bool Linear, float t )
	{
		BL.Pos = BL.AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
		TR.Pos = TR.AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
	}

	void SimpleBox::Calc( int anim, float t, int AnimLength, bool Loop, bool Linear )
	{
		BL.Pos = BL.AnimData.Calc( anim, t, AnimLength, Loop, Linear );
		TR.Pos = TR.AnimData.Calc( anim, t, AnimLength, Loop, Linear );
	}

	SimpleBox::SimpleBox( const boost::shared_ptr<SimpleBox> &box )
	{
		Animated = box->Animated;

		BL = box->BL;
		TR = box->TR;
	}

	SimpleBox::SimpleBox( const boost::shared_ptr<ObjectBox> &box )
	{
		Animated = true;

		BL.Pos = box->BL->Pos;
		TR.Pos = box->TR->Pos;

		BL.AnimData = box->BL->AnimData;
		TR.AnimData = box->TR->AnimData;
			BL.AnimData.Anims = std::vector<OneAnim>(); BL.AnimData.Anims.push_back( box->BL->AnimData.Anims[ 0 ] );
			TR.AnimData.Anims = std::vector<OneAnim>(); TR.AnimData.Anims.push_back( box->TR->AnimData.Anims[ 0 ] );
	}

	void SimpleBox::CopyUpdate( boost::shared_ptr<SimpleBox> &SourceBox, Vector2 &shift )
	{
		BL.Vertex.xy = SourceBox->BL.Vertex.xy + shift;
		TR.Vertex.xy = SourceBox->TR.Vertex.xy + shift;
	}

	void SimpleBox::Update( BasePoint &Base )
	{
		BL.Vertex.xy = Base.Origin + BL.Pos.X * Base.e1 + BL.Pos.Y * Base.e2;
		TR.Vertex.xy = Base.Origin + TR.Pos.X * Base.e1 + TR.Pos.Y * Base.e2;
	}

	Vector2 SimpleBox::Center()
	{
		return ( TR.Vertex.xy + BL.Vertex.xy ) / 2;
	}

	float SimpleBox::Width( BasePoint &Base )
	{
		return ( TR.Pos.X - BL.Pos.X ) * Base.e1.Length();
	}

	Vector2 SimpleBox::Size()
	{
		return ( TR.Vertex.xy - BL.Vertex.xy );
	}
}
