#ifndef FIRESPINNER
#define FIRESPINNER

#define _USE_MATH_DEFINES
#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_LineDeath.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/FireSpinner__Auto.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct FireSpinner : public _LineDeath
	{

		virtual ~FireSpinner()
		{
#ifdef BOOST_BIN
			OnDestructor( "FireSpinner" );
#endif
		}

	
		struct FireSpinnerTileInfo : public TileInfoBase
		{
			//public SpriteInfo Flame = new SpriteInfo(Tools::Texture("small flame"), new Vector2(72, 72), Vector2.Zero, new Color(255, 140, 140));
		
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
