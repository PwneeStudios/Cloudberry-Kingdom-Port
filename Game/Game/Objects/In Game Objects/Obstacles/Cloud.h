#ifndef CLOUD
#define CLOUD

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{

	struct Cloud : public _Obstacle
	{

		virtual ~Cloud() { }
	
		struct CloudTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Sprite;
			Vector2 BoxSize;

		
			void InitializeInstanceFields();


			CloudTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		Vector2 Displacement;
		float Shiftiness;
		Vector2 Size;

		boost::shared_ptr<QuadClass> MyQuad;

		boost::shared_ptr<AABox> Box;

		Cloud();
		Cloud( bool BoxesOnly );

	
		int PeriodOffset;

	
		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		virtual void Construct( bool BoxesOnly );

	
		virtual void ActivePhsxStep();

	
		virtual void PhsxStep2();

	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	
		virtual void Move( Vector2 shift );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

		virtual void Write( const boost::shared_ptr<BinaryWriter> &writer );
		virtual void Read( const boost::shared_ptr<BinaryReader> &reader );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef CLOUD
