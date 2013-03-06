#ifndef MOVINGPLATFORM
#define MOVINGPLATFORM

#define _USE_MATH_DEFINES
#include <global_header.h>


namespace CloudberryKingdom
{
	struct MovingPlatform : public BlockBase
	{
	
		virtual ~MovingPlatform()
		{
#ifdef BOOST_BIN
			OnDestructor( "MovingPlatform" );
#endif
		}


		struct ElevatorTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<BlockGroup> Group;

		
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

		boost::shared_ptr<BlockEmitter> Parent;

	
		const boost::shared_ptr<BlockEmitter_Parameters> getMyParams() const;

	
		virtual bool PermissionToUse();

		virtual void LandedOn( const boost::shared_ptr<Bob> &bob );
		virtual void OnUsed();

		virtual void OnMarkedForDeletion();

		virtual void MakeNew();

		virtual void Release();

		MovingPlatform( bool BoxesOnly );

	
		BoxStyle MyBoxStyle;
	
		void Init( Vector2 center, Vector2 size, const boost::shared_ptr<Level> &level, BoxStyle boxstyle );


		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		virtual void Draw();

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef MOVINGPLATFORM
