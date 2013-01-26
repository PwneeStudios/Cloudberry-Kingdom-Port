#ifndef BLOCK
#define BLOCK

#include <global_header.h>

#include "Core/FancyVector2.h"
#include "Core/FancyColor.h"
#include "Core/PhsxData.h"
#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
#include "Core/WriteReadTools.h"
#include "Core/Animation/SpriteAnim.h"
#include "Core/Effects/EzEffectWad.h"
#include "Core/Effects/EzEffect.h"
#include "Core/Graphics/MainRender.h"
#include "Core/Graphics/QuadDrawer.h"
#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"

namespace CloudberryKingdom
{
	
	struct BlockData : public ObjectData
	{

		virtual ~BlockData() { }
	
		void Decide_RemoveIfUnused( float ChanceToKeep, const boost::shared_ptr<Rand> &Rnd );

		bool Safe;

		bool Finalized, NoExtend;

		/// <summary>
		/// If false then objects attached to the block use Box.Target.Center as their reference point,
		/// otherwise they use CustomCenterAsParent
		/// </summary>
		bool UseCustomCenterAsParent;
		Vector2 CustomCenterAsParent;
		Vector2 OffsetMultAsParent;

		/// <summary>
		/// If true the block is drawn upside down.
		/// </summary>
		PieceQuad::Orientation MyOrientation;

		/// <summary>
		/// If true, overlapping non-child objects are removed.
		/// </summary>
		bool RemoveOverlappingObjects;

		/// <summary>
		/// True if any part of the block besides the top has been used.
		/// </summary>
		bool NonTopUsed;

		/// <summary>
		/// If true the block can not have its height modified, even if the tile set allows it.
		/// </summary>
		bool DisableFlexibleHeight;

		/// <summary>
		/// If true the block is deleted if ever attempted to be made TopOnly
		/// </summary>
		bool DeleteIfTopOnly;

		bool StoodOn, HitHead;

		/// <summary>
		/// When true the block will not override the imposition of another block.
		/// </summary>
		bool DoNotPushHard;

		/// <summary>
		/// If true then a player that lands on this block will take on its Y-velocity.
		/// </summary>
		bool GivesVelocity;

		/// <summary>
		/// The speed of the top surface of this block
		/// </summary>
		float GroundSpeed;

		float Layer;

		bool UseTopOnlyTexture;

		bool Ceiling, CeilingDraw, BlobsOnTop, Virgin;

		/// <summary>
		/// If true this block is an end piece of a level, typically with a door on it.
		/// </summary>
		bool EndPiece;

		/// <summary>
		/// If true this block is an start piece of a level, typically with a door on it.
		/// </summary>
		bool StartPiece;

		bool OnlyCollidesWithLowerLayers;

		boost::shared_ptr<BlockBase> TopRightNeighbor, TopLeftNeighbor;

		ObjectVec Objects;

		virtual void Release();

		void Draw();

		virtual void Init();

		virtual void Clone( const boost::shared_ptr<ObjectData> &A );

		virtual void Write( const boost::shared_ptr<BinaryWriter> &writer );

		virtual void Read( const boost::shared_ptr<BinaryReader> &reader );

	
		void InitializeInstanceFields();


		BlockData();
	};

	struct BlockBase : public ObjectBase
	{
	
		virtual ~BlockBase() { }

		boost::shared_ptr<AABox> MyBox;
		const boost::shared_ptr<AABox> &getBox() const;

		bool Active;
		const bool &getIsActive() const;
		void setIsActive( const bool &value );

	
		boost::shared_ptr<BlockData> BlockCoreData;
	
		const boost::shared_ptr<BlockData> &getBlockCore() const;

		BlockBase();

		virtual void Release();

		virtual void Reset( bool BoxesOnly );

		void Init( Vector2 &center, Vector2 &size, const boost::shared_ptr<Level> &level, const boost::shared_ptr<BlockGroup> &group );
		virtual void AdditionalInit( Vector2 center, Vector2 size, const boost::shared_ptr<Level> &level, bool _UseLowerBlockBounds );

		boost::shared_ptr<NormalBlockDraw> MyDraw;
		virtual void ResetPieces();

		virtual void PhsxStep2();


		virtual void Extend( Side side, float pos );

		virtual void LandedOn( const boost::shared_ptr<Bob> &bob );
		virtual void HitHeadOn( const boost::shared_ptr<Bob> &bob );
		virtual void SideHit( const boost::shared_ptr<Bob> &bob );
		virtual void Hit( const boost::shared_ptr<Bob> &bob );

		virtual bool PostCollidePreDecision( const boost::shared_ptr<Bob> &bob );

		virtual bool PostCollideDecision_Bottom_Meat( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Bottom_Normal( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Bottom( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual bool PostCollideDecision_Side_Meat( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Side_Normal( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Side( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual bool PostCollideDecision_Land_Meat( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Land_Normal( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Land( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual void PostCollideDecision( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap, bool &Delete );

	
		void EdgeSafety( const boost::shared_ptr<Bob> &bob, bool &Delete );

	
		virtual void PostKeep( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual void PostInteractWith( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		// These were extension methods
		void StampAsFullyUsed( int CurPhsxStep );
		void Stretch( Side side, float amount );
	};

}

#endif	//#ifndef BLOCK
