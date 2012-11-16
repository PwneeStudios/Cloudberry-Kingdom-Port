#ifndef LASER
#define LASER

#include <global_header.h>

namespace CloudberryKingdom
{
	class LineSpriteInfo;
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
	enum LaserState
	{
		LaserState_OFF,
		LaserState_WARN,
		LaserState_ON
	};
	class Laser : public _LineDeath, public IBound
	{
	public:
		class LaserTileInfo : public TileInfoBase
		{
		public:
//C# TO C++ CONVERTER NOTE: The variable Line was renamed since it is named the same as a user-defined type:
			std::shared_ptr<LineSpriteInfo> Line_Renamed;

			Vector4 Tint_Full;
			Vector4 Tint_Half;
			float Scale;

		private:
			void InitializeInstanceFields();

public:
			LaserTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	private:
		LaserState MyState;
		float StateChange;

	public:
		bool AlwaysOn, AlwaysOff;
		int Offset, Period, Duration, WarnDuration;

		virtual void MakeNew();

		Laser( bool BoxesOnly );

		void SetLine( Vector2 p, float degrees );

		/// <summary>
		/// Set the laser end points and calculate it's width (for optimization purposes).
		/// </summary>
		void SetLine( Vector2 p1, Vector2 p2 );

	private:
		Vector2 BL, TR;
	public:
		Vector2 TR_Bound();
		Vector2 BL_Bound();

	protected:
		virtual void ActivePhsxStep();

	public:
		float SmallerWidth;
	protected:
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	public:
		void MoveToBounded( Vector2 shift );

		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef LASER
