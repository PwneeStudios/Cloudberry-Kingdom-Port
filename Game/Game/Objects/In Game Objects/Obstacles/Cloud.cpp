#include <small_header.h>
#include "Game/Objects/In Game Objects/Obstacles/Cloud.h"

#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Collision Detection/Phsx.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_Obstacle.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Tilesets/SpriteInfo.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
#include "Game/Tilesets/TileSetInfo.h"

#include "Core/Texture/TextureOrAnim.h"
#include "Core/Tools/Random.h"
#include "Game/Collision Detection/FloatRectangle.h"
#include "Game/Player/Hero Physics/Base.h"

namespace CloudberryKingdom
{

	void Cloud::CloudTileInfo::InitializeInstanceFields()
	{
		Sprite = boost::make_shared<SpriteInfo>( TextureOrAnim::Get( Tools::Texture( std::wstring( L"Cloud1" ) ) ), Vector2( 250.f, 180.f ), Vector2( 0.f, -50.f ), Color( 1.f, 1.f, 1.f, .95f ) );
		BoxSize = Vector2( 180, 50 );
	}

	Cloud::Cloud() :
		Shiftiness( 0 ),
		PeriodOffset( 0 )
	{
		InitializeInstanceFields();
	}

	Cloud::Cloud( bool BoxesOnly ) :
		Shiftiness( 0 ),
		PeriodOffset( 0 )
	{
		InitializeInstanceFields();
		Construct( BoxesOnly );
	}

	void Cloud::MakeNew()
	{
		_Obstacle::MakeNew();

		PhsxCutoff_Playing = Vector2( 1000 );
		PhsxCutoff_BoxesOnly = Vector2( -100 );

		getCore()->Init();
		getCore()->DrawLayer = 9;
		getCore()->MyType = ObjectType_CLOUD;
		getCore()->Holdable = true;

		getCore()->EditHoldable = true;

		Displacement = Vector2();

		getCore()->WakeUpRequirements = true;
	}

	void Cloud::Init( Vector2 pos, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<CloudTileInfo> info = level->getInfo()->Clouds;

		_Obstacle::Init( pos, level );

		PeriodOffset = level->getRnd()->RndInt(0, 1000);

		getCore()->setMyTileSet(level->MyTileSet);

		Size = level->getInfo()->Clouds->BoxSize;
		Box->Initialize( getPos(), Size );

		if ( !level->BoxesOnly )
		{
			MyQuad->Set( info->Sprite );
		}
	}

	void Cloud::Construct( bool BoxesOnly )
	{
		Box = boost::make_shared<AABox>();

		if ( !BoxesOnly )
			MyQuad = boost::make_shared<QuadClass>();

		getCore()->BoxesOnly = BoxesOnly;

		MakeNew();
	}

	void Cloud::ActivePhsxStep()
	{
		int CurPhsxStep = getCore()->GetPhsxStep();

		Displacement *= .9f;

		float L = Displacement.Length();
		if ( L > 1 )
		{
			Displacement -= Displacement / L;
		}
		else
			Displacement *= .9f;

		Box->Current->Center = getPos();
		Box->SetTarget( Box->Current->Center + Displacement, Box->Current->Size );

		if ( getCore()->WakeUpRequirements )
		{
			Box->SwapToCurrent();
			getCore()->WakeUpRequirements = false;
		}
	}

	void Cloud::PhsxStep2()
	{
		if ( !getCore()->Active )
			return;
		if ( getCore()->SkippedPhsx )
			return;

		Box->SwapToCurrent();
	}

	void Cloud::DrawGraphics()
	{
		double t = 2 * M_PI * ( getCore()->GetPhsxStep() + PeriodOffset ) / static_cast<float>(220);
		Vector2 dis = Vector2( 0, static_cast<float>( cos( t ) ) ) * 10;

		MyQuad->setPos( getPos() + Displacement + dis );
		MyQuad->Draw();
	}

	void Cloud::DrawBoxes()
	{
		Box->Draw( Color::Azure, 10 );
		//Box.DrawT(Color.Blue, 10);
	}

	void Cloud::Move( Vector2 shift )
	{
		_Obstacle::Move( shift );

		Box->Move( shift );
	}

	void Cloud::Interact( const boost::shared_ptr<Bob> &bob )
	{
		if ( !getCore()->Active )
			return;

		bool Overlap = false;
		if ( !getCore()->SkippedPhsx )
		{
			Overlap = Phsx::BoxBoxOverlap( bob->Box, Box );

			if ( Overlap && getCore()->MyLevel->PlayMode == 2 )
			{
				Overlap = Phsx::BoxBoxOverlap( bob->Box, Box );

				bool Delete = false;

				if ( bob->WantsToLand == false )
					Delete = true;
				if ( bob->MyPhsx->DynamicGreaterThan( bob->getCore()->Data.Velocity.Y, 10 ) )
					Delete = true;
				if ( getCore()->GenData.Used )
					Delete = false;
				if ( Delete )
				{
					CollectSelf();

					getCore()->Active = false;
					return;
				}
				else
				{
					StampAsUsed( getCore()->MyLevel->CurPhsxStep );

					// Remove surrounding clouds
					for ( ObjectVec::const_iterator cloud = getCore()->MyLevel->Objects.begin(); cloud != getCore()->MyLevel->Objects.end(); ++cloud )
					{
						boost::shared_ptr<Cloud> Cloud_Renamed = boost::dynamic_pointer_cast<Cloud>( *cloud );
						if ( 0 != Cloud_Renamed )
							if ( !Cloud_Renamed->getCore()->GenData.Used && (Cloud_Renamed->getCore()->Data.Position - getCore()->Data.Position).Length() < 2.35f * Box->Current->Size.X )
							{
								getCore()->getRecycle()->CollectObject(Cloud_Renamed);
								( *cloud )->getCore()->Active = false;
							}
					}
				}
			}

			if ( Overlap )
			{
				if ( bob->MyPhsx->Gravity > 0 && bob->Box->BL.Y < Box->TR.Y - 75 || bob->MyPhsx->Gravity < 0 && bob->Box->TR.Y > Box->BL.Y + 75 )
				{
					//if (bob.Core.Data.Velocity.Y < -3.5f)
					if ( bob->MyPhsx->DynamicLessThan( bob->getCore()->Data.Velocity.Y, -3.5f ) )
						bob->getCore()->Data.Velocity.Y *= .9f;
				}

				//if (bob.Core.Data.Velocity.Y <= 0)
				//if (bob.Core.Data.Velocity.Y >= 0)
				if ( bob->MyPhsx->DynamicLessThan( bob->getCore()->Data.Velocity.Y, 0 ) )
				{
					if ( bob->MyPhsx->Gravity > 0 )
						bob->MyPhsx->LandOnSomething( false, shared_from_this() );
					else
						bob->MyPhsx->HitHeadOnSomething( shared_from_this() );

					Displacement += Shiftiness * bob->getCore()->Data.Velocity / 2;
				}
			}
		}
	}

	void Cloud::Reset( bool BoxesOnly )
	{
		_Obstacle::Reset( BoxesOnly );

		getCore()->WakeUpRequirements = true;
	}

	void Cloud::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<Cloud> CloudA = boost::dynamic_pointer_cast<Cloud>( A );

		Shiftiness = CloudA->Shiftiness;
		Size = CloudA->Size;
		Init( CloudA->getPos(), CloudA->getMyLevel() );

		Displacement = CloudA->Displacement;

		getCore()->WakeUpRequirements = true;
	}

	void Cloud::Write( const boost::shared_ptr<BinaryWriter> &writer )
	{
		getCore()->Write(writer);

		MyQuad->Write( writer );

		Box->Write( writer );
	}

	void Cloud::Read( const boost::shared_ptr<BinaryReader> &reader )
	{
		getCore()->Read(reader);

		MyQuad->Read( reader );

		Box->Read( reader );
		this->Size = Box->Current->Size;
	}

	void Cloud::InitializeInstanceFields()
	{
		PeriodOffset = 0;
	}
}
