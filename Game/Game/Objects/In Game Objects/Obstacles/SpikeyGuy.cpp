#include <global_header.h>

namespace CloudberryKingdom
{

	void SpikeyGuy::SpikeyGuyTileInfo::InitializeInstanceFields()
	{
		Ball = boost::make_shared<SpriteInfo>( TextureOrAnim::Get( _T( "EmitterTexture" ) ), Vector2( 320.f ), Vector2(), Color::White );
		Base = boost::make_shared<SpriteInfo>( TextureOrAnim::Get( _T( "Joint" ) ), Vector2( 50.f, -1.f ), Vector2(), Color::White );
		Chain = boost::make_shared<LineSpriteInfo>( TextureOrAnim::Get( _T( "Chain_Tile" ) ), 44.f, 63.f );
		Radius = 200;
		Rotate = false;
		RotateOffset = 0;
		RotateSpeed = 0;
	}

	void SpikeyGuy::OnAttachedToBlock()
	{
		_CircleDeath::OnAttachedToBlock();

		if ( boost::dynamic_pointer_cast<NormalBlock>( getCore()->ParentBlock ) != 0 )
			return;
		else
		{
			getCore()->DrawLayer = getCore()->ParentBlock->getCore()->DrawLayer;
			getCore()->DrawLayer2 = getCore()->ParentBlock->getCore()->DrawLayer + 1;
			getCore()->DrawLayer3 = getCore()->ParentBlock->getCore()->DrawLayer + 2;
		}
	}

	void SpikeyGuy::MakeNew()
	{
		_CircleDeath::MakeNew();

		AutoGenSingleton = SpikeyGuy_AutoGen::getInstance();
		getCore()->MyType = ObjectType_SPIKEY_GUY;
		DeathType = BobDeathType_SPIKEY_GUY;

		getCore()->ContinuousEnabled = true;

		Angle = 0;
		Dir = 1;
		Period = 150;
		Offset = 0;
		PivotPoint = Vector2();

		getCore()->DrawLayer = 4;
		getCore()->DrawLayer2 = 5;
		getCore()->DrawLayer3 = 6;
	}

	void SpikeyGuy::Init( Vector2 pos, const boost::shared_ptr<Level> &level )
	{
		_CircleDeath::Init( pos, level );

		PivotPoint = pos;

		if ( !getCore()->BoxesOnly )
		{
			Head->Set( level->getInfo()->SpikeyGuys->Ball );
			Anchor->Set( level->getInfo()->SpikeyGuys->Base );
		}
	}

	SpikeyGuy::SpikeyGuy( bool BoxesOnly ) :
		Angle( 0 ),
		MaxAngle( 0 ),
		Length( 0 ),
		Period( 0 ),
		Offset( 0 ),
		Dir( 0 ),
		CorrespondingAngle( 0 ),
		OffScreen( 0 )
	{
		InitializeInstanceFields();
		_CircleDeath::Construct( BoxesOnly );

		if ( !getCore()->BoxesOnly )
		{
			Anchor = boost::make_shared<QuadClass>();
			Head = boost::make_shared<QuadClass>();
		}
	}

	float SpikeyGuy::MinY()
	{
		return PivotPoint.Y - Length;
	}

	Vector2 SpikeyGuy::GetPos( float t )
	{
		CorrespondingAngle = static_cast<float>( 2 * M_PI * t );
		Vector2 Dir = CoreMath::AngleToDir( CorrespondingAngle );
		Vector2 Pos = PivotPoint + Length * Dir;

		return Pos;
	}

	void SpikeyGuy::PhsxStep()
	{
		if ( getCore()->ParentBlock != 0 )
			PivotPoint = getCore()->GetPosFromParentOffset();

		float PhsxCutoff = Length + 1800;
		if ( getCore()->MyLevel->BoxesOnly )
			PhsxCutoff = Length + 100;

		if ( !getCore()->MyLevel->getMainCamera()->OnScreen(PivotPoint, PhsxCutoff) )
		{
			getCore()->SkippedPhsx = true;
			getCore()->WakeUpRequirements = true;
			return;
		}
		getCore()->SkippedPhsx = false;

		float Step = CoreMath::Modulo( getCore()->MyLevel->GetIndependentPhsxStep() + Offset, static_cast<float>( Period ) );
		float t = Dir * static_cast<float>( Step ) / static_cast<float>( Period );

		setPos( GetPos( t ) );
		Angle = CorrespondingAngle;

		Radius = getInfo()->SpikeyGuys->Radius;

		ActivePhsxStep();
	}

	void SpikeyGuy::DrawGraphics()
	{
		if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer )
		{
			if ( getCore()->MyLevel->getMainCamera()->OnScreen(PivotPoint, Length + getInfo()->SpikeyGuys->Radius + 600) )
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

		if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer )
		{
			Anchor->setPos( PivotPoint );
			Anchor->Draw();
		}
		else if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer2 )
		{
			Tools::QDrawer->DrawLine( PivotPoint, getPos(), getInfo()->SpikeyGuys->Chain );
		}
		else if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer3 )
		{
			if ( getInfo()->SpikeyGuys->Rotate )
				Head->PointxAxisTo( CorrespondingAngle + getInfo()->SpikeyGuys->RotateOffset + getInfo()->SpikeyGuys->RotateSpeed * getMyLevel()->IndependentPhsxStep );
			else
				Head->PointxAxisTo( getInfo()->SpikeyGuys->RotateOffset );

			Head->setPos( getPos() );
			Head->Draw();
		}
	}

	void SpikeyGuy::DrawBoxes()
	{
		if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer )
		{
		}
		else if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer2 )
		{
			Tools::QDrawer->DrawLine( PivotPoint, getCore()->Data.Position, bColor(255, 255, 255, 215), 20 );
		}
		else if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer3 )
		{
			Circle->Draw( bColor( 50, 50, 255, 220 ) );
		}
	}

	void SpikeyGuy::Move( Vector2 shift )
	{
		PivotPoint += shift;

		_CircleDeath::Move( shift );
	}

	void SpikeyGuy::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<SpikeyGuy> FloaterA = boost::dynamic_pointer_cast<SpikeyGuy>( A );
		Init( FloaterA->getPos(), FloaterA->getMyLevel() );

		Angle = FloaterA->Angle;
		Dir = FloaterA->Dir;
		Period = FloaterA->Period;
		Offset = FloaterA->Offset;
		PivotPoint = FloaterA->PivotPoint;
		Length = FloaterA->Length;

		getCore()->WakeUpRequirements = true;
	}

	void SpikeyGuy::InitializeInstanceFields()
	{
		OffScreen = false;
	}
}
