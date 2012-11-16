#include "SpikeyLine.h"
#include "Game/Tilesets/SpriteInfo.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Objects/In Game Objects/Obstacles/Boulder__Auto.h"
#include "Game/Tools/Recycler.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Objects/ObjectBase.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void SpikeyLine::SpikeyLineTileInfo::InitializeInstanceFields()
	{
		Ball = std::make_shared<SpriteInfo>( 0, Vector2::One );
		Radius = 120;
		Rotate = false;
		RotateOffset = 0;
		RotateSpeed = 0;
	}

	void SpikeyLine::MakeNew()
	{
		_CircleDeath::MakeNew();

		AutoGenSingleton = Boulder_AutoGen::getInstance();
		getCore()->MyType = ObjectType_SPIKEY_LINE;
		DeathType = Bob::BobDeathType_FALLING_SPIKE;

		getCore()->ContinuousEnabled = true;

		Period = 150;
		Offset = 0;
		p1 = Vector2( 0, 1300 );
		p2 = Vector2( 0, -1300 );

		getCore()->DrawLayer = 2;
		getCore()->DrawLayer2 = 6;
	}

	void SpikeyLine::Init( Vector2 pos, const std::shared_ptr<Level> &level )
	{
		_CircleDeath::Init( pos, level );

		if ( !getCore()->BoxesOnly )
		{
			Head->Set( level->getInfo()->SpikeyLines->Ball );
		}
	}

	SpikeyLine::SpikeyLine( bool BoxesOnly )
	{
		InitializeInstanceFields();
		_CircleDeath::Construct( BoxesOnly );

		if ( !getCore()->BoxesOnly )
		{
			Head = std::make_shared<QuadClass>();
		}
	}

	Microsoft::Xna::Framework::Vector2 SpikeyLine::GetPos( float t )
	{
		Vector2 pos = Vector2::Lerp( p1, p2, t );
		return pos;
	}

	void SpikeyLine::PhsxStep()
	{
		float PhsxCutoff = 360;
		if ( !getCore()->MyLevel->getMainCamera()->OnScreen(p1, PhsxCutoff) && !getCore()->MyLevel->getMainCamera()->OnScreen(p2, PhsxCutoff) )
		{
			getCore()->SkippedPhsx = true;
			getCore()->WakeUpRequirements = true;
			return;
		}
		getCore()->SkippedPhsx = false;

		float Step = CoreMath::Modulo( getCore()->MyLevel->GetIndependentPhsxStep() + Offset, static_cast<float>(Period) );
		float t = static_cast<float>( Step ) / static_cast<float>( Period );

		Vector2 v = GetPos( t );

		getCore()->Data.Position = v;
		//CoreMath.PointxAxisToAngle(ref MyObject.Base, Core.MyLevel.CurPhsxStep / 20f);

		Radius = getInfo()->SpikeyLines->Radius;

		ActivePhsxStep();
	}

	void SpikeyLine::DrawGraphics()
	{
		if ( getCore()->SkippedPhsx )
			return;

		if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer )
		{
			if ( getCore()->MyLevel->getMainCamera()->OnScreen(getCore()->Data.Position, 200) )
				OffScreen = false;
			else
			{
				OffScreen = true;
				return;
			}
		}
		else
			if ( OffScreen )
				return;

		if ( getInfo()->SpikeyLines->Rotate )
			Head->PointxAxisTo( getInfo()->SpikeyLines->RotateOffset + getInfo()->SpikeyLines->RotateSpeed * getMyLevel()->IndependentPhsxStep );
		else
			Head->PointxAxisTo( getInfo()->SpikeyLines->RotateOffset );

		Head->setPos( getPos() );
		Head->Draw();
	}

	void SpikeyLine::Move( Vector2 shift )
	{
		p1 += shift;
		p2 += shift;

		_CircleDeath::Move( shift );
	}

	Microsoft::Xna::Framework::Vector2 SpikeyLine::TR_Bound()
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

	Microsoft::Xna::Framework::Vector2 SpikeyLine::BL_Bound()
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

	void SpikeyLine::MoveToBounded( Vector2 shift )
	{
		Move( shift );
	}

	void SpikeyLine::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<SpikeyLine> FloaterA = dynamic_cast<SpikeyLine*>( A );
		Init( FloaterA->getPos(), FloaterA->getMyLevel() );

		Period = FloaterA->Period;
		Offset = FloaterA->Offset;
		p1 = FloaterA->p1;
		p2 = FloaterA->p2;

		getCore()->WakeUpRequirements = true;
	}

	void SpikeyLine::InitializeInstanceFields()
	{
		OffScreen = false;
	}
}
