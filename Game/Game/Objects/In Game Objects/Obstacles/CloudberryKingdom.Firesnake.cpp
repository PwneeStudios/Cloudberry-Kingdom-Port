#include <global_header.h>

namespace CloudberryKingdom
{

	void Firesnake::FiresnakeTileInfo::InitializeInstanceFields()
	{
		Sprite = std::make_shared<SpriteInfo>( TextureOrAnim::Get( _T( "EmitterTexture" ) ), Vector2( 320.f ), Vector2(), Color::White );
	}

	void Firesnake::MakeNew()
	{
		_CircleDeath::MakeNew();

		AutoGenSingleton = Firesnake_AutoGen::getInstance();
		getCore()->MyType = ObjectType_FIRESNAKE;
		DeathType = BobDeathType_FIRESNAKE;

		PhsxCutoff_Playing = Vector2( 400 );
		PhsxCutoff_BoxesOnly = Vector2( -100, 400 );

		Size = Vector2( 140 );

		getCore()->Init();
		getCore()->MyType = ObjectType_FIRESNAKE;
		getCore()->DrawLayer = 7;

		Orbit = Vector2();
	}

	void Firesnake::Init( Vector2 pos, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<FiresnakeTileInfo> info = level->getInfo()->Firesnakes;

		Size = info->Sprite->Size * level->getInfo()->ScaleAll * level->getInfo()->ScaleAllObjects;

		if ( !level->BoxesOnly )
		{
			MyQuad->Set( info->Sprite );
		}

		_CircleDeath::Init( pos, level );
	}

	Firesnake::Firesnake( bool BoxesOnly ) :
		Period( 0 ),
		Offset( 0 )
	{
		if ( !BoxesOnly )
		{
			MyQuad = std::make_shared<QuadClass>();
		}

		Construct( BoxesOnly );
	}

	void Firesnake::PhsxStep()
	{
		double t = 2 * M_PI * ( getCore()->GetIndependentPhsxStep() + Offset ) / static_cast<float>(Period);
		setPos( CoreMath::AngleToDir( t ) * Radii + Orbit );

		_CircleDeath::PhsxStep();
	}

	void Firesnake::DrawGraphics()
	{
		//// Chains
		//Tools.QDrawer.DrawLine(Orbit, Core.Data.Position,
		//            new Color(255, 255, 255, 215),
		//            Info.Orbs.ChainWidth,
		//            Info.Orbs.ChainSprite.MyTexture, Tools.BasicEffect, Info.Orbs.ChainRepeatWidth, 0, 0f);

		// Draw the Firesnake
		MyQuad->setPos( getPos() );
		MyQuad->Draw();
	}

	void Firesnake::Move( Vector2 shift )
	{
		_CircleDeath::Move( shift );

		Orbit += shift;
	}

	void Firesnake::Reset( bool BoxesOnly )
	{
		getCore()->Active = true;
	}

	void Firesnake::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<Firesnake> FiresnakeA = std::dynamic_pointer_cast<Firesnake>( A );
		Init( A->getPos(), A->getMyLevel() );

		Size = FiresnakeA->Size;

		Period = FiresnakeA->Period;
		Offset = FiresnakeA->Offset;
		Radii = FiresnakeA->Radii;
		Orbit = FiresnakeA->Orbit;
	}
}
