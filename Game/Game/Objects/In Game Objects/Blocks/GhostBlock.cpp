#include <small_header.h>
#include "Game/Objects/In Game Objects/Blocks/GhostBlock.h"

#include "Core/Graphics/Draw/Simple/SimpleObject.h"
#include "Core/Texture/TextureOrAnim.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Collision Detection/Phsx.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Tilesets/BlockGroup.h"
#include "Game/Tools/Prototypes.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
#include "Game/Tilesets/TileSetInfo.h"

#include "Core/Texture/EzTextureWad.h"
#include "Game/Collision Detection/FloatRectangle.h"

#include "Game/Tools/Camera.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlockDraw.h"

namespace CloudberryKingdom
{

	void GhostBlock::GhostBlockTileInfo::InitializeInstanceFields()
	{
		Group = 0;
		Sprite = Tools::TextureWad->FindTextureOrAnim( std::wstring( L"fading block" ) );
		Shift = Vector2();
	}

	void GhostBlock::MakeNew()
	{
		TallBox = false;
		TallInvertBox = false;

		MyAnimSpeed = .1666f;

		MyBox->TopOnly = true;

		getCore()->Init();
		getCore()->DrawLayer = 3;
		getBlockCore()->MyType = ObjectType_GHOST_BLOCK;

		SetState( GhostBlockState_PHASED_IN );

		SetAnimation();

		MyObject->Boxes[ 0 ]->Animated = false;
	}

	void GhostBlock::SetState( GhostBlockState NewState )
	{
		SetState( NewState, false );
	}

	void GhostBlock::SetState( GhostBlockState NewState, bool ForceSet )
	{
		if ( State != NewState || ForceSet )
		{
			switch ( NewState )
			{
				case GhostBlockState_PHASED_IN:
					break;
				case GhostBlockState_PHASED_OUT:
					break;
			}
		}

		State = NewState;
	}

	void GhostBlock::SetAnimation()
	{
		MyObject->Read( 0, 0 );
		MyObject->Play = true;
		MyObject->Loop = true;
		//MyObject.EnqueueAnimation(0, (float)MyLevel.Rnd.Rnd.NextDouble() * 1.5f, true);
		MyObject->EnqueueAnimation( 0, static_cast<float>( 0 ), true );
		MyObject->DequeueTransfers();
		MyObject->Update();
	}

	GhostBlock::GhostBlock( bool BoxesOnly )
	{
		MyObject = boost::make_shared<SimpleObject>( Prototypes::GhostBlockObj, BoxesOnly );

		MyObject->Boxes[ 0 ]->Animated = false;

		MyBox = boost::make_shared<AABox>();

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

float GhostBlock::TallScale = 1.45f;
float TallInvertScale = 1.635f;

	void GhostBlock::Init( Vector2 center, Vector2 size, const boost::shared_ptr<Level> &level )
	{
		Active = true;

		getBlockCore()->Layer = .35f;
		getCore()->DrawLayer = 7;

		if ( TallBox )
			size.Y *= TallScale;
        else if ( TallInvertBox )
            size.Y *= TallInvertScale;

		// Use PieceQuad group if it exists.
		if ( level->getInfo()->GhostBlocks->Group != 0 )
			BlockBase::Init( center, size, level, level->getInfo()->GhostBlocks->Group );
		// Otherwise use old SimpleObject
		else
		{
			getCore()->StartData.Position = getCore()->Data.Position = center;

			MyBox->Initialize( center, size );
		}

		MyBox->TopOnly = true;

		SetState( GhostBlockState_PHASED_IN, true );

		Update();
	}

	void GhostBlock::Reset( bool BoxesOnly )
	{
		getBlockCore()->BoxesOnly = BoxesOnly;

		Active = true;

		// Sub in image
		if ( !BoxesOnly )
			MyObject->Quads[ 0 ].Set( getInfo()->GhostBlocks->Sprite );

		SetState( GhostBlockState_PHASED_IN, true );

		getBlockCore()->Data = getBlockCore()->StartData;

		MyBox->Current->Center = getBlockCore()->StartData.Position;

		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );
		MyBox->SwapToCurrent();

		Update();
	}

	void GhostBlock::AnimStep()
	{
		if ( MyObject->DestinationAnim() == 0 && MyObject->Loop )
			MyObject->PlayUpdate( MyAnimSpeed * getCore()->getIndependentDeltaT() );
	}

	const int GhostBlock::getPeriod() const
	{
		return InLength + OutLength;
	}

	float GhostBlock::GetStep()
	{
		//return CoreMath::Modulo(Core.MyLevel.GetPhsxStep() + Offset, Period);
		return CoreMath::Modulo( getCore()->MyLevel->GetIndependentPhsxStep() + Offset, static_cast<float>(getPeriod()) );
	}

	void GhostBlock::ModOffset( int DesiredStep )
	{
		//int CurPhsxStep = Core.MyLevel.GetPhsxStep();
		int CurPhsxStep = static_cast<int>( getCore()->MyLevel->GetIndependentPhsxStep() + .49f );

		// Make sure the desired step is positive
		DesiredStep = ( DesiredStep + getPeriod() ) % getPeriod();

		// Calculate the new offset
		Offset = DesiredStep - CurPhsxStep % getPeriod();

		// Make sure the offset is positive
		Offset = ( Offset + getPeriod() ) % getPeriod();
	}

int GhostBlock::LengthOfPhaseChange = 35;

	void GhostBlock::PhsxStep()
	{
		Active = getCore()->Active = true;
		if ( !getCore()->Held )
		{
			if ( MyBox->Current->BL.X > getBlockCore()->MyLevel->getMainCamera()->TR.X + 40 || MyBox->Current->BL.Y > getBlockCore()->MyLevel->getMainCamera()->TR.Y + 200 )
				Active = getCore()->Active = false;
			if ( MyBox->Current->TR.X < getBlockCore()->MyLevel->getMainCamera()->BL.X - 40 || MyBox->Current->TR.Y < getBlockCore()->MyLevel->getMainCamera()->BL.Y - 200 )
				Active = getCore()->Active = false;
		}

		if ( !getCore()->BoxesOnly && Active && getCore()->Active )
			AnimStep();

		getCore()->GenData.JumpNow = getCore()->GenData.TemporaryNoLandZone = false;

		float Step = GetStep();
		if ( Step < InLength )
		{
			getCore()->Active = true;
			State = GhostBlockState_PHASED_IN;

			// As Step approaches InLength the StateChange approaches 0 (faded out)
			StateChange = ( InLength - Step ) / static_cast<float>( LengthOfPhaseChange );
			if ( StateChange < .25f )
				getCore()->Active = false;

			// If we're about to fade out don't allow computer to land on this ghost
			// and jump if the computer is already on it
			if ( StateChange < .25f + TimeSafety )
				getCore()->GenData.JumpNow = true;
			if ( StateChange < .25f + .65f )
				getCore()->GenData.JumpNow = true;
		}
		else
		{
			getCore()->Active = false;
			State = GhostBlockState_PHASED_OUT;

			// As Step approaches InLength + OutLength (the total period),
			// the StateChange approaches 0 (faded out)
			StateChange = ( InLength + OutLength - Step ) / static_cast<float>( LengthOfPhaseChange );
			if ( StateChange < .75f )
				getCore()->Active = true;
		}

		// Make sure StateChange lies between 0 and 1
		StateChange = __min( 1, StateChange );

		// If this is Stage 1 of the level gen and this ghost hasn't been uset yet,
		// then set it to be always active.
		// We can adjust its Offset once it is used.
		if ( getCore()->MyLevel->PlayMode == 2 && getCore()->GenData.Used == false )
			getCore()->Active = true;

		Update();

		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );

		getBlockCore()->StoodOn = false;
	}

	void GhostBlock::PhsxStep2()
	{
		if ( !Active )
			return;

		MyBox->SwapToCurrent();
	}

	void GhostBlock::Update()
	{
		if ( getBlockCore()->BoxesOnly )
			return;

		if ( TallBox )
			MyObject->Base.Origin -= MyObject->Boxes[ 0 ]->Center() - MyBox->Current->Center - Vector2(0, MyBox->Current->Size.Y * (TallScale - 1) / 2);
        else if ( TallInvertBox )
            MyObject->Base.Origin -= MyObject->Boxes[ 0 ]->Center() - MyBox->Current->Center - Vector2(0, MyBox->Current->Size.Y * (TallInvertScale - 1) / 2);
		else
			MyObject->Base.Origin -= MyObject->Boxes[ 0 ]->Center() - MyBox->Current->Center;
		
		if ( getInfo() != 0 )
			MyObject->Base.Origin += getInfo()->GhostBlocks->Shift;

		MyObject->Base.e1.X = 1;
		MyObject->Base.e2.Y = 1;
		MyObject->Update();

		Vector2 CurSize = MyObject->Boxes[ 0 ]->Size() / 2;
		Vector2 Scale = MyBox->Current->Size / CurSize;

		if ( TallBox )
			Scale.Y /= TallScale;
        else if ( TallInvertBox )
            Scale.Y /= TallInvertScale;

		MyObject->Base.e1.X = Scale.X;
		MyObject->Base.e2.Y = Scale.Y;

		MyObject->Update();
	}

	void GhostBlock::Extend( Side side, float pos )
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

		Update();

		getBlockCore()->StartData.Position = MyBox->Current->Center;
	}

	void GhostBlock::Move( Vector2 shift )
	{
		getBlockCore()->Data.Position += shift;
		getBlockCore()->StartData.Position += shift;

		getBox()->Move(shift);

		Update();
	}

	void GhostBlock::Draw()
	{
		if ( Active )
		{
			Update();

			if ( Tools::DrawBoxes )
				MyBox->DrawFilled( Tools::QDrawer, Color::Green );
		}

		if ( Tools::DrawGraphics )
		{
			if ( Active && !getBlockCore()->BoxesOnly )
			{
				Vector4 Full, Half;
				Full = Vector4( 1, 1, 1, 1 );
				Half = Vector4( 1, 1, 1, 0.06f );
				Color color;

				if ( State == GhostBlockState_PHASED_IN )
					color = Color( ( 1 - StateChange ) * Half + StateChange * Full );
				else
					color = Color( ( 1 - StateChange ) * Full + StateChange * Half );

				if ( getInfo()->GhostBlocks->Group == 0 )
				{
					MyObject->SetColor( color );
					MyObject->Draw( Tools::QDrawer, Tools::EffectWad );
					//Tools::QDrawer.Flush();
				}
				else
				{
					MyDraw->Update();
					MyDraw->Draw();
				}
			}
		}

		getBlockCore()->Draw();
	}

	void GhostBlock::PostInteractWith( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		BlockBase::PostInteractWith( bob, Col, Overlap );

		boost::shared_ptr<GhostBlock> block = boost::dynamic_pointer_cast<GhostBlock>( shared_from_this() );

		// Ghost blocks delete surrounding blocks when stamped as used
		for ( BlockVec::const_iterator gblock = getCore()->MyLevel->Blocks.begin(); gblock != getCore()->MyLevel->Blocks.end(); ++gblock )
		{
			boost::shared_ptr<GhostBlock> ghost = boost::dynamic_pointer_cast<GhostBlock>( *gblock );
			if ( 0 != ghost && !ghost->getCore()->MarkedForDeletion )
				if ( !ghost->getCore()->GenData.Used && (ghost->getCore()->Data.Position - block->getCore()->Data.Position).Length() < 200 )
				{
					bob->DeleteObj( ghost );
					ghost->setIsActive( false );
				}
		}
	}

	void GhostBlock::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<GhostBlock> BlockA = boost::dynamic_pointer_cast<GhostBlock>( A );

		Init( BlockA->getBox()->Current->Center, BlockA->getBox()->Current->Size, A->getMyLevel() );
		MyBox->TopOnly = BlockA->MyBox->TopOnly;
	}
}
