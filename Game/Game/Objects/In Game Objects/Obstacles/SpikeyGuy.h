#ifndef SPIKEYGUY
#define SPIKEYGUY

#define _USE_MATH_DEFINES
#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_CircleDeath.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/SpikeyGuy__Auto.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	
	struct SpikeyGuy : public _CircleDeath
	{

		virtual ~SpikeyGuy()
		{
#ifdef BOOST_BIN
			OnDestructor( "SpikeyGuy" );
#endif
		}

	
		struct SpikeyGuyTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Ball;
			boost::shared_ptr<SpriteInfo> Base;

			boost::shared_ptr<LineSpriteInfo> Chain;

			float Radius;

			bool Rotate;
			float RotateOffset, RotateSpeed;

		
			void InitializeInstanceFields();


			SpikeyGuyTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		float Angle, MaxAngle, Length;
		int Period, Offset;
		Vector2 PivotPoint;

		int Dir;

	
		boost::shared_ptr<QuadClass> Anchor, Head;

	
		virtual void OnAttachedToBlock();

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		SpikeyGuy( bool BoxesOnly );

		float MinY();

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

	
		virtual void Move( Vector2 shift );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef SPIKEYGUY
