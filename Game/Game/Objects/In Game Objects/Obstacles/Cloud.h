#ifndef CLOUD
#define CLOUD

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	struct Cloud : public _Obstacle
	{
	
		struct CloudTileInfo : public TileInfoBase
		{
		
			std::shared_ptr<SpriteInfo> Sprite;
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

		std::shared_ptr<QuadClass> MyQuad;

		std::shared_ptr<AABox> Box;

		Cloud();
		Cloud( bool BoxesOnly );

	
		int PeriodOffset;

	
		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

		virtual void Construct( bool BoxesOnly );

	
		virtual void ActivePhsxStep();

	
		virtual void PhsxStep2();

	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	
		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

		virtual void Write( const std::shared_ptr<BinaryWriter> &writer );
		virtual void Read( const std::shared_ptr<BinaryReader> &reader );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOUD
