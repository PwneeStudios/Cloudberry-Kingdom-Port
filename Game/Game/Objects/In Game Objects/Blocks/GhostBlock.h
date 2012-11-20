#ifndef GHOSTBLOCK
#define GHOSTBLOCK

#include <global_header.h>

namespace CloudberryKingdom
{
	class BlockGroup;
}

namespace CloudberryKingdom
{
	class TextureOrAnim;
}

namespace CloudberryKingdom
{
	class SimpleObject;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}



namespace CloudberryKingdom
{
	class GhostBlock : public BlockBase
	{
	public:
		class GhostBlockTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<BlockGroup> Group;
			std::shared_ptr<TextureOrAnim> Sprite;
			Vector2 Shift;

		private:
			void InitializeInstanceFields();

public:
			GhostBlockTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		std::shared_ptr<SimpleObject> MyObject;

	private:
		GhostBlockState State;

		/// <summary>
		/// When phased in, StateChange == 1 means fully phased in
		///                 StateChange == 0 means fully phased out, ready to change state to phased out
		/// When phased out, StateChange == 1 means fully phased out
		///                  StateChange == 0 means fully phased in, ready to change state to phased in
		/// </summary>
		float StateChange;

	public:
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

	private:
		void SetAnimation();

	public:
		GhostBlock( bool BoxesOnly );

		static float TallScale;
		bool TallBox;
		void Init( Vector2 center, Vector2 size, const std::shared_ptr<Level> &level );

		virtual void Reset( bool BoxesOnly );

		void AnimStep();

		const int &getPeriod() const;

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

		virtual void PostInteractWith( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef GHOSTBLOCK
