#include "FallingBlock.h"
#include "Game/Tilesets/BlockGroup.h"
#include "Game/Tools/Recycler.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlockDraw.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Tools/Tools.h"
#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
#include "Game/Objects/ObjectBase.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	FallingBlock::FallingBlockTileInfo::FallingBlockTileInfo()
	{
		InitializeInstanceFields();
	}

	void FallingBlock::FallingBlockTileInfo::InitializeInstanceFields()
	{
		Group = PieceQuad::FallGroup;
	}

int FallingBlock::ResetTimerLength = 12;

	void FallingBlock::MakeNew()
	{
		Thwomp = false;

		EmittedExplosion = HitGround = false;

		getCore()->Init();
		getCore()->DrawLayer = 3;
		getBlockCore()->MyType = ObjectType_FALLING_BLOCK;

		SetState( FallingBlockState_REGULAR );
	}

	void FallingBlock::SetState( FallingBlockState NewState )
	{
		SetState( NewState, false );
	}

	void FallingBlock::SetState( FallingBlockState NewState, bool ForceSet )
	{
		if ( State != NewState || ForceSet )
		{
			switch ( NewState )
			{
				case FallingBlockState_REGULAR:
					TouchedOnce = HitGround = false;
					if ( !getCore()->BoxesOnly )
						MyDraw->MyPieces->CalcTexture( 0, 0 );
					break;
				case FallingBlockState_TOUCHED:
					HitGround = false;
					if ( !getCore()->BoxesOnly )
						MyDraw->MyPieces->CalcTexture( 0, 1 );
					break;
				case FallingBlockState_FALLING:
					if ( !getCore()->BoxesOnly )
						MyDraw->MyPieces->CalcTexture( 0, 2 );
					break;
				case FallingBlockState_ANGRY:
					//if (!Core.BoxesOnly) MyDraw.MyPieces.CalcTexture(0, 3);
					if ( !getCore()->BoxesOnly )
						MyDraw->MyPieces->CalcTexture( 0, 2 );
					break;
			}
		}

		State = NewState;
	}

	FallingBlock::FallingBlock( bool BoxesOnly )
	{
		MyBox = std::make_shared<AABox>();
		MyDraw = std::make_shared<NormalBlockDraw>();

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	void FallingBlock::Init( Vector2 center, Vector2 size, int life, const std::shared_ptr<Level> &level )
	{
		Active = true;

		Life = StartLife = life;

		getBlockCore()->Layer = .35f;

		BlockBase::Init( center, size, level, level->getInfo()->FallingBlocks->Group );

		SetState( FallingBlockState_REGULAR, true );
	}

	void FallingBlock::HitHeadOn( const std::shared_ptr<Bob> &bob )
	{
		/* Use this if you want inverted Bobs to set off falling blocks
		 * 
		// We only care about inverted Bobs landing on us upside down.
		if (bob.MyPhsx.Gravity > 0) return;
	
		// Don't register as a land if the Bob is moving downward.
		if (bob.Core.Data.Velocity.Y < -3)
		{
		    BlockCore.StoodOn = false;
		    return;
		}
	
		if (State == FallingBlockState.Regular)
		    SetState(FallingBlockState.Touched);
	
		if (bob.Core.Data.Velocity.Y > 10)
		    Life -= 8;
		 * */
	}

	void FallingBlock::LandedOn( const std::shared_ptr<Bob> &bob )
	{
		// Don't register as a land if the Bob is moving upward.
		if ( bob->getCore()->Data.Velocity.Y > 3 )
		{
			getBlockCore()->StoodOn = false;
			return;
		}

		if ( State == FallingBlockState_REGULAR )
				SetState( FallingBlockState_TOUCHED );

		if ( bob->getCore()->Data.Velocity.Y < -10 )
			Life -= 8;
	}

	void FallingBlock::Reset( bool BoxesOnly )
	{
		BlockBase::Reset( BoxesOnly );

		Active = true;

		Life = StartLife;
		TouchedOnce = false;
		EmittedExplosion = false;

		ResetTimer = 0;

		SetState( FallingBlockState_REGULAR, true );

		getBlockCore()->Data = getBlockCore()->StartData;

		getBlockCore()->StoodOn = false;

		MyBox->Current->Center = getBlockCore()->StartData.Position;

		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );
		MyBox->SwapToCurrent();
	}

	void FallingBlock::PhsxStep()
	{
		Active = getCore()->Active = true;
		if ( !getCore()->Held )
		{
			if ( MyBox->Current->BL.X > getBlockCore()->MyLevel->getMainCamera()->TR.X || MyBox->Current->BL.Y > getBlockCore()->MyLevel->getMainCamera()->TR.Y )
				Active = getCore()->Active = false;
			if ( MyBox->Current->TR.X < getBlockCore()->MyLevel->getMainCamera()->BL.X || MyBox->Current->TR.Y < getBlockCore()->MyLevel->getMainCamera()->BL.Y - 200 )
				Active = getCore()->Active = false;
		}


		if ( getCore()->MyLevel->GetPhsxStep() % 2 == 0 )
			Offset = Vector2::Zero;

		// Update the block's apparent center according to attached objects
		getBlockCore()->UseCustomCenterAsParent = true;
		getBlockCore()->CustomCenterAsParent = getBox()->Target->Center + Offset;

		if ( getBlockCore()->StoodOn )
		{
			ResetTimer = ResetTimerLength;

			TouchedOnce = true;

			if ( getCore()->MyLevel->GetPhsxStep() % 2 == 0 )
				if ( Life > 0 )
				{
					Offset = Vector2( getMyLevel()->getRnd()->Rnd->Next(-10, 10), getMyLevel()->getRnd()->Rnd->Next(-10, 10) );
				}
		}
		else
		{
			if ( State == FallingBlockState_TOUCHED )
			{
				ResetTimer--;
				if ( ResetTimer <= 0 )
					SetState( FallingBlockState_REGULAR );
			}
		}

		if ( State == FallingBlockState_ANGRY )
		{
			getBlockCore()->Data.Velocity.Y += AngryAccel.Y;
			if ( getBlockCore()->Data.Velocity.Y > AngryMaxSpeed )
				getBlockCore()->Data.Velocity.Y = AngryMaxSpeed;
			MyBox->Current->Center.Y += getBlockCore()->Data.Velocity.Y;
		}
		else
		{
			if ( getBlockCore()->StoodOn || Life < StartLife / 3 )
				Life--;
			if ( Life <= 0 )
			{
				if ( State != FallingBlockState_FALLING )
				{
					if ( Thwomp )
						SetState( FallingBlockState_ANGRY );
					else
						SetState( FallingBlockState_FALLING );
				}
				getBlockCore()->Data.Velocity.Y -= 1;
				if ( getBlockCore()->Data.Velocity.Y < -20 )
					getBlockCore()->Data.Velocity.Y = -20;
				MyBox->Current->Center.Y += getBlockCore()->Data.Velocity.Y;
			}

			// Check for hitting bottom of screen
			if ( State == FallingBlockState_FALLING && ( getCore()->MyLevel->Geometry != LevelGeometry_UP && getCore()->MyLevel->Geometry != LevelGeometry_DOWN ) )
			{
				if ( MyBox->Current->Center.Y < getBlockCore()->MyLevel->getMainCamera()->BL.Y - 200 )
				{
					// Emit a dust plume if the game is in draw mode and there isn't any lava
					if ( getCore()->MyLevel->PlayMode == 0 && !EmittedExplosion && !Tools::CurGameData->HasLava )
					{
						EmittedExplosion = true;
						ParticleEffects::DustCloudExplosion( getCore()->MyLevel, MyBox->Current->Center );
					}
				}
				if ( MyBox->Current->Center.Y < getBlockCore()->MyLevel->getMainCamera()->BL.Y - 500 )
					Active = false;
			}
		}

		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );

		getBlockCore()->StoodOn = false;
	}

	void FallingBlock::Extend( Side side, float pos )
	{
		switch ( side )
		{
			case Side_LEFT:
				MyBox->Target->BL.X = pos;
				break;
			case Side_RIGHT:
				MyBox->Target->TR.X = pos;
				break;
			case Side_TOP:
				MyBox->Target->TR.Y = pos;
				break;
			case Side_BOTTOM:
				MyBox->Target->BL.Y = pos;
				break;
		}

		MyBox->Target->FromBounds();
		MyBox->SwapToCurrent();

		getBlockCore()->StartData.Position = MyBox->Current->Center;
	}

	void FallingBlock::Move( Vector2 shift )
	{
		getBlockCore()->Data.Position += shift;
		getBlockCore()->StartData.Position += shift;

		getBox()->Move(shift);
	}

	void FallingBlock::Draw()
	{
		bool DrawSelf = true;
		if ( !getCore()->Held )
		{
			if ( !Active )
				DrawSelf = false;

			if ( !getCore()->MyLevel->getMainCamera()->OnScreen(MyBox->Current->Center, 600) )
				DrawSelf = false;
		}

		if ( DrawSelf )
		{
			if ( Tools::DrawBoxes )
			{
				MyBox->DrawFilled( Tools::QDrawer, Color::Red );
			}
		}

		if ( Tools::DrawGraphics )
		{
			if ( DrawSelf && !getBlockCore()->BoxesOnly )
			if ( !getBlockCore()->BoxesOnly )
			{
				MyDraw->Update();
				MyDraw->MyPieces->Base.Origin += Offset;

				MyDraw->Draw();
			}
		}

		getBlockCore()->Draw();
	}

	void FallingBlock::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<FallingBlock> BlockA = dynamic_cast<FallingBlock*>( A );

		Init( BlockA->getBox()->Current->Center, BlockA->getBox()->Current->Size, BlockA->StartLife, BlockA->getMyLevel() );

		TouchedOnce = BlockA->TouchedOnce;
		StartLife = BlockA->StartLife;
		Life = BlockA->Life;

		EmittedExplosion = BlockA->EmittedExplosion;

		Thwomp = BlockA->Thwomp;
	}
}
