#ifndef BLOCK
#define BLOCK

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BlockData : public ObjectData
	{
	
		void Decide_RemoveIfUnused( float ChanceToKeep, const std::shared_ptr<Rand> &Rnd );

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

		std::shared_ptr<BlockBase> TopRightNeighbor, TopLeftNeighbor;

		ObjectVec Objects;

		virtual void Release();

		void Draw();

		virtual void Init();

		virtual void Clone( const std::shared_ptr<ObjectData> &A );

		virtual void Write( const std::shared_ptr<BinaryWriter> &writer );

		virtual void Read( const std::shared_ptr<BinaryReader> &reader );

	
		void InitializeInstanceFields();


		BlockData();
	};

	struct BlockBase : public ObjectBase
	{
	
		std::shared_ptr<AABox> MyBox;
		const std::shared_ptr<AABox> &getBox() const;

		bool Active;
		const bool &getIsActive() const;
		void setIsActive( const bool &value );

	
		std::shared_ptr<BlockData> BlockCoreData;
	
		const std::shared_ptr<BlockData> &getBlockCore() const;

		BlockBase();

		virtual void Release();

		virtual void Reset( bool BoxesOnly );

		void Init( Vector2 &center, Vector2 &size, const std::shared_ptr<Level> &level, const std::shared_ptr<BlockGroup> &group );

		std::shared_ptr<NormalBlockDraw> MyDraw;
		virtual void ResetPieces();

		virtual void PhsxStep2();


		virtual void Extend( Side side, float pos );

		virtual void LandedOn( const std::shared_ptr<Bob> &bob );
		virtual void HitHeadOn( const std::shared_ptr<Bob> &bob );
		virtual void SideHit( const std::shared_ptr<Bob> &bob );
		virtual void Hit( const std::shared_ptr<Bob> &bob );

		virtual bool PostCollidePreDecision( const std::shared_ptr<Bob> &bob );

		virtual bool PostCollideDecision_Bottom_Meat( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Bottom_Normal( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Bottom( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual bool PostCollideDecision_Side_Meat( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Side_Normal( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Side( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual bool PostCollideDecision_Land_Meat( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Land_Normal( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual bool PostCollideDecision_Land( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual void PostCollideDecision( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap, bool &Delete );

	
		void EdgeSafety( const std::shared_ptr<Bob> &bob, bool &Delete );

	
		virtual void PostKeep( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );
		virtual void PostInteractWith( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		// These were extension methods
		void StampAsFullyUsed( int CurPhsxStep );
		void Stretch( Side side, float amount );
	};
}

#endif	//#ifndef BLOCK
