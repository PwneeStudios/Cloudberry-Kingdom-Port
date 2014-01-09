#include <small_header.h>
#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Firesnake.h"

#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_CircleDeath.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Obstacles/Firesnake__Auto.h"
#include "Game/Tilesets/SpriteInfo.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tilesets/TileSetInfo.h"

#include "Core/Texture/TextureOrAnim.h"

namespace CloudberryKingdom
{

	void Firesnake::FiresnakeTileInfo::InitializeInstanceFields()
	{
		Sprite = boost::make_shared<SpriteInfo>( TextureOrAnim::Get( std::wstring( L"EmitterTexture" ) ), Vector2( 320.f ), Vector2(), Color::White );
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

	void Firesnake::Init( Vector2 pos, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<FiresnakeTileInfo> info = level->getInfo()->Firesnakes;

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
			MyQuad = boost::make_shared<QuadClass>();
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
		//Tools::QDrawer.DrawLine(Orbit, Core.Data.Position,
		//            new Color(255, 255, 255, 215),
		//            Info.Orbs.ChainWidth,
		//            Info.Orbs.ChainSprite.MyTexture, Tools::BasicEffect, Info.Orbs.ChainRepeatWidth, 0, 0f);

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

	void Firesnake::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<Firesnake> FiresnakeA = boost::dynamic_pointer_cast<Firesnake>( A );
		Init( A->getPos(), A->getMyLevel() );

		Size = FiresnakeA->Size;

		Period = FiresnakeA->Period;
		Offset = FiresnakeA->Offset;
		Radii = FiresnakeA->Radii;
		Orbit = FiresnakeA->Orbit;
	}
}
