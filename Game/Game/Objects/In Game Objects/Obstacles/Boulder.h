#ifndef BOULDER
#define BOULDER

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	struct SpriteInfo;
}

namespace CloudberryKingdom
{
	struct LineSpriteInfo;
}

namespace CloudberryKingdom
{
	struct QuadClass;
}

namespace CloudberryKingdom
{
	struct Level;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}

namespace CloudberryKingdom
{
	struct Boulder : public _CircleDeath, public IBound
	{
	
		enum PivotLocationTypes
		{
			PivotLocationTypes_TOP_BOTTOM,
			PivotLocationTypes_LEFT_RIGHT
		};
	
		struct BoulderTileInfo : public TileInfoBase
		{
		
			std::shared_ptr<SpriteInfo> Ball;

			float Radius;

			std::shared_ptr<LineSpriteInfo> Chain;

		
			void InitializeInstanceFields();


			BoulderTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		std::shared_ptr<QuadClass> MyQuad;

		float Angle, MaxAngle, Length;
		int Period, Offset;
		Vector2 PivotPoint;

		virtual void OnAttachedToBlock();

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

	
		void SetLayers();

	
		Boulder( bool BoxesOnly );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		float MinY();

		float AddAngle;

		PivotLocationTypes PivotLocationType;

		/// <summary>
		/// Get's the specified position of the floater at time t
		/// </summary>
		/// <param name="t">The parametric time variable, t = (Step + Offset) / Period</param>
		/// <returns></returns>
	
		float CorrespondingAngle;
		Vector2 GetPos( float t );

	
		virtual void PhsxStep();

	
		bool OffScreen;
	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	
		void CalculateLength();

		virtual void Move( Vector2 shift );

		void MoveToBounded( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BOULDER
