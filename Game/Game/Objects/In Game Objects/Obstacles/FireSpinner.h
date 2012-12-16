#ifndef FIRESPINNER
#define FIRESPINNER

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	struct FireSpinner : public _LineDeath
	{
	
		struct FireSpinnerTileInfo : public TileInfoBase
		{
			//public SpriteInfo Flame = new SpriteInfo(Tools.Texture("small flame"), new Vector2(72, 72), Vector2.Zero, new Color(255, 140, 140));
		
			boost::shared_ptr<SpriteInfo> Flame;
			boost::shared_ptr<SpriteInfo> Base;

			float SegmentSpacing;
			float SpaceFromBase;

			bool Rotate;
			float RotateStep;

			// Placement info
			float TopOffset, BottomOffset;

		
			void InitializeInstanceFields();


			FireSpinnerTileInfo()
			{
				InitializeInstanceFields();
			}
		};

		/// <summary>
		/// If true then the individual flames comprising the firespinners have an offset
		/// that varies between different firespinners (to prevent player 'vertigo')
		/// </summary>
	
		static bool RandomMiniOrientation;

	
		boost::shared_ptr<QuadClass> MyQuad, MyBaseQuad;

		int Offset, Period;

		float Radius;
		float Angle;

		/// <summary>
		/// Angle of the individual flames comprising the firespinner
		/// </summary>
	
		float MiniAngle;
		/// <summary>
		/// Offset angle of the individual flames comprising the firespinner
		/// </summary>
		float MiniAngle_Offset;

	
		int Orientation;

		Vector2 dir;

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		FireSpinner( bool BoxesOnly );

	
		virtual void ActivePhsxStep();

	
		void SetCurrent( float Step );
		void SetTarget( float Step );
		void GetLine( float Step, Vector2 &p1, Vector2 &p2 );

	
		virtual void DrawGraphics();

	
		virtual void Move( Vector2 shift );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef FIRESPINNER
