#include "Boulder.h"
#include "Game/Tilesets/SpriteInfo.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Objects/In Game Objects/Obstacles/Boulder__Auto.h"
#include "Game/Tools/Recycler.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Tools/Tools.h"
#include "Game/Objects/ObjectBase.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void Boulder::BoulderTileInfo::InitializeInstanceFields()
	{
		Ball = std::make_shared<SpriteInfo>( 0, Vector2::One );
		Radius = 120;
		Chain = std::make_shared<LineSpriteInfo>( _T( "chain_tile" ), 44, 63, 0, ( Color( 255, 255, 255, 210 ) ).ToVector4(),.2f );
	}

	void Boulder::OnAttachedToBlock()
	{
		_CircleDeath::OnAttachedToBlock();

		getCore()->DrawLayer2 = getCore()->ParentBlock->getCore()->DrawLayer + 1;
	}

	void Boulder::MakeNew()
	{
		_CircleDeath::MakeNew();

		AutoGenSingleton = Boulder_AutoGen::getInstance();
		getCore()->MyType = ObjectType_BOULDER;
		DeathType = Bob::BobDeathType_BOULDER;

		getCore()->ContinuousEnabled = true;

		Angle = 0;
		MaxAngle = 0;
		Period = 150;
		Offset = 0;
		PivotPoint = Vector2::Zero;

		AddAngle = 0;
		PivotLocationType = PivotLocationTypes_TOP_BOTTOM;

		SetLayers();
	}

	void Boulder::Init( Vector2 pos, const std::shared_ptr<Level> &level )
	{
		_CircleDeath::Init( pos, level );

		Radius = 120;

		getCore()->Init();
		getCore()->ContinuousEnabled = true;

		getCore()->GenData.OverlapWidth = 60;

		Circle->setCenter( getCore()->Data.Position );
		getCore()->Data.Position = getCore()->StartData.Position = PivotPoint = pos;

		std::shared_ptr<BoulderTileInfo> info = level->getInfo()->Boulders;

		if ( !level->BoxesOnly )
		{
			if ( info->Ball->Sprite == 0 )
				MyQuad->Show = false;
			else
			{
				MyQuad->Set( info->Ball );
			}
		}

		SetLayers();
	}

	void Boulder::SetLayers()
	{
		getCore()->DrawLayer = 7;
		getCore()->DrawLayer2 = 8;
	}

	Boulder::Boulder( bool BoxesOnly )
	{
		InitializeInstanceFields();
		_CircleDeath::Construct( BoxesOnly );

		if ( !getCore()->BoxesOnly )
		{
			MyQuad = std::make_shared<QuadClass>();
		}
	}

	Microsoft::Xna::Framework::Vector2 Boulder::TR_Bound()
	{
		Vector2 TR = GetPos( 0 );
		float step = .2f;
		float t = step;
		while ( t <= 1 )
		{
			TR = Vector2::Max( TR, GetPos( t ) );
			t += step;
		}

		return TR;
	}

	Microsoft::Xna::Framework::Vector2 Boulder::BL_Bound()
	{
		Vector2 BL = GetPos( 0 );
		float step = .2f;
		float t = step;
		while ( t <= 1 )
		{
			BL = Vector2::Min( BL, GetPos( t ) );
			t += step;
		}

		return BL;
	}

	float Boulder::MinY()
	{
		return PivotPoint.Y - Length;
	}

	Microsoft::Xna::Framework::Vector2 Boulder::GetPos( float t )
	{
		CorrespondingAngle = MaxAngle * static_cast<float>( cos( 2 * M_PI * t ) );
		Vector2 Dir = Vector2( static_cast<float>( cos( AddAngle + CorrespondingAngle - M_PI / 2 ) ), static_cast<float>( sin( AddAngle + CorrespondingAngle - M_PI / 2 ) ) );
		Vector2 Pos = PivotPoint + Length * Dir;

		return Pos;
	}

	void Boulder::PhsxStep()
	{
		if ( PivotLocationType == PivotLocationTypes_TOP_BOTTOM && ( PivotPoint.X > getCore()->MyLevel->getMainCamera()->TR.X + Length || PivotPoint.X < getCore()->MyLevel->getMainCamera()->BL.X - Length ) || PivotLocationType == PivotLocationTypes_LEFT_RIGHT && (PivotPoint.Y > getCore()->MyLevel->getMainCamera()->TR.Y + Length || PivotPoint.Y < getCore()->MyLevel->getMainCamera()->BL.Y - Length) )
		{
			float PhsxCutoff = 200;
			if ( getCore()->MyLevel->BoxesOnly )
				PhsxCutoff = -100;
			if ( !getCore()->MyLevel->getMainCamera()->OnScreen(getCore()->Data.Position, PhsxCutoff) )
			{
				getCore()->SkippedPhsx = true;
				getCore()->WakeUpRequirements = true;
				return;
			}
		}
		getCore()->SkippedPhsx = false;

		Radius = getInfo()->Boulders->Radius;

		float Step = CoreMath::Modulo( getCore()->MyLevel->IndependentPhsxStep + Offset, static_cast<float>(Period) );
		float t = static_cast<float>( Step ) / static_cast<float>( Period );

		Vector2 Pos = GetPos( t );
		Angle = CorrespondingAngle;

		getCore()->Data.Position = Pos;

		ActivePhsxStep();
	}

	void Boulder::DrawGraphics()
	{
		if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer )
		{
			if ( PivotLocationType == PivotLocationTypes_TOP_BOTTOM )
			{
				if ( PivotPoint.X > getCore()->MyLevel->getMainCamera()->TR.X || PivotPoint.X < getCore()->MyLevel->getMainCamera()->BL.X )
				{
					Vector2 BL = Circle->BL - Vector2( 170, 170 );
					if ( BL.X > getCore()->MyLevel->getMainCamera()->TR.X || BL.Y > getCore()->MyLevel->getMainCamera()->TR.Y )
					{
						OffScreen = true;
						return;
					}
					Vector2 TR = Circle->TR + Vector2( 170, 170 );
					if ( TR.X < getCore()->MyLevel->getMainCamera()->BL.X || TR.Y < getCore()->MyLevel->getMainCamera()->BL.Y )
					{
						OffScreen = true;
						return;
					}
				}
			}
			else
			{
				if ( PivotPoint.Y > getCore()->MyLevel->getMainCamera()->TR.Y || PivotPoint.Y < getCore()->MyLevel->getMainCamera()->BL.Y )
				{
					Vector2 BL = Circle->BL - Vector2( 170, 170 );
					if ( BL.Y > getCore()->MyLevel->getMainCamera()->TR.Y || BL.Y > getCore()->MyLevel->getMainCamera()->TR.Y )
					{
						OffScreen = true;
						return;
					}
					Vector2 TR = Circle->TR + Vector2( 170, 170 );
					if ( TR.Y < getCore()->MyLevel->getMainCamera()->BL.Y || TR.Y < getCore()->MyLevel->getMainCamera()->BL.Y )
					{
						OffScreen = true;
						return;
					}
				}
			}

			OffScreen = false;
		}
		else
			if ( OffScreen )
				return;

		if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer )
		{
			Tools::QDrawer->DrawLine( getCore()->Data.Position, PivotPoint, getInfo()->Boulders->Chain );
		}
		else if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer2 )
		{
			if ( MyQuad != 0 && MyQuad->Show )
			{
				MyQuad->PointxAxisTo( Angle );
				MyQuad->setPos( getPos() );

				MyQuad->Draw();
			}
		}
	}

	void Boulder::DrawBoxes()
	{
		Tools::QDrawer->DrawLine( PivotPoint, getCore()->Data.Position, Color(255, 255, 255, 215), 20 );

		Circle->Draw( Color::LightSlateGray );
	}

	void Boulder::CalculateLength()
	{
		Length = ( getCore()->StartData.Position - PivotPoint )->Length();
	}

	void Boulder::Move( Vector2 shift )
	{
		PivotPoint += shift;

		_CircleDeath::Move( shift );
	}

	void Boulder::MoveToBounded( Vector2 shift )
	{
		Move( shift );
	}

	void Boulder::Reset( bool BoxesOnly )
	{
		_CircleDeath::Reset( BoxesOnly );

		getCore()->Data.Velocity = Vector2::Zero;
	}

	void Boulder::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<Boulder> FloaterA = dynamic_cast<Boulder*>( A );
		Init( FloaterA->getPos(), FloaterA->getMyLevel() );

		Angle = FloaterA->Angle;
		MaxAngle = FloaterA->MaxAngle;
		Period = FloaterA->Period;
		Offset = FloaterA->Offset;
		PivotPoint = FloaterA->PivotPoint;
		Length = FloaterA->Length;

		AddAngle = FloaterA->AddAngle;
		PivotLocationType = FloaterA->PivotLocationType;

		getCore()->WakeUpRequirements = true;
	}

	void Boulder::InitializeInstanceFields()
	{
		OffScreen = false;
	}
}
