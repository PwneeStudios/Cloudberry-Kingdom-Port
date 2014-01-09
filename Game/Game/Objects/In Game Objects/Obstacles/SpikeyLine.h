#ifndef SPIKEYLINE
#define SPIKEYLINE

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/IBounded.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_CircleDeath.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/Boulder__Auto.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct SpikeyLine : public _CircleDeath, public IBound
	{

		virtual ~SpikeyLine()
		{
#ifdef BOOST_BIN
			OnDestructor( "SpikeyLine" );
#endif
		}

	
		struct SpikeyLineTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Ball;

			float Radius;

			bool Rotate;
			float RotateOffset, RotateSpeed;

		
			void InitializeInstanceFields();


			SpikeyLineTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		int Period, Offset;
		Vector2 p1, p2;

	
		boost::shared_ptr<QuadClass> Head;

	
		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		SpikeyLine( bool BoxesOnly );

		/// <summary>
		/// Get's the specified position of the floater at time t
		/// </summary>
		/// <param name="t">The parametric time variable, t = (Step + Offset) / Period</param>
		/// <returns></returns>
		Vector2 GetPos( float t );

		virtual void PhsxStep();


	
		bool OffScreen;
	
		virtual void DrawGraphics();

	
		virtual void Move( Vector2 shift );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		void MoveToBounded( Vector2 shift );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef SPIKEYLINE
