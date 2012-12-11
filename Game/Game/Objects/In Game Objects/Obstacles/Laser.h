#ifndef LASER
#define LASER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct LineSpriteInfo;
}

namespace CloudberryKingdom
{
	struct Bob;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}




namespace CloudberryKingdom
{
	enum LaserState
	{
		LaserState_OFF,
		LaserState_WARN,
		LaserState_ON
	};
	struct Laser : public _LineDeath, public IBound
	{
	
		struct LaserTileInfo : public TileInfoBase
		{
		
//C# TO C++ CONVERTER NOTE: The variable Line was renamed since it is named the same as a user-defined type:
			std::shared_ptr<LineSpriteInfo> Line_Renamed;

			Vector4 Tint_Full;
			Vector4 Tint_Half;
			float Scale;

		
			void InitializeInstanceFields();


			LaserTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		LaserState MyState;
		float StateChange;

	
		bool AlwaysOn, AlwaysOff;
		int Offset, Period, Duration, WarnDuration;

		virtual void MakeNew();

		Laser( bool BoxesOnly );

		void SetLine( Vector2 p, float degrees );

		/// <summary>
		/// Set the laser end points and calculate it's width (for optimization purposes).
		/// </summary>
		void SetLine( Vector2 p1, Vector2 p2 );

	
		Vector2 BL, TR;
	
		Vector2 TR_Bound();
		Vector2 BL_Bound();

	
		virtual void ActivePhsxStep();

	
		float SmallerWidth;
	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	
		void MoveToBounded( Vector2 shift );

		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef LASER
