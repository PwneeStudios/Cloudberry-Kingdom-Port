#ifndef GHOSTBLOCK
#define GHOSTBLOCK

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GhostBlock : public BlockBase
	{

	
		struct GhostBlockTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<BlockGroup> Group;
			boost::shared_ptr<TextureOrAnim> Sprite;
			Vector2 Shift;

		
			void InitializeInstanceFields();

	
			GhostBlockTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		boost::shared_ptr<SimpleObject> MyObject;

	
		GhostBlockState State;

		/// <summary>
		/// When phased in, StateChange == 1 means fully phased in
		///                 StateChange == 0 means fully phased out, ready to change state to phased out
		/// When phased out, StateChange == 1 means fully phased out
		///                  StateChange == 0 means fully phased in, ready to change state to phased in
		/// </summary>
		float StateChange;

	
		float MyAnimSpeed;

		int InLength, OutLength, Offset;

		/// <summary>
		/// How close in time to the block fading out or in can the computer interact with the block.
		/// Units are time are in the time it takes for a phase change to happen.
		/// Smaller is harder.
		/// </summary>
		float TimeSafety;

		virtual void MakeNew();

		void SetState( GhostBlockState NewState );
		void SetState( GhostBlockState NewState, bool ForceSet );

	
		void SetAnimation();

	
		GhostBlock( bool BoxesOnly );

		static float TallScale;
		bool TallBox, TallInvertBox;
		void Init( Vector2 center, Vector2 size, const boost::shared_ptr<Level> &level );

		virtual void Reset( bool BoxesOnly );

		void AnimStep();

		const int getPeriod() const;

		/// <summary>
		/// Gets the Ghosts current step in its periodic cycle,
		/// shifting to account for its Offset
		/// </summary>
		float GetStep();

		/// <summary>
		/// Calculate what the Offset should be such that at this moment in time
		/// the Ghost is at the given step in its periodic cycle.
		/// </summary>
		void ModOffset( int DesiredStep );

		static int LengthOfPhaseChange;

		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Extend( Side side, float pos );

		virtual void Move( Vector2 shift );
		virtual void Draw();

		virtual void PostInteractWith( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef GHOSTBLOCK
