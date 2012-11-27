#include <global_header.h>
namespace CloudberryKingdom
{

	void Cloud::CloudTileInfo::InitializeInstanceFields()
	{
		Sprite = std::make_shared<SpriteInfo>( Tools::Texture( _T( "Cloud1" ) ), Vector2( 250, 180 ), Vector2( 0, -50 ), Color( 1, 1, 1,.95f ) );
		BoxSize = Vector2( 180, 50 );
	}

	Cloud::Cloud()
	{
		InitializeInstanceFields();
	}

	Cloud::Cloud( bool BoxesOnly )
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

	void Cloud::Init( Vector2 pos, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<CloudTileInfo> info = level->getInfo()->Clouds;

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
		Box = std::make_shared<AABox>();

		if ( !BoxesOnly )
			MyQuad = std::make_shared<QuadClass>();

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

	void Cloud::Interact( const std::shared_ptr<Bob> &bob )
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
					for ( std::vector<ObjectBase*>::const_iterator cloud = getCore()->MyLevel->Objects.begin(); cloud != getCore()->MyLevel->Objects.end(); ++cloud )
					{
//C# TO C++ CONVERTER NOTE: The variable Cloud was renamed since it is named the same as a user-defined type:
						std::shared_ptr<Cloud> Cloud_Renamed = dynamic_cast<Cloud*>( *cloud );
						if ( 0 != Cloud_Renamed )
							if ( !Cloud_Renamed->getCore()->GenData.Used && (Cloud_Renamed->getCore()->Data.Position - getCore()->Data.Position)->Length() < 2.35f * Box->Current->Size.X )
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
						bob->MyPhsx->LandOnSomething( false, this );
					else
						bob->MyPhsx->HitHeadOnSomething( this );

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

	void Cloud::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<Cloud> CloudA = dynamic_cast<Cloud*>( A );

		Shiftiness = CloudA->Shiftiness;
		Size = CloudA->Size;
		Init( CloudA->getPos(), CloudA->getMyLevel() );

		Displacement = CloudA->Displacement;

		getCore()->WakeUpRequirements = true;
	}

	void Cloud::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		getCore()->Write(writer);

		MyQuad->Write( writer );

		Box->Write( writer );
	}

	void Cloud::Read( const std::shared_ptr<BinaryReader> &reader )
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
