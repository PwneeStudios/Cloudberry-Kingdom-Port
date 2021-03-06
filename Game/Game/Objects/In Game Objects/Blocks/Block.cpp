#include <small_header.h>
#include "Game/Objects/In Game Objects/Blocks/Block.h"

#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Core/Tools/Random.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Collision Detection/Phsx.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlock.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlockDraw.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Player/Hero Physics/Meat.h"
#include "Game/Tilesets/BlockGroup.h"

#include "Game/Tilesets/TileSetInfo.h"
#include "Game/Tools/Camera.h"

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	void BlockData::Decide_RemoveIfUnused( float ChanceToKeep, const boost::shared_ptr<Rand> &Rnd )
	{
		GenData.Decide_RemoveIfUnused( ChanceToKeep, Rnd );
		if ( GenData.RemoveIfUnused || Rnd->RndFloat() < .75f )
			BlobsOnTop = true;
		else
			Virgin = true;
	}

	void BlockData::Release()
	{
		ObjectData::Release();

		//Objects = null;
		Objects.clear();

		TopRightNeighbor.reset();
		TopLeftNeighbor.reset();
	}

	void BlockData::Draw()
	{
		if ( Objects.empty() )
			return;

		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			if ( !( *obj )->getCore()->MarkedForDeletion )
				( *obj )->Draw();
	}

	void BlockData::Init()
	{
		ObjectData::Init();

		//Objects = new List<IObject>();

		DoNotPushHard = false;

		UseCustomCenterAsParent = false;
		CustomCenterAsParent = Vector2();
		OffsetMultAsParent = Vector2(1);

		MyOrientation = PieceQuad::Orientation_NORMAL;

		RemoveOverlappingObjects = true;

		Finalized = NoExtend = false;

		NonTopUsed = false;

		DisableFlexibleHeight = false;
		DeleteIfTopOnly = false;

		StoodOn = HitHead = false;

		GivesVelocity = true;

		UseTopOnlyTexture = true;

		Layer = 0;

		CeilingDraw = Ceiling = BlobsOnTop = Virgin = false;

		TopLeftNeighbor = TopRightNeighbor = 0;
	}

	void BlockData::Clone( const boost::shared_ptr<ObjectData> &A )
	{
		ObjectData::Clone( A );

		boost::shared_ptr<BlockData> BlockDataA = boost::dynamic_pointer_cast<BlockData>( A );
		// FIXME: Implement exceptions?
		//if ( BlockDataA == 0 )
		//	throw ( std::exception( std::wstring( L"Can't copy block data from object data" ) ) );

		Safe = BlockDataA->Safe;

		UseCustomCenterAsParent = BlockDataA->UseCustomCenterAsParent;
		CustomCenterAsParent = BlockDataA->CustomCenterAsParent;
		OffsetMultAsParent = BlockDataA->OffsetMultAsParent;

		MyOrientation = BlockDataA->MyOrientation;

		GivesVelocity = BlockDataA->GivesVelocity;

		EndPiece = BlockDataA->EndPiece;

		BlobsOnTop = BlockDataA->BlobsOnTop;
		Ceiling = BlockDataA->Ceiling;
		CeilingDraw = BlockDataA->CeilingDraw;
		Virgin = BlockDataA->Virgin;

		UseTopOnlyTexture = BlockDataA->UseTopOnlyTexture;

		OnlyCollidesWithLowerLayers = BlockDataA->OnlyCollidesWithLowerLayers;

		Layer = BlockDataA->Layer;

		Objects.clear();
		AddRange( Objects, BlockDataA->Objects );
	}

	void BlockData::Write( const boost::shared_ptr<BinaryWriter> &writer )
	{
		ObjectData::Write( writer );

		writer->Write( Safe );

		writer->Write( BlobsOnTop );
		writer->Write( Ceiling );
		writer->Write( Virgin );

		writer->Write( OnlyCollidesWithLowerLayers );

		writer->Write( Layer );
	}

	void BlockData::Read( const boost::shared_ptr<BinaryReader> &reader )
	{
		ObjectData::Read( reader );

		Safe = reader->ReadBoolean();

		BlobsOnTop = reader->ReadBoolean();
		Ceiling = reader->ReadBoolean();
		Virgin = reader->ReadBoolean();

		OnlyCollidesWithLowerLayers = reader->ReadBoolean();

		Layer = static_cast<float>( reader->ReadInt32() );
	}

	void BlockData::InitializeInstanceFields()
	{
		Objects = ObjectVec();
	}

	BlockData::BlockData() :
		Safe( false ),
		Finalized( false ),
		NoExtend( false ),
		UseCustomCenterAsParent( false ),
		MyOrientation( PieceQuad::Orientation_NORMAL ),
		RemoveOverlappingObjects( false ),
		NonTopUsed( false ),
		DisableFlexibleHeight( false ),
		DeleteIfTopOnly( false ),
		StoodOn( false ),
		HitHead( false ),
		DoNotPushHard( false ),
		GivesVelocity( false ),
		GroundSpeed( 0 ),
		Layer( 0 ),
		UseTopOnlyTexture( false ),
		Ceiling( false ),
		CeilingDraw( false ),
		BlobsOnTop( false ),
		Virgin( false ),
		EndPiece( false ),
		StartPiece( false ),
		OnlyCollidesWithLowerLayers( false )
	{
		InitializeInstanceFields();
	}

	const boost::shared_ptr<AABox> &BlockBase::getBox() const
	{
		return MyBox;
	}

	const bool &BlockBase::getIsActive() const
	{
		return Active;
	}

	void BlockBase::setIsActive( const bool &value )
	{
		Active = value;
	}

	const boost::shared_ptr<BlockData> &BlockBase::getBlockCore() const
	{
		return BlockCoreData;
	}

	BlockBase::BlockBase() :
		Active( false )
	{
		BlockCoreData = boost::make_shared<BlockData>();
		CoreData = boost::dynamic_pointer_cast<ObjectData>( getBlockCore() );
	}

	void BlockBase::Release()
	{
		ObjectBase::Release();

		MyBox.reset();

		if ( MyDraw != 0 )
		{
			MyDraw->Release();
			MyDraw.reset();
		}
	}

	void BlockBase::Reset( bool BoxesOnly )
	{
		ObjectBase::Reset( BoxesOnly );

		getBlockCore()->BoxesOnly = BoxesOnly;

		if ( !getCore()->BoxesOnly )
			ResetPieces();
	}

	void BlockBase::Init( Vector2 &center, Vector2 &size, const boost::shared_ptr<Level> &level, const boost::shared_ptr<BlockGroup> &group )
	{
		size *= level->getInfo()->ScaleAll * level->getInfo()->ScaleAllBlocks;

		if ( level->MyTileSet->FixedWidths )
			group->SnapWidthUp( size );
		MyBox->Initialize( center, size );
		MyDraw->MyTemplate = getCore()->getMyTileSet()->GetPieceTemplate( boost::static_pointer_cast<BlockBase>( shared_from_this() ), level->getRnd(), group);

        bool _UseLowerBlockBounds = false;
        if ( level != 0 && level->CurMakeData != 0 )
            _UseLowerBlockBounds = level->getStyle()->UseLowerBlockBounds;

        AdditionalInit( center, size, level, _UseLowerBlockBounds );
    }

    void BlockBase::AdditionalInit( Vector2 center, Vector2 size, const boost::shared_ptr<Level> &level, bool _UseLowerBlockBounds )
    {
        float newsizey = MyDraw->MyTemplate->ModLowerBlockBound;
        if ( _UseLowerBlockBounds && newsizey != 0)
        {
            float shift;

            if ( MyDraw->MyTemplate->RelativeLowerLip)
            {
                shift = newsizey;
                center.Y -= shift / 2;
                size.Y += shift;
            }
            else
            {
                shift = (newsizey - size.Y);
                center.Y -= shift / 2;
                size.Y += shift;
            }
            MyBox->Initialize( center, size );
        }

		getCore()->Data.Position = getBlockCore()->Data.Position = getBlockCore()->StartData.Position = center;

		if ( !getCore()->BoxesOnly )
			Reset( false );
	}

	void BlockBase::ResetPieces()
	{
		if ( MyDraw == 0 )
			return;

		MyDraw->Init( boost::static_pointer_cast<BlockBase>( shared_from_this() ) );

		MyDraw->MyPieces->Center.Playing = false;
	}

	void BlockBase::PhsxStep2()
	{
		if ( !Active )
			return;

		MyBox->SwapToCurrent();
	}

	void BlockBase::Extend( Side side, float pos )
	{
	}

	void BlockBase::LandedOn( const boost::shared_ptr<Bob> &bob )
	{
	}

	void BlockBase::HitHeadOn( const boost::shared_ptr<Bob> &bob )
	{
	}

	void BlockBase::SideHit( const boost::shared_ptr<Bob> &bob )
	{
	}

	void BlockBase::Hit( const boost::shared_ptr<Bob> &bob )
	{
	}

	bool BlockBase::PostCollidePreDecision( const boost::shared_ptr<Bob> &bob )
	{
		return false;
	}

	bool BlockBase::PostCollideDecision_Bottom_Meat( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		if ( Col == ColType_BOTTOM )
			return true;
		return false;
	}

	bool BlockBase::PostCollideDecision_Bottom_Normal( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		if ( bob->MyPhsx->Gravity > 0 )
		{
			//if (Col == ColType.Bottom && bob.Core.Data.Position.Y < bob.TargetPosition.Y) return true;
			if ( Col == ColType_BOTTOM )
				return true;
			return false;
		}
		else
		{
			//if (bob.TopCol && Col == ColType.Bottom) return true;
			//if (Col == ColType.Bottom && bob.WantsToLand != false) return true;
			if ( Col == ColType_TOP )
				return true;
			return false;
		}
	}

	bool BlockBase::PostCollideDecision_Bottom( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		if ( boost::dynamic_pointer_cast<BobPhsxMeat>( bob->MyPhsx ) != 0 )
			return PostCollideDecision_Bottom_Meat( bob, Col, Overlap );
		else
			return PostCollideDecision_Bottom_Normal( bob, Col, Overlap );
	}

	bool BlockBase::PostCollideDecision_Side_Meat( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		if ( Col == ColType_LEFT || Col == ColType_RIGHT )
		{
			if ( getCore()->GetPhsxStep() < bob->MyPhsx->LastUsedStamp + 7 )
				return true;

			if ( getBox()->BL.Y > bob->Box->TR.Y - 40 )
				return true;
			if ( getBox()->TR.Y < bob->Box->BL.Y + 40 )
				return true;
			//if (Box.BL.Y > bob.Box.TR.Y - 20) return true;
			//if (Box.TR.Y < bob.Box.BL.Y + 20) return true;


			if ( boost::dynamic_pointer_cast<BouncyBlock>( shared_from_this() ) != 0 )
				return true;

			//BobPhsxMeat meat = (BobPhsxMeat)bob.MyPhsx;
			float Safety = 860; // 650;
			if ( bob->getPos().X > getCam()->getPos().X + Safety && Col == ColType_LEFT )
				return false;
			if ( bob->getPos().X < getCam()->getPos().X - Safety && Col == ColType_RIGHT )
				return false;
			if ( bob->getPos().X > getCam()->getPos().X + Safety && Col == ColType_RIGHT )
				return true;
			if ( bob->getPos().X < getCam()->getPos().X - Safety && Col == ColType_LEFT )
				return true;

			//return false;
			if ( bob->WantsToLand )
				return false;
			else
				return true;
		}

		return false;
	}

	bool BlockBase::PostCollideDecision_Side_Normal( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		if ( Col == ColType_LEFT || Col == ColType_RIGHT )
			return true;

		if ( bob->MyPhsx->Gravity > 0 )
		{
			if ( Col != ColType_TOP && Overlap )
				return true;
		}
		else
		{
			if ( Col != ColType_BOTTOM && Overlap )
				return true;
		}

		return false;
	}

	bool BlockBase::PostCollideDecision_Side( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		if ( boost::dynamic_pointer_cast<BobPhsxMeat>( bob->MyPhsx ) != 0 )
			return PostCollideDecision_Side_Meat( bob, Col, Overlap );
		else
			return PostCollideDecision_Side_Normal( bob, Col, Overlap );
	}

	bool BlockBase::PostCollideDecision_Land_Meat( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		boost::shared_ptr<BobPhsxMeat> meat = boost::static_pointer_cast<BobPhsxMeat>( bob->MyPhsx );

		if ( meat->WantToLandOnTop && Col == ColType_TOP )
			return false;

		if ( boost::dynamic_pointer_cast<BouncyBlock>( shared_from_this() ) != 0 )
			return false;

		if ( Col == ColType_TOP )
			return true;

		return false;
	}

	bool BlockBase::PostCollideDecision_Land_Normal( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		if ( bob->MyPhsx->Gravity > 0 )
		{
			if ( Col == ColType_TOP && bob->WantsToLand == false )
				return true;
		}
		else
		{
			if ( Col == ColType_BOTTOM && bob->WantsToLand == false )
				return true;
		}

		return false;
	}

	bool BlockBase::PostCollideDecision_Land( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
		if ( boost::dynamic_pointer_cast<BobPhsxMeat>( bob->MyPhsx ) != 0 )
			return PostCollideDecision_Land_Meat( bob, Col, Overlap );
		else
			return PostCollideDecision_Land_Normal( bob, Col, Overlap );
	}

	void BlockBase::PostCollideDecision( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap, bool &Delete )
	{
		// Decide if we should delete or keep the block
		//bool Delete = false;

		// MAKE SAVENOBLOCK a countdown
		if ( bob->SaveNoBlock )
			Delete = true;
		if ( bob->BottomCol && Col == ColType_TOP )
			Delete = true;
		if ( bob->TopCol && Col == ColType_BOTTOM )
			Delete = true;

		//if (Col == ColType.Top && bob.WantsToLand == false) Delete = true;

		Delete |= PostCollideDecision_Land( bob, Col, Overlap );
		Delete |= PostCollideDecision_Bottom( bob, Col, Overlap );
		Delete |= PostCollideDecision_Side( bob, Col, Overlap );

		// ???
		if ( Overlap && Col == ColType_NO_COL && !getBox()->TopOnly && !(boost::dynamic_pointer_cast<NormalBlock>( shared_from_this() ) != 0 && !getBlockCore()->NonTopUsed) )
			Delete = true;

		// Don't land on the very edge of the block
		EdgeSafety( bob, Delete );

		// Don't land on a block that says not to
		bool DesiresDeletion = false;
		if ( getCore()->GenData.TemporaryNoLandZone || !getCore()->GenData.Used && !(boost::static_pointer_cast<BlockBase>( shared_from_this() ) )->PermissionToUse() )
			DesiresDeletion = Delete = true;

		if ( getCore()->GenData.Used )
			Delete = false;
		if ( !DesiresDeletion && getCore()->GenData.AlwaysLandOn && !getCore()->MarkedForDeletion && Col == ColType_TOP )
			Delete = false;
		if ( !DesiresDeletion && getCore()->GenData.AlwaysLandOn_Reluctantly && bob->WantsToLand_Reluctant && !getCore()->MarkedForDeletion && Col == ColType_TOP )
			Delete = false;

		if ( Overlap && getCore()->GenData.RemoveIfOverlap )
			Delete = true;
		if ( !DesiresDeletion && getCore()->GenData.AlwaysUse && !getCore()->MarkedForDeletion )
			Delete = false;
	}

	void BlockBase::EdgeSafety( const boost::shared_ptr<Bob> &bob, bool &Delete )
	{
		if ( boost::dynamic_pointer_cast<BobPhsxMeat>( bob->MyPhsx ) != 0 )
			return;

		if ( !Delete && !bob->MyPhsx->OnGround )
		{
			float Safety = getBlockCore()->GenData.EdgeSafety;
			if ( bob->Box->BL.X > getBox()->TR.X - Safety || bob->Box->TR.X < getBox()->BL.X + Safety )
			{
				Delete = true;
			}
		}
	}

	void BlockBase::PostKeep( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
	}

	void BlockBase::PostInteractWith( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap )
	{
	}

	void BlockBase::StampAsFullyUsed( int CurPhsxStep )
	{
		StampAsUsed( CurPhsxStep );
		getBlockCore()->NonTopUsed = true;
	}

	void BlockBase::Stretch( Side side, float amount )
	{
		getBox()->CalcBounds();
		switch ( side )
		{
			case Side_RIGHT:
				Extend( side, getBox()->GetTR().X + amount );
				break;
			case Side_LEFT:
				Extend( side, getBox()->GetBL().X + amount );
				break;
			case Side_TOP:
				Extend( side, getBox()->GetTR().Y + amount );
				break;
			case Side_BOTTOM:
				Extend( side, getBox()->GetBL().Y + amount );
				break;
		}
	}

}
