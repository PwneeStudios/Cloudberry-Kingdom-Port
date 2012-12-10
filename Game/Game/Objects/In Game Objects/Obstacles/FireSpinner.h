#ifndef FIRESPINNER
#define FIRESPINNER

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class FireSpinner : public _LineDeath
	{
	public:
		class FireSpinnerTileInfo : public TileInfoBase
		{
			//public SpriteInfo Flame = new SpriteInfo(Tools.Texture("small flame"), new Vector2(72, 72), Vector2.Zero, new Color(255, 140, 140));
		public:
			std::shared_ptr<SpriteInfo> Flame;
			std::shared_ptr<SpriteInfo> Base;

			float SegmentSpacing;
			float SpaceFromBase;

			bool Rotate;
			float RotateStep;

			// Placement info
			float TopOffset, BottomOffset;

		private:
			void InitializeInstanceFields();

public:
			FireSpinnerTileInfo()
			{
				InitializeInstanceFields();
			}
		};

		/// <summary>
		/// If true then the individual flames comprising the firespinners have an offset
		/// that varies between different firespinners (to prevent player 'vertigo')
		/// </summary>
	private:
		static bool RandomMiniOrientation;

	public:
		std::shared_ptr<QuadClass> MyQuad, MyBaseQuad;

		int Offset, Period;

		float Radius;
		float Angle;

		/// <summary>
		/// Angle of the individual flames comprising the firespinner
		/// </summary>
	private:
		float MiniAngle;
		/// <summary>
		/// Offset angle of the individual flames comprising the firespinner
		/// </summary>
		float MiniAngle_Offset;

	public:
		int Orientation;

		Vector2 dir;

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

		FireSpinner( bool BoxesOnly );

	protected:
		virtual void ActivePhsxStep();

	private:
		void SetCurrent( float Step );
		void SetTarget( float Step );
		void GetLine( float Step, Vector2 &p1, Vector2 &p2 );

	protected:
		virtual void DrawGraphics();

	public:
		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef FIRESPINNER
