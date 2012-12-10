#ifndef MOVINGPLATFORM
#define MOVINGPLATFORM

#define _USE_MATH_DEFINES
#include <global_header.h>


namespace CloudberryKingdom
{
	struct MovingPlatform : public BlockBase
	{
	
		struct ElevatorTileInfo : public TileInfoBase
		{
		
			std::shared_ptr<BlockGroup> Group;

		
			void InitializeInstanceFields();


			ElevatorTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		enum MoveType
		{
			MoveType_NORMAL,
			MoveType_SINE
		};
	
		MoveType MyMoveType;
		float Amp;
		int Offset;

		Vector2 Range;

		std::shared_ptr<BlockEmitter> Parent;

	
		const std::shared_ptr<BlockEmitter_Parameters> getMyParams() const;

	
		virtual bool PermissionToUse();

		virtual void LandedOn( const std::shared_ptr<Bob> &bob );
		virtual void OnUsed();

		virtual void OnMarkedForDeletion();

		virtual void MakeNew();

		virtual void Release();

		MovingPlatform( bool BoxesOnly );

	
		BoxStyle MyBoxStyle;
	
		void Init( Vector2 center, Vector2 size, const std::shared_ptr<Level> &level, BoxStyle boxstyle );


		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef MOVINGPLATFORM
