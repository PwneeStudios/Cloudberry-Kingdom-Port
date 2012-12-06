#include <global_header.h>

namespace CloudberryKingdom
{

	void NormalBlock::BasicConstruction( bool BoxesOnly )
	{
		getCore()->BoxesOnly = BoxesOnly;

		MyBox = std::make_shared<AABox>();
		MyDraw = std::make_shared<NormalBlockDraw>();

		MakeNew();
	}

	void NormalBlock::Release()
	{
		BlockBase::Release();

		if ( MyDraw != 0 )
			MyDraw->Release();
		MyDraw.reset();
	}

	void NormalBlock::MakeNew()
	{
		Active = true;

		Invert = false;

		getBox()->MakeNew();

		if ( MyDraw != 0 )
			MyDraw->MakeNew();

		getBlockCore()->Init();
		getBlockCore()->Layer = .3f;
		getCore()->DrawLayer = 1;
		getCore()->MyType = ObjectType_NORMAL_BLOCK;
		getCore()->EditHoldable = getCore()->Holdable = true;

		Init( Vector2(), Vector2(), TileSets::DefaultTileSet );
	}

	NormalBlock::NormalBlock( bool BoxesOnly )
	{
		InitializeInstanceFields();
		BasicConstruction( BoxesOnly );
	}

	std::shared_ptr<PieceQuad> NormalBlock::GetPieceTemplate()
	{
		if ( getBlockCore()->MyOrientation == PieceQuad::Orientation_ROTATE_RIGHT || getBlockCore()->MyOrientation == PieceQuad::Orientation_ROTATE_LEFT )
			return GetPieceTemplate( getBox()->Current->Size.Y );
		else
			return GetPieceTemplate( getBox()->Current->Size.X );
	}

	std::shared_ptr<PieceQuad> NormalBlock::GetPieceTemplate( float width )
	{
		std::shared_ptr<CloudberryKingdom::TileSet> tileset = getCore()->getMyTileSet();
		if ( tileset->ProvidesTemplates )
		{
			if ( getMyLevel() == 0 )
				return tileset->GetPieceTemplate( std::static_pointer_cast<BlockBase>( shared_from_this() ), 0 );
			else
				return tileset->GetPieceTemplate( std::static_pointer_cast<BlockBase>( shared_from_this() ), getRnd() );
		}

		if ( tileset->PassableSides )
		{
			getBlockCore()->UseTopOnlyTexture = false;
			getBox()->TopOnly = true;
		}

		getBox()->TopOnly = true;
		return 0;
		//return PieceQuad.Catwalk;
	}

	void NormalBlock::ResetPieces()
	{
		if ( MyDraw == 0 )
			return;

		MyDraw->Init( std::static_pointer_cast<BlockBase>( shared_from_this() ), GetPieceTemplate(), Invert );

		MyDraw->MyPieces->Center.Playing = false;
	}

	void NormalBlock::Init( Vector2 center, Vector2 size, const std::shared_ptr<TileSet> &tile )
	{
		getCore()->Data.Position = getCore()->StartData.Position = center;
		getCore()->setMyTileSet(tile);
		Tools::Assert( getCore()->getMyTileSet() != 0 );

		if ( tile->FixedWidths )
		{
			if ( getBlockCore()->Ceiling )
				tile->Ceilings->SnapWidthUp( size );
			else if ( getBox()->TopOnly )
				tile->Platforms->SnapWidthUp( size );
			else if ( getBlockCore()->EndPiece && tile->EndBlock->Dict.size() > 0 )
				tile->EndBlock->SnapWidthUp( size );
			else if ( getBlockCore()->StartPiece && tile->StartBlock->Dict.size() > 0 )
				tile->StartBlock->SnapWidthUp( size );
			else
				tile->Pillars->SnapWidthUp( size );

			//size.Y = 170;
			//Extend(Side.Bottom, Box.TR.Y - 170);
		}

		MyBox->Initialize( center, size );

		if ( !getCore()->BoxesOnly )
			MyDraw->Init( std::static_pointer_cast<BlockBase>( shared_from_this() ), GetPieceTemplate(), Invert );

		Update();

		getBox()->Validate();
	}

float NormalBlock::TopOnlyHeight = 60;

	void NormalBlock::CheckHeight()
	{
		Tools::Assert( getCore()->getMyTileSet() != 0 );

		if ( getBlockCore()->DisableFlexibleHeight || !getCore()->getMyTileSet()->FlexibleHeight )
		{
			if ( MyBox->Current->BL.Y > getCore()->MyLevel->getMainCamera()->BL.Y - 20 )
				MakeTopOnly();
		}
		else
		{
			if ( getBox()->Current->Size.Y < TopOnlyHeight )
				MakeTopOnly();
		}
	}

	void NormalBlock::MakeTopOnly()
	{
		Tools::Assert( getCore()->getMyTileSet() != 0 );

		getBox()->TopOnly = true;
		Extend( Side_BOTTOM, getBox()->Current->TR.Y - TopOnlyHeight );
		Update();
	}

	void NormalBlock::Move( Vector2 shift )
	{
		getBlockCore()->Data.Position += shift;
		getBlockCore()->StartData.Position += shift;

		getBox()->Move(shift);

		Update();
	}

	void NormalBlock::Reset( bool BoxesOnly )
	{
		if ( getCore()->AlwaysBoxesOnly )
			BoxesOnly = true;
		else
			getBlockCore()->BoxesOnly = BoxesOnly;

		if ( !getCore()->BoxesOnly && !getCore()->VisualResettedOnce )
			ResetPieces();

		Active = true;

		getBlockCore()->Data = getBlockCore()->StartData;

		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );
		MyBox->SwapToCurrent();

		Update();

		if ( !getCore()->BoxesOnly )
			getCore()->VisualResettedOnce = true;
	}

	void NormalBlock::PhsxStep()
	{
		int Padding = 250;
		if ( getMyLevel()->PlayMode != 0 )
			Padding = -150;

		Active = getCore()->Active = true;
		Vector2 BL = MyBox->Current->BL;
		if ( MyBox->Current->BL.X > getBlockCore()->MyLevel->getMainCamera()->TR.X + Padding || MyBox->Current->BL.Y > getBlockCore()->MyLevel->getMainCamera()->TR.Y + 500 ) //+ 1250)
			Active = getCore()->Active = false;
		Vector2 TR = MyBox->Current->TR;
		if ( MyBox->Current->TR.X < getBlockCore()->MyLevel->getMainCamera()->BL.X - Padding || MyBox->Current->TR.Y < getBlockCore()->MyLevel->getMainCamera()->BL.Y - 250 ) //- 500)
			Active = getCore()->Active = false;
	}

	void NormalBlock::PhsxStep2()
	{
		if ( Moved )
			MyBox->SwapToCurrent();

		if ( !Active )
			return;
	}

	void NormalBlock::Update()
	{
		MyDraw->Update();
	}

	void NormalBlock::MoveTo( Vector2 Pos )
	{
		getCore()->Data.Position = Pos;
		MyBox->Target->Center = Pos;

		getBox()->SetTarget(getBox()->Target->Center, getBox()->Target->Size);
		Moved = true;
	}

	void NormalBlock::Extend( Side side, float pos )
	{
		Tools::Assert( getCore()->getMyTileSet() != 0 );

		MyBox->Invalidated = true;

		MyBox->Extend( side, pos );

		Update();
		MyBox->Validate();

		if ( !getCore()->BoxesOnly )
			MyDraw->Init( std::static_pointer_cast<BlockBase>( shared_from_this() ), GetPieceTemplate(), Invert );

		getBlockCore()->StartData.Position = MyBox->Current->Center;

		if ( !getCore()->BoxesOnly )
			ResetPieces();
	}

	void NormalBlock::Draw()
	{
		if ( !Active )
			return;
		if ( !getCore()->Active )
			return;

		Update();

		if ( Tools::DrawBoxes )
			MyBox->Draw( Tools::QDrawer, Color::Olive, 15 );

		if ( getBlockCore()->BoxesOnly )
			return;

		if ( Tools::DrawGraphics && getCore()->Show )
		{
			if ( getCore()->getMyTileSet() != TileSets::None )
			{
				//if (BlockCore.Ceiling)
					MyDraw->Draw();
				//Tools.QDrawer.Flush();
			}

			if ( getCore()->Encased )
			{
				MyBox->DrawFilled( Tools::QDrawer, bColor( 100, 100, 200, 100 ) );
				MyBox->Draw( Tools::QDrawer, bColor( 120, 120, 240, 150 ), 18, true );
			}

			getBlockCore()->Draw();
		}
	}

	void NormalBlock::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		std::shared_ptr<NormalBlock> BlockA = std::dynamic_pointer_cast<NormalBlock>( A );
		getBlockCore()->Clone(A->getCore());

		if ( BlockA == 0 )
			return;

		getBox()->TopOnly = BlockA->getBox()->TopOnly;

		Init( BlockA->getBox()->Current->Center, BlockA->getBox()->Current->Size, A->getCore()->getMyTileSet() );

		if ( MyDraw != 0 && BlockA->MyDraw != 0 )
			MyDraw->Clone( BlockA->MyDraw );
	}

	void NormalBlock::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		getBlockCore()->Write(writer);

		getBox()->Write(writer);
	}

	void NormalBlock::Read( const std::shared_ptr<BinaryReader> &reader )
	{
		getBlockCore()->Read(reader);

		getBox()->Read(reader);
		ResetPieces();
	}

	bool NormalBlock::PreDecision( const std::shared_ptr<Bob> &bob )
	{
		if ( getBlockCore()->Ceiling )
		{
			if ( bob->getCore()->Data.Position.X > getBox()->Current->BL.X - 100 && bob->getCore()->Data.Position.X < getBox()->Current->TR.X + 100 )
			{
				float NewBottom = getBox()->Current->BL.Y;

				// If ceiling has a left neighbor make sure we aren't too close to it
				if ( getBlockCore()->TopLeftNeighbor != 0 )
				{
					if ( NewBottom > getBlockCore()->TopLeftNeighbor->getBox()->Current->BL.Y - 100 )
						NewBottom = __max( NewBottom, getBlockCore()->TopLeftNeighbor->getBox()->Current->BL.Y + 120 );
				}
				Extend( Side_BOTTOM, __max( NewBottom, __max( bob->Box->Target->TR.Y, bob->Box->Current->TR.Y ) + bob->CeilingParams->BufferSize.GetVal( bob->getCore()->Data.Position ) ) );

				if ( getBox()->Current->Size.Y < 170 || getBox()->Current->BL.Y > bob->getCore()->MyLevel->getMainCamera()->TR.Y - 75 )
				{
					bob->DeleteObj( shared_from_this() );
				}
			}

			return true;
		}

		return false;
	}

	bool NormalBlock::PostCollidePreDecision( const std::shared_ptr<Bob> &bob )
	{
		if ( getBlockCore()->Ceiling )
		{
			Extend( Side_BOTTOM, __max( getBox()->Current->BL.Y, __max(bob->Box->Target->TR.Y, bob->Box->Current->TR.Y) + bob->CeilingParams->BufferSize.GetVal(bob->getCore()->Data.Position) ) );
			return true;
		}

		return false;
	}

	void NormalBlock::PostCollideDecision( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap, bool &Delete )
	{
		Block_PostCollideDecision( std::dynamic_pointer_cast<BlockBase>( shared_from_this() ), bob, Col, Overlap, Delete );
		BlockBase::PostCollideDecision( bob, Col, Overlap, Delete );
	}

	void NormalBlock::Block_PostCollideDecision( const std::shared_ptr<BlockBase> &block, const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap, bool &Delete )
	{
		bool MakeTopOnly = false;

		if ( !block->getCore()->GenData.NoMakingTopOnly )
		{
			// If we interact with the block in any way besides landing on top of it, make it top only
			if ( ( Col == ColType_BOTTOM || Overlap ) && Col != ColType_TOP )
				MakeTopOnly = true;
			if ( Col == ColType_LEFT || Col == ColType_RIGHT )
				MakeTopOnly = true;

			//// Note if we use the left or right side of the block
			//if ((Col == ColType.Left || Col == ColType.Right) && Col != ColType.Top)
			//{
			//    if (bob.Box.Current.TR.Y < block.Box.Current.TR.Y)
			//        MakeTopOnly = true;
			//    else
			//        MakeTopOnly = true;
			//}

			// If we've used something besides the top of the block already,
			// or this tileset doesn't allow for top only blocks,
			// then make sure we don't make the block top only.
			if ( block->getBlockCore()->NonTopUsed || !(std::dynamic_pointer_cast<NormalBlock>(block) != 0) || !block->getInfo()->AllowTopOnlyBlocks )
			{
				if ( MakeTopOnly )
				{
					MakeTopOnly = false;
					Delete = true;
				}
			}

			// If we are trying to make a block be top only that can't be, delete it
			if ( MakeTopOnly && block->getBlockCore()->DeleteIfTopOnly )
			{
				if ( block->getCore()->GenData.Used )
					MakeTopOnly = Delete = false;
				else
					Delete = true;
			}

			// If we have decided to make the block top only, actually do so
			if ( MakeTopOnly )
			{
				block->Extend( Side_BOTTOM, __max( block->getBox()->Current->BL.Y, __max(bob->Box->Target->TR.Y, bob->Box->Current->TR.Y) + bob->CeilingParams->BufferSize.GetVal(bob->getCore()->Data.Position) ) );
				( std::static_pointer_cast<NormalBlock>( block ) )->CheckHeight();
				if ( Col != ColType_TOP )
					Col = ColType_NO_COL;
			}
		}
	}

	void NormalBlock::PostInteractWith( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		BlockBase::PostInteractWith( bob, Col, Overlap );

		std::shared_ptr<BlockBase> block = std::static_pointer_cast<BlockBase>( shared_from_this() );

		// Draw block upside down if Bob used it upside down.
		if ( Col == ColType_BOTTOM && bob->MyPhsx->Gravity < 0 )
			getBlockCore()->CeilingDraw = true;

		// Normal blocks delete surrounding blocks when stamped as used
		if ( block->getCore()->GenData.DeleteSurroundingOnUse && std::dynamic_pointer_cast<NormalBlock>(block) != 0 )
			for ( BlockVec::const_iterator nblock = getCore()->MyLevel->Blocks.begin(); nblock != getCore()->MyLevel->Blocks.end(); ++nblock )
			{
				std::shared_ptr<NormalBlock> Normal = std::dynamic_pointer_cast<NormalBlock>( *nblock );
				if ( 0 != Normal && !Normal->getCore()->MarkedForDeletion && !Normal->getCore()->GenData.AlwaysUse )
					if ( !Normal->getCore()->GenData.Used && abs(Normal->getBox()->Current->TR.Y - block->getBox()->TR.Y) < 15 && !(Normal->getBox()->Current->TR.X < block->getBox()->Current->BL.X - 350 || Normal->getBox()->Current->BL.X > block->getBox()->Current->TR.X + 350) )
					{
						bob->DeleteObj( Normal );
						Normal->setIsActive( false );
					}
			}
	}

	void NormalBlock::PostKeep( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		BlockBase::PostKeep( bob, Col, Overlap );

		std::shared_ptr<BlockBase> block = std::static_pointer_cast<NormalBlock>( shared_from_this() );

		if ( !block->getCore()->GenData.NoBottomShift )
		{
			// Shift bottom of block if necessary
			if ( std::dynamic_pointer_cast<NormalBlock>( block ) != 0 && !block->getBlockCore()->DeleteIfTopOnly )
			{
				float NewBottom = __max( block->getBox()->Current->BL.Y, __max(getBox()->Target->TR.Y, getBox()->Current->TR.Y) + bob->CeilingParams->BufferSize.GetVal(getCore()->Data.Position) );

				if ( ( Col == ColType_BOTTOM || Overlap ) && Col != ColType_TOP && !block->getBlockCore()->NonTopUsed )
				{
					block->Extend( Side_BOTTOM, NewBottom );
					( std::static_pointer_cast<NormalBlock>( block ) )->CheckHeight();
				}
			}
		}
	}

	void NormalBlock::InitializeInstanceFields()
	{
		Invert = false;
	}
}
